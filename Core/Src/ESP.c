/*
 * ESP.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 *              Bert Havinga nov-dec
 */


#include "ESP.h"
#include <String.h>
#include <stdio.h>
#include "EEprom.h"
#include "Config.h"
#include "microphone.h"
#include "PowerUtils.h"
#include "RealTimeClock.h"
#include "sen5x.h"
#include "statusCheck.h"
#include "main.h"
#include <stdint.h>
#include "setLED.h"

static UART_HandleTypeDef *EspUart = NULL;
extern DMA_HandleTypeDef hdma_usart4_rx;

static volatile bool RxComplete = false;

static uint8_t RxBuffer[ESP_MAX_BUFFER_SIZE] = {0};
// static uint8_t LastATResponse[ESP_MAX_BUFFER_SIZE] = {0};
static const char user[] = "Test";
static bool testRound = true;
bool EspTurnedOn = false;
static bool sendCWJAP = false;
static bool setTime = true;
static uint32_t uid[3];
static uint32_t start;
static uint32_t stop;
static uint8_t oldEspState = 255;
float batteryCharge = 0.0;
float solarCharge = 0.0;
ESPHandler *ESPHandle = NULL;
SensorType2 *HTLink = NULL;
SensorType1 *VOCLink = NULL;
SensorType1 *DBLink = NULL;
SensorType3 *SensLink = NULL; 

WifiConfig Credentials;

static char message[1152];
static const char API[] = "\"https://api.opensensemap.org/boxes/";
static AT_Commands ATCommandArray[10];
static AT_Commands AT_INIT[] = {AT_WAKEUP, AT_SET_RFPOWER, AT_CHECK_RFPOWER, AT_CWINIT, AT_CWAUTOCONN, AT_CWMODE1, AT_CWJAP, AT_CIPMUX};
static AT_Commands AT_SEND[] = {AT_WAKEUP, AT_HTTPCPOST, AT_SENDDATA}; 
static AT_Commands AT_LOGIN[] = {AT_WAKEUP, AT_CWSTATE};
static AT_Commands AT_WIFI_CONFIG[] = {AT_WAKEUP, AT_CWINIT, AT_CWMODE3, AT_CWAUTOCONN, AT_CWJAP, AT_CIPMUX};
static AT_Commands AT_WIFI_RECONFIG[] = {AT_WAKEUP, AT_CWMODE3, AT_CWSAP, AT_CIPMUX, AT_WEBSERVER};
static AT_Commands AT_SNTP[] = {AT_WAKEUP, AT_CIPSNTPCFG, AT_CIPSNTPTIME, AT_CIPSNTPINTV}; //RTC, then AT_RTC
uint8_t ATState;
uint8_t ATCounter = 0;
static uint8_t errorcntr = 0;
//===
static uint8_t timeoutcntr = 0;
//===
static uint32_t ESPTimeStamp = 0;
static uint32_t ESPNTPTimeStamp = 0;
static uint8_t retry = 0;

typedef struct
{
	char *ATCommand;
	bool *doneFlag;
} ATCommandsParameters;


static AT_Expectation ATExpectation = RECEIVE_EXPECTATION_OK;
static AT_Commands ATCommand = AT_WAKEUP;
static ESP_States EspState = ESP_STATE_INIT;
static AT_Mode Mode;
// static ATCommandsParameters ATCommands[ESP_AT_COMMANDS_COUNT];

void forceNTPupdate()
{
	ESPNTPTimeStamp = 0;
}

void initVariableLink(SensorType2* HT, SensorType1* VOC, SensorType1* DB, SensorType3* Sens){
	HTLink = HT;
	DBLink = DB;
	VOCLink = VOC;
	SensLink = Sens;
}

void setCharges()
{
	batteryCharge = ReadBatteryVoltage();
	solarCharge = ReadSolarVoltage();
}

void getWifiCred(void){
	ReadUint8ArrayEEprom(SSIDStartAddr, Credentials.SSID, SSIDAddrMaxSize);
	ReadUint8ArrayEEprom(PasswordStartAddr, Credentials.Password, PasswordAddrMaxSize);
	Info("The SSID is: %s", Credentials.SSID);
	Info("The Password is: %s", Credentials.Password);
}

bool PM25Active(){
	static uint8_t tempConfig[IdSize];
	static uint32_t configSum = 0;
	static bool test;
	ReadUint8ArrayEEprom(PM2ConfigAddr, tempConfig, IdSize);
	for (uint8_t i = 0; i < IdSize; i++)
	{
		configSum += tempConfig[i];
	}
	test = !(configSum == 0);
	return test;
}

bool checkName()
{
	static uint8_t nameConfig[CustomNameMaxLength];
	static uint32_t configSum = 0;
	static bool test;
	ReadUint8ArrayEEprom(CustomNameConfigAddr, nameConfig, CustomNameMaxLength);
	for (uint8_t i = 0; i < IdSize; i++)
	{
		configSum += nameConfig[i];
	}
	test = (configSum != 0);
	return test;
}


void DisableESP()
{
	EspTurnedOn = false;
	HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
}

void ESP_GetUID()
{
	uid[0] = HAL_GetUIDw0();
	uid[1] = HAL_GetUIDw1();
	uid[2] = HAL_GetUIDw2();
}

void initESPHandler(ESPHandler* ESPHand){
	ESPHandle = ESPHand;
	ESPHandle->state = ESP_STATE_INIT;
	ESP_GetUID();
}

void initUart(UART_HandleTypeDef* espUart){
	EspUart = espUart;
}

static bool ESP_Send(const char *command)
{
#ifdef LONGMESSAGES
	printf("ESP_Send: %s\r\n", command);
#else
	Debug("ESP_Send: %s", command);
#endif
	uint16_t length = strlen(command);
	HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(EspUart, (const uint8_t*)command, length);
	if (status != HAL_OK)
	{
		Error("Error in HAL_UART_Transmit_DMA");
		return false;
	}
	return true;
}

static bool ESP_Receive(uint8_t *reply, uint16_t length)
{
	//  HAL_UART_DMAStop(EspUart);
	RxComplete = false;
	bool reset = false;
	HAL_StatusTypeDef status = HAL_UART_Receive_DMA(EspUart, reply, length);
	if (status != HAL_OK)
	{
		Error("Error in HAL_UART_Receive_DMA. errorcode: %d", EspUart->ErrorCode);
		if (status & HAL_UART_ERROR_PE)
		{
			Error("Parity error in UART to ESP module");
			reset = true;
		}
		if (status & HAL_UART_ERROR_NE)
		{
			Error("Noise error in UART to ESP module");
		}
		if (status & HAL_UART_ERROR_FE)
		{
			Error("Frame error in UART to ESP module");
		}
		if (status & HAL_UART_ERROR_ORE)
		{
			Error("Overrun error in UART to ESP module");
		}
		if (status & HAL_UART_ERROR_DMA)
		{
			Error("DMA transfer error in UART to ESP module");
		}
		if (status & HAL_UART_ERROR_RTO)
		{
			Error("Receiver Timeout error in UART to ESP module");
		}
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
		if (status & HAL_UART_ERROR_INVALID_CALLBACK)
		{
			Error("Invalid Callback error in UART to ESP module");
		}
#endif
		if (reset)
		{
			// Fire all LEDs to red independent of usertoggle or power status and reboot
			TIM2->CCR1 = 0;
			TIM2->CCR3 = 4000;
			TIM2->CCR4 = 4000;
			TIM3->CCR1 = 0;
			TIM3->CCR2 = 4000;
			TIM3->CCR3 = 4000;

			HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, false);
			HAL_Delay(2000);
			HAL_NVIC_SystemReset();
		}
		RxComplete = true;
		return false;
	}
	return true;
}

// Callback for reception complete
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//  if (huart == EspUart) {
//    RxComplete = true;
//    Debug("RxComplete");
//  }
//}

// Callback for UART error
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart == EspUart)
	{
		// Handle error
		// EspState = ESP_STATE_ERROR;
		if (huart->ErrorCode != 4)
		{
			Debug("A callback error has occurred, errorcode %d", huart->ErrorCode);
		}
	}
}

void uint8ArrayToString(char *destination, uint8_t data[])
{
	for (int i = 0; i < 12; i++)
	{
		sprintf(&destination[i * 2], "%02x", data[i]);
	}
}

uint16_t CreateMessage()
{
	//  uint16_t messageLength = 0;
	static char Buffer[25];
	static uint8_t tempConfig[IdSize];
	static uint8_t humidConfig[IdSize];
	static uint8_t soundConfig[IdSize];
	static uint8_t vocConfig[IdSize];
	static uint8_t batteryConfig[IdSize];
	static uint8_t solarConfig[IdSize];
	static uint8_t noxConfig[IdSize];
	static uint8_t PM2Config[IdSize];
	static uint8_t PM10Config[IdSize];
	static uint8_t nameConfig[CustomNameMaxLength];
	ReadUint8ArrayEEprom(TempConfigAddr, tempConfig, IdSize);
	ReadUint8ArrayEEprom(HumidConfigAddr, humidConfig, IdSize);
	ReadUint8ArrayEEprom(dBaConfigAddr, soundConfig, IdSize);
	if (soundConfig[0] == 0)
	{
	ReadUint8ArrayEEprom(dBAConfigAddr, soundConfig, IdSize);
	}
	ReadUint8ArrayEEprom(VocIndexConfigAddr, vocConfig, IdSize);
	ReadUint8ArrayEEprom(BatVoltConfigAddr, batteryConfig, IdSize);
	ReadUint8ArrayEEprom(SolVoltConfigAddr, solarConfig, IdSize);
	ReadUint8ArrayEEprom(NOxIndexConfigAddr, noxConfig, IdSize);
	ReadUint8ArrayEEprom(PM2ConfigAddr, PM2Config, IdSize);
	ReadUint8ArrayEEprom(PM10ConfigAddr, PM10Config, IdSize);
	if (checkName())
	{
		ReadUint8ArrayEEprom(CustomNameConfigAddr, nameConfig, CustomNameMaxLength);
	}
	else
	{
		strncpy((char *)nameConfig, user, 5);
	}
	//(char*)nameConfig
	// get name etc from EEprom
	Debug("sensorid voor opensensmaps nox: %d", noxConfig);
	setCharges();
#ifdef LONGDATAGRAM
	memset(message, '\0', 1152);
	uint16_t index = 0;
	sprintf(&message[index], "[");
	index = strlen(message);

	uint8ArrayToString(Buffer, tempConfig);
	Debug("The temperature value = %2.2f", HTLink->measurementValue1);
	// sprintf(&message[index], "{\"name\":\"temp\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%f, \"unit\":\"C\"},", uid[2], (char *)nameConfig, Buffer, Temperature);
	sprintf(&message[index], "{\"name\":\"temp\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"C\"},", uid[2], (char *)nameConfig, Buffer, HTLink->measurementValue1);
	index = strlen(message);

	uint8ArrayToString(Buffer, humidConfig);
	// sprintf(&message[index], "{\"name\":\"humid\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%f, \"unit\":\"%%\"},", uid[2], (char *)nameConfig, Buffer, Humidity);
	sprintf(&message[index], "{\"name\":\"humid\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.1f, \"unit\":\"%%\"},", uid[2], (char *)nameConfig, Buffer, HTLink->measurementValue2);
	index = strlen(message);

	uint8ArrayToString(Buffer, soundConfig);
	sprintf(&message[index], "{\"name\":\"Sound\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"dB(A)\"},", uid[2], (char *)nameConfig, Buffer, DBLink->measurementValue);
	index = strlen(message);

	uint8ArrayToString(Buffer, batteryConfig);
	sprintf(&message[index], "{\"name\":\"battery voltage\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"V\"},", uid[2], (char *)nameConfig, Buffer, batteryCharge);
	index = strlen(message);

	if(!SensLink->active){
		Info("Sens5 not active");

		uint8ArrayToString(Buffer, vocConfig);
		sprintf(&message[index], "{\"name\":\"voc\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%d, \"unit\":\"VOCi\"},", uid[2], (char *)nameConfig, Buffer, (uint16_t)VOCLink->measurementValue);
		index = strlen(message);

		uint8ArrayToString(Buffer, solarConfig);
		sprintf(&message[index], "{\"name\":\"solar voltage\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"V\"}", uid[2], (char *)nameConfig, Buffer, solarCharge);
		index = strlen(message);
	}

	if(SensLink->active){

		uint8ArrayToString(Buffer, vocConfig);
		sprintf(&message[index], "{\"name\":\"voc\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%d, \"unit\":\"VOCi\"},", uid[2], (char *)nameConfig, Buffer, SensLink->measurementValue3/10.0f);
		index = strlen(message);

		uint8ArrayToString(Buffer, solarConfig);
		sprintf(&message[index], "{\"name\":\"solar voltage\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"V\"},", uid[2], (char *)nameConfig, Buffer, solarCharge);
		index = strlen(message);

		if(PM25Active()){
			uint8ArrayToString(Buffer, PM2Config);
			sprintf(&message[index], "{\"name\":\"PM2.5\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"PPM\"},", uid[2], (char *)nameConfig, Buffer, SensLink->measurementValue1/10.0f);
			index = strlen(message);
		}
		else{
			uint8ArrayToString(Buffer, PM10Config);
			sprintf(&message[index], "{\"name\":\"PM10\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"PPM\"},", uid[2], (char *)nameConfig, Buffer, SensLink->measurementValue2/10.0f);
			index = strlen(message);
		}

		uint8ArrayToString(Buffer, noxConfig);
		sprintf(&message[index], "{\"name\":\"NOx\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"PPM\"}", uid[2], (char *)nameConfig, Buffer, SensLink->measurementValue4/10.0f);
		index = strlen(message);
	}
#else
	memset(message, '\0', 255);
	uint16_t index = 0;
	sprintf(&message[index], "[");
	index = strlen(message);

	sprintf(&message[index], "{\"Temperature\":%.2f},", Temperature);
	index = strlen(message);

	sprintf(&message[index], "{\"Humidity\":%.1f},", Humidity);
	index = strlen(message);

	sprintf(&message[index], "{\"Sound\":%.2f},", dBA);
	index = strlen(message);

	sprintf(&message[index], "{\"VOC\":%d},", VOCIndex);
	index = strlen(message);

	sprintf(&message[index], "{\"BatteryVoltage\":%.2f},", batteryCharge);
	index = strlen(message);

	sprintf(&message[index], "{\"SolarVoltage\":%.2f}", solarCharge);
#endif
	Debug("Length of datagram: %d", index);
	index = sprintf(&message[index], "]");
	return strlen(message);
}

void resetESP(){
	HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	// Reset ESP, so we're sure that we're in the right state.
	HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, 1);
	HAL_Delay(10);
	HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_SET);
}

void StartProg()
{
	// InitWifiConfig();
	HAL_Delay(100);
	HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, GPIO_PIN_SET);
	HAL_Delay(40);
}


// PollAwake, RFPOWER and CheckRFPower necesarry when comming out of sleep mode.
//bool setCommand()

bool PollAwake()
{
	return ESP_Send("ATE0\r\n");
}

bool RFPower()
{
	return ESP_Send("AT+RFPOWER=70\r\n");
}

bool CheckRFPower()
{
	return ESP_Send("AT+RFPOWER?\r\n");
}

// Only necesarry on first init
bool ATRestore()
{
	return ESP_Send("AT+RESTORE\r\n");
}

bool CWINIT()
{
	return ESP_Send("AT+CWINIT=1\r\n");
}

bool CWMODE1()
{
	return ESP_Send("AT+CWMODE=1\r\n");
}

bool CWMODE2()
{
	return ESP_Send("AT+CWMODE=2\r\n");
}

bool CWAUTOCONN()
{
	return ESP_Send("AT+CWAUTOCONN=1\r\n");
}


#define AT_COMMAND_BUFF_LEN 150
static char atCommandBuff[AT_COMMAND_BUFF_LEN];

void appendEscapedString(const char *str)
{
	size_t pos = strlen(atCommandBuff);
	for (; *str != '\0' && pos < AT_COMMAND_BUFF_LEN - 8; str++)
	{
		if (*str == ',' || *str == '\\' || *str == '"')
		{
			atCommandBuff[pos++] = '\\';
		}
		atCommandBuff[pos++] = *str;
	}
	atCommandBuff[pos] = '\0';
}

bool CWJAP()
{
	sendCWJAP = true;
	getWifiCred();
	static char atCommandBuff[100];
	memset(atCommandBuff, '\0', 100);
	sprintf(atCommandBuff, "AT+CWJAP=\"%s\",\"%s\"\r\n", Credentials.SSID, Credentials.Password);
	uint8_t len = strlen(atCommandBuff);
	char atCommand[len + 1];
	memset(atCommand, '\0', len + 1);
	strncpy(atCommand, atCommandBuff, len);
	// SetCommandBuffer(atCommand);
	return ESP_Send(atCommandBuff);
}

bool CWMODE3()
{
	return ESP_Send("AT+CWMODE=3\r\n");
}

bool CWSTATE()
{
	return ESP_Send("AT+CWSTATE?\r\n");
}

bool CWSAP()
{
	return ESP_Send("AT+CWSAP=\"Omgevingsmonitor_Config\",\"\",11,0,1\r\n");
}

bool CIPMUX()
{
	return ESP_Send("AT+CIPMUX=0\r\n");
}

// This command sets the webserver, only necessary for first initialization.
bool WEBSERVER()
{
	return ESP_Send("AT+WEBSERVER=1,80,60\r\n");
}

// These are the commands necesarry for sending data.
bool HTTPCPOST()
{
	uint16_t length = CreateMessage();
		static uint8_t boxConfig[IdSize];
		static char Buffer[25];
		ReadUint8ArrayEEprom(BoxConfigAddr, boxConfig, IdSize);
		uint8ArrayToString(Buffer, boxConfig);
		sprintf(atCommandBuff, "AT+HTTPCPOST=%s%s/data\",%d,1,\"content-type: application/json\"\r\n", API, Buffer, length);
	return ESP_Send(atCommandBuff); // && ReadyToSendMeasurement) //Gaat niet door de retry waar door die altijd fout gaat
}

bool SENDDATA()
{
	return ESP_Send(message);
}

bool CIPSNTPCFG()
{
	if (ESP_Send("AT+CIPSNTPCFG=1,100,\"nl.pool.ntp.org\",\"time.google.com\",\"time.windows.com\"\r\n"))
	{
		HAL_Delay(1000);
		return true;
	}
	else
	{
		return false;
	}
}

bool CIPSNTPTIME()
{
	return ESP_Send("AT+CIPSNTPTIME?\r\n");
}

bool CIPSNTPINTV()
{
	return ESP_Send("AT+CIPSNTPINTV=14400\r\n");
}

#define RECEIVE_BUFFER_LEN 128

Receive_Status DMA_ProcessBuffer(uint8_t expectation)
{
	uint16_t pos = ESP_MAX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart4_rx);
	static volatile uint8_t OldPos = 0;
	Receive_Status status = RECEIVE_STATUS_INCOMPLETE;
	if (pos > ESP_MAX_BUFFER_SIZE - 1)
	{
		pos = ESP_MAX_BUFFER_SIZE - 1;
	}

	if (pos == OldPos)
	{
		if (retry > ESP_WIFI_WAIT_RESPONSE_TIME_FACTOR)
		{
			retry = 0;
			// EspState = ESP_STATE_SEND;
			if (ATCommand == AT_WAKEUP && testRound == true)
			{
				status = RECEIVE_STATUS_UNPROGGED;
			}
			if (ATCommand == AT_CWJAP)
			{
				EspState = ESP_STATE_MODE_SELECT;
			}
			else
			{
				status = RECEIVE_STATUS_TIMEOUT;
			}
		}
		else
		{
			retry++;
			ESPTimeStamp = HAL_GetTick() + ESP_WIFI_RETRY_TIME;
			status = RECEIVE_STATUS_RETRY;
		}
		return status;
	}

	// Received some data
	retry = 0;

	// Fill tempBuf with data for printing
	uint16_t j = 0;
	char tempBuf[RECEIVE_BUFFER_LEN];
	for (uint16_t i = OldPos; i != pos; i = (i + 1) % ESP_MAX_BUFFER_SIZE) {
		char ch = RxBuffer[i];
		if (ch >= ' ') {
			if (j < RECEIVE_BUFFER_LEN - 1) {
				tempBuf[j++] = ch;
			}
		}
		else {
			if (j < RECEIVE_BUFFER_LEN - 1) {
				tempBuf[j++] = '\\';
				}
			char esc = '?';
			switch (ch) {
				case '\n': esc = 'n'; break;
				case '\r': esc = 'r'; break;
				case '\t': esc = 't'; break;
				case '\b': esc = 'b'; break;
					}
			if (j < RECEIVE_BUFFER_LEN - 1) {
				tempBuf[j++] = esc;
			}
		}
	}
	tempBuf[j] = '\0';
#ifdef LONGMESSAGES
	printf("Receive DMA_ProcessBuffer: '%s'", tempBuf);
#else
	Info("Receive DMA_ProcessBuffer: '%s'", tempBuf);
#endif

	// Segment the receive data into command terminated with newline or '>'
	static char receiveBuffer[RECEIVE_BUFFER_LEN];
	static uint16_t receiveBufferPos = 0;
	for (uint16_t i = OldPos; i != pos; i = (i + 1) % ESP_MAX_BUFFER_SIZE) {
		char ch = RxBuffer[i];
		bool end_of_reply = true;
		if (ch >= ' ' && receiveBufferPos < RECEIVE_BUFFER_LEN - 1) {
			if (receiveBufferPos < RECEIVE_BUFFER_LEN - 1) {
				receiveBuffer[receiveBufferPos++] = ch;
			}
			end_of_reply = ch == '>';
		}
		if (end_of_reply && receiveBufferPos > 0) {
			receiveBuffer[receiveBufferPos] = '\0';
			receiveBufferPos = 0;
#ifdef LONGMESSAGES
			printf("Receive command: '%s'", receiveBuffer);
#else
			Info("Receive command: '%s'", receiveBuffer);
#endif

			// Process a command
			switch (expectation) {
			case RECEIVE_EXPECTATION_OK:
				if (strstr(receiveBuffer, AT_RESPONSE_OK) != 0) {
					status = RECEIVE_STATUS_OK;
				}
				break;
			case RECEIVE_EXPECTATION_READY:
				if (strstr(receiveBuffer, AT_RESPONSE_READY) != 0) {
					status = RECEIVE_STATUS_READY;
				}
				break;
			case RECEIVE_EXPECTATION_START:
				if (strstr(receiveBuffer, AT_RESPONSE_START) != 0) {
					status = RECEIVE_STATUS_START;
				}
				break;
			case RECEIVE_EXPECTATION_TIME:
				if (strstr(receiveBuffer, AT_RESPONSE_TIME_UPDATED) != 0) {
					status = RECEIVE_STATUS_TIME;
				}
				break;
			}
			if (strstr(receiveBuffer, AT_RESPONSE_ERROR) != 0 || strstr(receiveBuffer, AT_RESPONSE_FAIL) != 0) {
				status = RECEIVE_STATUS_ERROR;
			}
			else if (strstr(receiveBuffer, AT_RESPONSE_WIFI) != 0) {
				ESPHandle->connectionMade = true;

			}
			else if (ATCommand == AT_CIPSNTPTIME) {
				char *timeReply = strstr(receiveBuffer, AT_RESPONSE_CIPSNTPTIME);
				if (timeReply != NULL) {
					ParseTime(timeReply);
				}
			}
		}
	}

	OldPos = pos;

	return status;
}

void clearDMABuffer()
{
	memset(RxBuffer, '\0', ESP_MAX_BUFFER_SIZE);
}

// Compares the received status to the expected status (OK, ready, >).
bool ATCompare(Receive_Status AT_Command_Received, AT_Expectation AT_Command_Expected)
{
	bool value = false;
	if (AT_Command_Expected == RECEIVE_EXPECTATION_OK)
	{
		value = (AT_Command_Received == RECEIVE_STATUS_OK);
	}
	if (AT_Command_Expected == RECEIVE_EXPECTATION_READY)
	{
		value = (AT_Command_Received == RECEIVE_STATUS_READY);
	}
	if (AT_Command_Expected == RECEIVE_EXPECTATION_START)
	{
		value = (AT_Command_Received == RECEIVE_STATUS_START);
	}
	if (AT_Command_Expected == RECEIVE_EXPECTATION_TIME)
	{
		value = (AT_Command_Received == RECEIVE_STATUS_TIME);
	}
	return (value);
}

bool AT_Send(AT_Commands state)
{
	bool ATCommandSend = false;
	switch (state)
	{

	case AT_WAKEUP:
		if (TimestampIsReached(ESPTimeStamp))
		{
			ATCommandSend = PollAwake();
			ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME; //ESP_RESPONSE_LONG;
		}
		break;
///////////////////////////////////////////////////////////////////////////////////////////////////	
	// case AT_ECHO:
	// 	if (TimestampIsReached(ESPTimeStamp))
	// 	{
	// 		ATCommandSend = EnableEcho();
	// 		ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME; //ESP_RESPONSE_LONG;
	// 	}
	// 	break;
	// case AT_SYSLOG:
	// 	if (TimestampIsReached(ESPTimeStamp))
	// 	{
	// 		ATCommandSend = EnableSysLOG();
	// 		ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME; //ESP_RESPONSE_LONG;
	// 	}
	// 	break;
///////////////////////////////////////////////////////////////////////////////////////////////////
	case AT_SET_RFPOWER:
		Debug("Setting RF Power");
		ATCommandSend = RFPower();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CHECK_RFPOWER:
		Debug("Checking RF Power");
		ATCommandSend = CheckRFPower();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_RESTORE:
		Debug("Restoring ESP");
		ATCommandSend = ATRestore();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_LONG;
		break;

	case AT_CWINIT:
		Debug("Initializing Wi-Fi");
		ATCommandSend = CWINIT();
		ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
		break;

	case AT_CWSTATE:
		Debug("Checking current SSID");
		ATCommandSend = CWSTATE();
		ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
		break;

	case AT_CWMODE1:
		Debug("Setting to station mode");
		ATCommandSend = CWMODE1();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CWMODE2:
		Debug("Setting to station mode");
		ATCommandSend = CWMODE2();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CWAUTOCONN:
		Debug("Setting auto connect");
		ATCommandSend = CWAUTOCONN();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CWJAP:
		Debug("Connect to Wi-Fi");
		ATCommandSend = CWJAP();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_LONG;
		break;

	case AT_CWMODE3:
		Debug("SET in station/soft-ap mode");
		ATCommandSend = CWMODE3();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CWSAP:
		Debug("SET soft AP mode parameters");
		ATCommandSend = CWSAP();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CIPMUX:
		ATCommandSend = CIPMUX();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_WEBSERVER:
		ATCommandSend = WEBSERVER();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_HTTPCPOST:
		if (ESPHandle->startSend) //TimestampIsReached(HTTPCPostTimestamp)
		{
			ATCommandSend = HTTPCPOST();
			ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
		}
		else 
		{
			return false;
		}
		break;

	case AT_SENDDATA:
		Debug("Send the data");
		ATCommandSend = SENDDATA();
		ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME; // + 7000;
		break;

	case AT_CIPSNTPCFG:
		Debug("Config SNTP client");
		ATCommandSend = CIPSNTPCFG();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;

	case AT_CIPSNTPTIME:
		Debug("Get time from internet");
		ATCommandSend = CIPSNTPTIME();
		ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
		break;
	case AT_CIPSNTPINTV:
		Debug("Set the interval to timesync");
		ATCommandSend = CIPSNTPINTV();
		ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
		break;
	case AT_END:
		break;
	}

	return (ATCommandSend);
}

ESP_States ESP_Upkeep(void)
{
	static uint32_t timeoutTimer = 0;
	static Receive_Status ATReceived = RECEIVE_STATUS_INCOMPLETE;

	if ((ESPHandle->state != oldEspState) && (GetVerboseLevel() == VERBOSE_ALL))
	{
		oldEspState = ESPHandle->state;
		if (!((oldEspState == 3) && (ATCommand == AT_HTTPCPOST)))
		{
			Debug("EspState: %d ATcmd: %d Mode: %d ATExp: %d", oldEspState, ATCommand, Mode, ATExpectation);
		}
	}
	switch (ESPHandle->state)
	{

	case ESP_STATE_IDLE:
		if(!ESPHandle->done){
			ESPHandle->timeOutStamp = HAL_GetTick() + 15000;
			ESPHandle->state = ESP_STATE_INIT;
			EspTurnedOn = false;
		}
		// Waiting for wake up call.
		break;

	case ESP_STATE_INIT:
		if (!EspTurnedOn)
		{
			resetESP();
			ESPTimeStamp = HAL_GetTick() + ESP_START_UP_TIME;
			EspTurnedOn = true;
			ESPHandle->ready = true;
		}
		// Wait for ESP to be ready
		// Start reading DMA buffer for AT commands
		if (ESP_Receive(RxBuffer, ESP_MAX_BUFFER_SIZE))
		{
			ESPHandle->state = ESP_STATE_WAIT_AWAKE;
		}
		break;

	case ESP_STATE_WAIT_AWAKE:
		Debug("Waiting to process answer");
		ATReceived = DMA_ProcessBuffer(RECEIVE_EXPECTATION_READY);
		bool proceed = ATCompare(ATReceived, RECEIVE_EXPECTATION_READY);
		if (proceed || TimestampIsReached(timeoutTimer))
		{
			ESPHandle->state = ESP_STATE_MODE_SELECT;
		}
		break;

	case ESP_STATE_MODE_SELECT:   //use ESPHand.mode
		memset(ATCommandArray, AT_END, 9); //sizeof(ATCommandArray)); //9
		if (ESPHandle->mode == ESP_PROGRAM_INIT)
		{
			memcpy(ATCommandArray, AT_INIT, sizeof(AT_INIT));
			ESPHandle->state = ESP_STATE_SEND;
			ATCounter = 0;
			Mode = AT_MODE_INIT;
			ATCommand = ATCommandArray[ATCounter];
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		if (ESPHandle->mode == ESP_PROGRAM_SET_CONN)  // Still necesary?
		{
			memcpy(ATCommandArray, AT_WIFI_CONFIG, sizeof(AT_WIFI_CONFIG));
			ESPHandle->state = ESP_STATE_SEND;
			ATCounter = 0;
			Mode = AT_MODE_CONFIG;
			ATCommand = ATCommandArray[ATCounter];
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		if (ESPHandle->mode == ESP_PROGRAM_TEST)
		{
			memcpy(ATCommandArray, AT_LOGIN, sizeof(AT_LOGIN));
			ESPHandle->state = ESP_STATE_SEND;
			ATCounter = 0;
			Mode = AT_MODE_TEST;
			ATCommand = ATCommandArray[ATCounter];
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		if (ESPHandle->mode == ESP_PROGRAM_SEND)
		{
			memcpy(ATCommandArray, AT_SEND, sizeof(AT_SEND));
			ESPHandle->state = ESP_STATE_SEND;
			ATCounter = 0;
			Mode = AT_MODE_SEND;
			start = HAL_GetTick();
			// SetESPIndicator();
			ATCommand = ATCommandArray[ATCounter];
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		if (ESPHandle->mode == ESP_PROGRAM_RECONFIG)
		{
			memcpy(ATCommandArray, AT_WIFI_RECONFIG, sizeof(AT_WIFI_RECONFIG));
			Debug("Reconfig mode voor local wifi config selected");
			//DisableConnectedDevices();
			ESPHandle->state = ESP_STATE_SEND;
			ATCounter = 0;
			Mode = AT_MODE_RECONFIG;
			// SetESPIndicator();
			ATCommand = ATCommandArray[ATCounter];
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		if (ESPHandle->mode == ESP_PROGRAM_RTC)			//TIME REQ
		{
			memcpy(ATCommandArray, AT_SNTP, sizeof(AT_SNTP));
			ESPHandle->state = ESP_STATE_SEND;
			ATCounter = 0;
			Mode = AT_MODE_GETTIME;
			start = HAL_GetTick();
			// SetESPIndicator();
			ATCommand = ATCommandArray[ATCounter];
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		break;

	case ESP_STATE_SEND: 
		if(AT_Send(ATCommand))
			ESPHandle->state = ESP_STATE_WAIT_FOR_REPLY;
		break;

	case ESP_STATE_WAIT_FOR_REPLY:
		if (TimestampIsReached(ESPTimeStamp))
		{
			ATReceived = DMA_ProcessBuffer(ATExpectation);
			bool proceed = ATCompare(ATReceived, ATExpectation);
			if (ATReceived == RECEIVE_STATUS_ERROR)
			{
				if(ATCommand == AT_CWJAP){
					ErrorBlinkWiFi();
				}
				if (ATCommand == AT_SENDDATA)
				{
					ATCommand = AT_HTTPCPOST;
					ATExpectation = RECEIVE_EXPECTATION_START;
					ATCounter = 1;
				}
				ESPHandle->state = ESP_STATE_SEND;
				errorcntr++;
				if (errorcntr >= ESP_MAX_RETRANSMITIONS)
				{
					ESPTimeStamp = HAL_GetTick() + ESP_UNTIL_NEXT_SEND;
					// ResetESPIndicator();
					clearDMABuffer();
					stop = HAL_GetTick();
					Error("ESP to many retransmits, terminated after %lu ms", (stop - start));
					ESPHandle->state = ESP_STATE_DEINIT;
				}
			}
			if (ATReceived == RECEIVE_STATUS_INCOMPLETE)
			{
				ESPTimeStamp = HAL_GetTick() + 10;
			}
			if (ATReceived == RECEIVE_STATUS_TIMEOUT)
			{
				timeoutcntr++;
				Error("In ESP_STATE_WAIT_FOR_REPLY: RECEIVE_STATUS_TIMEOUT reached");
				if (timeoutcntr >= ESP_MAX_RETRANSMITIONS)
				{
					ESPTimeStamp = HAL_GetTick() + ESP_UNTIL_NEXT_SEND;
					clearDMABuffer();
					stop = HAL_GetTick();
					Error("ESP to many timeouts, terminated after %lu ms", (stop - start));
					ESPHandle->state = ESP_STATE_DEINIT;
				}
				if (ATCommand != AT_SENDDATA)
				{
					ESPHandle->state = ESP_STATE_SEND;
				}
				else
				{
					ATCommand = AT_HTTPCPOST;
					ATCounter -= 1;
					ATExpectation = RECEIVE_EXPECTATION_START;
					ESPHandle->state = ESP_STATE_SEND;
				}
			}
			if (proceed)
			{	
				ESPHandle->state = ESP_STATE_NEXT_AT;
			}
		}
 		break;

	case ESP_STATE_NEXT_AT:
		ATCounter += 1;
		ATCommand = ATCommandArray[ATCounter];
		if (ATCommand == AT_RESTORE)
		{
			ATExpectation = RECEIVE_EXPECTATION_READY;
		}
		if (ATCommand == AT_HTTPCPOST)
		{
			ATExpectation = RECEIVE_EXPECTATION_START;
		}
		if (ATCommand != AT_HTTPCPOST && ATCommand != AT_RESTORE)
		{
			ATExpectation = RECEIVE_EXPECTATION_OK;
		}
		if (ATCommand == AT_CIPSNTPCFG)
		{
			ATExpectation = RECEIVE_EXPECTATION_TIME;
		}
		ESPHandle->state = ESP_STATE_SEND;
		if (ATCommand == AT_END)
		{
			if(ESPHandle->mode == ESP_PROGRAM_INIT || ESPHandle->mode == ESP_PROGRAM_SET_CONN){
				if(!ESPHandle->connectionMade){
					ErrorBlinkWiFi();
					if(ESPHandle->mode == ESP_PROGRAM_SET_CONN){
						ESPHandle->done = true;
					}
					ESPHandle->mode = ESP_PROGRAM_SET_CONN;
				}
				else{
					ESPHandle->mode = ESP_PROGRAM_RTC;
				}
				ESPHandle->state = ESP_STATE_IDLE;
			}
			else if (ESPHandle->mode == ESP_PROGRAM_SEND)
			{
				ESPTimeStamp = HAL_GetTick();// + ESP_UNTIL_NEXT_SEND;
				// ResetESPIndicator();
				clearDMABuffer();
				stop = HAL_GetTick();
				Info("Message send in %lu ms", (stop - start));
				ResetdBAmax();
				showTime();
				ESPHandle->done = true;
				// if(lastUpdateMonth != RTC_GetMonth())
				// 	ESPHandle->mode = ESP_PROGRAM_RTC;
				ESPHandle->state = ESP_STATE_IDLE; //ESP_STATE_DEINIT;
			}
			else if (ESPHandle->mode == ESP_PROGRAM_RTC)  //TIME REQ
			{
				setTime = false;
				ESPNTPTimeStamp = HAL_GetTick() + ESP_UNTIL_NEXT_NTP;
				Info("Time synchronized by NTP, next NTP should be called at tick: %lu", ESPNTPTimeStamp);
				// ESPTimeStamp = savedESPTimeStamp;
				// ResetESPIndicator();
				clearDMABuffer();
				stop = HAL_GetTick();
				Info("Message time update in %lu ms", (stop - start));
				ESPHandle->mode = ESP_PROGRAM_SEND;
				ESPHandle->state = ESP_STATE_IDLE;
			}
			else
			{
				ESPHandle->state = ESP_STATE_IDLE;
			}
		}
		break;

	default:
		// Handle unexpected state
		Error("Something unknown went wrong with the ESP_STATE");
		ESPHandle->state = ESP_STATE_INIT;
		break;
	}
	return ESPHandle->state;
}
