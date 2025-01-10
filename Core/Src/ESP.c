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
#ifdef PUBLIC
#include "cred_pub.h"
#else
#include "cred.h"
#endif

static UART_HandleTypeDef* EspUart = NULL;
extern DMA_HandleTypeDef hdma_usart4_rx;

static volatile bool RxComplete = false;

static uint8_t RxBuffer[ESP_MAX_BUFFER_SIZE] = {0};
//static uint8_t LastATResponse[ESP_MAX_BUFFER_SIZE] = {0};
static const char user[] = "Test";
static bool testRound = true;
bool EspTurnedOn = false;
static bool InitIsDone = false;
static bool WifiReset = false;
static bool ReconfigSet = false;
static bool ConnectionMade = false;
static bool beursTest = false;
static bool beurs = false;
static bool setTime = true;
bool ESPTransmitDone = false;
static uint32_t uid[3];
static uint32_t start;
static uint32_t stop;
static uint8_t oldEspState = 255;
//static WifiConfig BeursConfig;
//static APIConfig OpenSenseApi;
//static APIConfig BeursApi;

//static bool measurementDone = false;
//static const char SSIDBeurs[] = "25ac316853";
//static const char PasswordBeurs[] = "HalloDitIsDeWifi!2024";
float Temperature = 0.0;
float Humidity = 0.0;
float batteryCharge = 0.0;
float solarCharge = 0.0;
uint16_t VOCIndex = 0;
static float dBA = 0.0;
static float airPM2 = 0.0;
static float airPM10 = 0.0;
static float airNOx = 0.0;
static char message[1152];
static const char APIBeurs[] = "\"https://deomgevingsmonitor.nl//api/set_device_data.php\"";
static const char API[] = "\"https://api.opensensemap.org/boxes/";
static AT_Commands ATCommandArray[10];
static AT_Commands AT_INIT[] = {AT_WAKEUP, AT_SET_RFPOWER, AT_CHECK_RFPOWER, AT_CWINIT, AT_CWAUTOCONN, AT_CWMODE1, AT_CIPMUX};
static AT_Commands AT_SEND[] = {AT_WAKEUP,  AT_HTTPCPOST, AT_SENDDATA};
static AT_Commands AT_BEURSTEST[] = {AT_WAKEUP, AT_CWSTATE};
static AT_Commands AT_WIFI_CONFIG[] = {AT_WAKEUP, AT_CWINIT, AT_CWMODE3, AT_CWAUTOCONN, AT_CWJAP, AT_CIPMUX};
static AT_Commands AT_WIFI_RECONFIG[] = {AT_WAKEUP, AT_CWMODE3, AT_CWSAP, AT_CIPMUX, AT_WEBSERVER};
static AT_Commands AT_SNTP[] = {AT_WAKEUP, AT_CIPSNTPCFG, AT_CIPSNTPTIME, AT_CIPSNTPINTV};
uint8_t ATState;
uint8_t ATCounter = 0;
static uint8_t errorcntr = 0;
//===
static uint8_t timeoutcntr = 0;
//===
static uint32_t ESPTimeStamp = 0;
static uint32_t ESPNTPTimeStamp = 0;
static uint32_t savedESPTimeStamp = 0;
static uint8_t retry = 0;


//static char TempBuffer[ESP_MAX_BUFFER_SIZE];      // Buffer to build up the received message
//static char CommandBuffer[ESP_TX_BUFFER_SIZE]; // Buffer to store the last sent command
//static bool CommandEchoed = false;            // Flag to indicate if the command was echoed
/* TODO: Add done function per ATCommand and save the response in there.
 * Response handle functions
*/
//static char* ATCommands[AT_COMMANDS_SIZE] = {};

typedef struct {
    char* ATCommand;
    bool* doneFlag;
} ATCommandsParameters;

static AT_Expectation ATExpectation = RECEIVE_EXPECTATION_OK;
static AT_Commands ATCommand = AT_WAKEUP;
static ESP_States EspState = ESP_STATE_INIT;
static AT_Mode Mode;
static ESP_Test TestState = ESP_TEST_INIT;
//static ATCommandsParameters ATCommands[ESP_AT_COMMANDS_COUNT];

void forceNTPupdate() {
  ESPNTPTimeStamp = 0;
}

void setESPTimeStamp(uint32_t delayms) {
  ESPTimeStamp = HAL_GetTick() + delayms;
//  ATExpectation = RECEIVE_EXPECTATION_OK;
//  ATCommand = AT_WAKEUP;
//  EspState = ESP_STATE_INIT;
}
void setCharges(){
  batteryCharge = ReadBatteryVoltage();
  solarCharge = ReadSolarVoltage() / 1000.0;
}
bool checkEEprom(){
  static uint8_t tempConfig[IdSize];
  static uint32_t configSum = 0;
  static bool test;
  ReadUint8ArrayEEprom(TempConfigAddr, tempConfig, IdSize);
  for(uint8_t i = 0; i < IdSize; i++){
    configSum += tempConfig[i];
  }
  test = (configSum == 0);
  return test;
}
bool checkName(){
  static uint8_t nameConfig[CustomNameMaxLength];
  static uint32_t configSum = 0;
  static bool test;
  ReadUint8ArrayEEprom(CustomNameConfigAddr, nameConfig, CustomNameMaxLength);
  for(uint8_t i = 0; i < IdSize; i++){
    configSum += nameConfig[i];
  }
  test = (configSum != 0);
  return test;
}
void ESP_GetHT(float temp, float humid){
  Temperature = temp;
  Humidity = humid;
}
void setHIDS(float temp, float humid){
  Temperature = temp;
  Humidity = humid;
}
void setVOC(uint16_t voc){
  VOCIndex = voc;
}
void setMic(float dB){
  dBA = dB;
}

void setPMsen50(uint16_t PM2, uint16_t PM10) {
  airPM2 = PM2 / 10.0f;
  airPM10 = PM10 / 10.0f;
}

void setPMs(uint16_t PM2, uint16_t PM10, uint16_t voc, uint16_t nox) {
  airPM2 = PM2 / 10.0f;
  airPM10 = PM10 / 10.0f;
  VOCIndex = voc / 10.0f;
  airNOx = nox / 10.0f;
}

void SetConfigMode(){
  ReconfigSet = true;
}
// Taken from firmware https://github.com/opendata-stuttgart/sensors-software/blob/master/airrohr-firmware/airrohr-firmware.ino

//struct struct_wifiInfo
//{
//  char ssid[35];
//  uint8_t encryptionType;
//  int32_t RSSI;
//  int32_t channel;
//};


//TODO: Add de-init if ESP is off. Otherwise there is going to be 3.3V on the ESP.

void ESP_GetUID(){
  uid[0] = HAL_GetUIDw0();
  uid[1] = HAL_GetUIDw1();
  uid[2] = HAL_GetUIDw2();
}
void ESP_Init(UART_HandleTypeDef* espUart) {
  EspUart = espUart;
  EspState = ESP_STATE_INIT;
  ESP_GetUID();
  beurs = checkEEprom();
}

static bool ESP_Send(uint8_t* command, uint16_t length) {
#ifdef LONGMESSAGES
  printf("ESP_Send: %s\r\n", command);
#else
  Debug("ESP_Send: %s", command);
#endif
  HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(EspUart, command, length);
  if (status != HAL_OK) {
    Error("Error in HAL_UART_Transmit_DMA");
    return false;
  }
  return true;
}
static bool ESP_Receive(uint8_t* reply, uint16_t length) {
//  HAL_UART_DMAStop(EspUart);
  RxComplete = false;
  bool reset = false;
  HAL_StatusTypeDef status = HAL_UART_Receive_DMA(EspUart, reply, length);
  if (status != HAL_OK) {
    Error("Error in HAL_UART_Receive_DMA. errorcode: %d", EspUart->ErrorCode);
    if (status & HAL_UART_ERROR_PE) {
      Error("Parity error in UART to ESP module");
      reset = true;
    }
    if (status & HAL_UART_ERROR_NE) {
      Error("Noise error in UART to ESP module");
    }
    if (status & HAL_UART_ERROR_FE) {
      Error("Frame error in UART to ESP module");
    }
    if (status & HAL_UART_ERROR_ORE) {
      Error("Overrun error in UART to ESP module");
    }
    if (status & HAL_UART_ERROR_DMA) {
      Error("DMA transfer error in UART to ESP module");
    }
    if (status & HAL_UART_ERROR_RTO) {
      Error("Receiver Timeout error in UART to ESP module");
    }
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    if (status & HAL_UART_ERROR_INVALID_CALLBACK) {
      Error("Invalid Callback error in UART to ESP module");
    }
#endif
    if (reset) {
    // Fire all LEDs to red independent of usertoggle or power status and reboot
      TIM2 -> CCR1 = 0;
      TIM2 -> CCR3 = 4000;
      TIM2 -> CCR4 = 4000;
      TIM3 -> CCR1 = 0;
      TIM3 -> CCR2 = 4000;
      TIM3 -> CCR3 = 4000;

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
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//  if (huart == EspUart) {
//    RxComplete = true;
//    Debug("RxComplete");
//  }
//}

// Callback for UART error
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  if (huart == EspUart) {
    // Handle error
    //EspState = ESP_STATE_ERROR;
    if (huart->ErrorCode != 4) {
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
uint16_t CreateMessage(bool onBeurs){
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
  ReadUint8ArrayEEprom(dBAConfigAddr, soundConfig, IdSize);
  ReadUint8ArrayEEprom(VocIndexConfigAddr, vocConfig, IdSize);
  ReadUint8ArrayEEprom(BatVoltConfigAddr, batteryConfig, IdSize);
  ReadUint8ArrayEEprom(SolVoltConfigAddr, solarConfig, IdSize);
  ReadUint8ArrayEEprom(NOxIndexConfigAddr, noxConfig, IdSize);
  ReadUint8ArrayEEprom(PM2ConfigAddr, PM2Config, IdSize);
  ReadUint8ArrayEEprom(PM10ConfigAddr, PM10Config, IdSize);
  if(checkName()){
    ReadUint8ArrayEEprom(CustomNameConfigAddr, nameConfig, CustomNameMaxLength);
  }
  else{
    strncpy((char*)nameConfig, user, 5);
  }
  //(char*)nameConfig
  //get name etc from EEprom
  Debug("sensorid voor opensensmaps nox: %d", noxConfig);
  setCharges();
#ifdef LONGDATAGRAM
  memset(message, '\0', 1152);
  uint16_t index = 0;
  sprintf(&message[index], "[");
  index = strlen(message);

  uint8ArrayToString(Buffer, tempConfig);
  sprintf(&message[index], "{\"name\":\"temp\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"C\"},", uid[2], (char*)nameConfig, Buffer, Temperature);
  index = strlen(message);

  uint8ArrayToString(Buffer, humidConfig);
  sprintf(&message[index], "{\"name\":\"humid\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.1f, \"unit\":\"%%\"},", uid[2], (char*)nameConfig, Buffer, Humidity);
  index = strlen(message);

  uint8ArrayToString(Buffer, soundConfig);
  sprintf(&message[index], "{\"name\":\"Sound\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"dB(A)\"},", uid[2], (char*)nameConfig, Buffer, dBA);
  index = strlen(message);

  uint8ArrayToString(Buffer, vocConfig);
  sprintf(&message[index], "{\"name\":\"voc\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%d, \"unit\":\"VOCi\"},", uid[2], (char*)nameConfig, Buffer, VOCIndex);
  index = strlen(message);

  if(!onBeurs){
    uint8ArrayToString(Buffer, batteryConfig);
    sprintf(&message[index], "{\"name\":\"battery voltage\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"V\"},", uid[2], (char*)nameConfig, Buffer, batteryCharge);
    index = strlen(message);

    uint8ArrayToString(Buffer, solarConfig);
    sprintf(&message[index], "{\"name\":\"Solar voltage\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"V\"},", uid[2], (char*)nameConfig, Buffer, solarCharge);
    index = strlen(message);

    uint8ArrayToString(Buffer, noxConfig);
    sprintf(&message[index], "{\"name\":\"NOx\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.1f, \"unit\":\"NOxr\"},", uid[2], (char*)nameConfig, Buffer, airNOx);
    index = strlen(message);

    uint8ArrayToString(Buffer, PM2Config);
    sprintf(&message[index], "{\"name\":\"PM2.5\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.1f, \"unit\":\"µg/m3\"},", uid[2], (char*)nameConfig, Buffer, airPM2);
    index = strlen(message);

    uint8ArrayToString(Buffer, PM10Config);
    sprintf(&message[index], "{\"name\":\"PM10\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.1f, \"unit\":\"µg/m3\"}", uid[2], (char*)nameConfig, Buffer, airPM10);
    index = strlen(message);

  }
  else{
    uint8ArrayToString(Buffer, batteryConfig);
    sprintf(&message[index], "{\"name\":\"battery\", \"id\": %ld, \"user\": \"%s\", \"sensor\": \"%s\", \"value\":%.2f, \"unit\":\"V\"}", uid[2], (char*)nameConfig, Buffer, batteryCharge);
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

//void //SetCommandBuffer(const char* command) {
//    strncpy(CommandBuffer, command, ESP_TX_BUFFER_SIZE);
//    CommandEchoed = false; // Reset the flag when a new command is sent
//}
void StartProg(){
  //InitWifiConfig();
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
 uint8_t ParseBuffer(uint8_t* buffer, uint16_t len, uint8_t expectation) {
  char tempBuf[256];
  memset(tempBuf, '\0', 256);
  char status = RECEIVE_STATUS_INCOMPLETE;
  for(uint16_t i=0; i<len; i++){
    tempBuf[i] = (char)buffer[i];
  }
  tempBuf[len] = '\0';
  if (GetVerboseLevel() == VERBOSE_ALL) {
#ifdef LONGMESSAGES
  printf("Receive ParseBuffer: %s", tempBuf );
#else
  Debug("Receive ParseBuffer: %s", tempBuf );
#endif
  }
  char * ParsePoint = 0;
  const char OK[] = AT_RESPONSE_OK;
  const char ERROR[] = AT_RESPONSE_ERROR;
  const char FAIL[] = AT_RESPONSE_FAIL;
  const char ready[] = AT_RESPONSE_READY;
  const char start[] = AT_RESPONSE_START;
  const char WIFI[] = AT_RESPONSE_WIFI;
  const char TIME[] = AT_RESPONSE_TIME_UPDATED;
  if(expectation == RECEIVE_EXPECTATION_OK){
    ParsePoint = strstr(tempBuf, OK);
  }
  if(expectation == RECEIVE_EXPECTATION_READY){
    ParsePoint = strstr(tempBuf, ready);
  }
  if(expectation == RECEIVE_EXPECTATION_START){
    ParsePoint = strstr(tempBuf, start);
  }
  if(expectation == RECEIVE_EXPECTATION_TIME){
    ParsePoint = strstr(tempBuf, TIME);
  }

  char *ParsePoint2 = strstr(tempBuf, ERROR);
  char *ParsePoint3 = strstr(tempBuf, WIFI);
  char *ParsePoint4 = strstr(tempBuf, SSIDBeurs);
  char *ParsePoint5 = strstr(tempBuf, FAIL);
  if(len > 1 ){
    if(ParsePoint != 0 && *ParsePoint == 'O'){
// call function to update time in realtimeclock.c
      status = RECEIVE_STATUS_OK;
      if ( ATCommand == AT_CIPSNTPTIME ) {
        if ((len == 43) && (tempBuf[33] == '2' )) {  // validity check
          ParseTime(tempBuf);
        }
        else {
          Error("Error getting time");
          return RECEIVE_STATUS_TIMEOUT;
        }
      }
    }
    if(ParsePoint != 0 && *ParsePoint == 'r') {
      status = RECEIVE_STATUS_READY;
    }
    if(ParsePoint != 0 && *ParsePoint == '>') {
      status = RECEIVE_STATUS_START;
    }
    if(ParsePoint != 0 && *ParsePoint == '+') {
      status = RECEIVE_STATUS_TIME;
    }
    if((ParsePoint2 != 0 && *ParsePoint2 == 'E') || (ParsePoint5 != 0 && *ParsePoint5 == 'F')) {
      status = RECEIVE_STATUS_ERROR;
    }
    if(ParsePoint3 != 0 && *ParsePoint3 == 'W'){
      ConnectionMade = true;
    }
    if(ParsePoint4 != 0 && *ParsePoint4 == '2'){
      beurs = true;
    }
  }
  return(status);

}
 //PollAwake, RFPOWER and CheckRFPower necesarry when comming out of sleep mode.
bool PollAwake(){
  char* atCommand = "ATE0\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool RFPower(){
  char* atCommand = "AT+RFPOWER=70\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CheckRFPower(){
  char* atCommand = "AT+RFPOWER?\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
//Only necesarry on first init
bool ATRestore(){
  char* atCommand = "AT+RESTORE\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWINIT(){
  char* atCommand = "AT+CWINIT=1\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWMODE1(){
  char* atCommand = "AT+CWMODE=1\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWMODE2(){
  char* atCommand = "AT+CWMODE=2\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWAUTOCONN(){
  char* atCommand = "AT+CWAUTOCONN=1\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWJAP(){
  beursTest = true;
  char atCommandBuff[100];
  memset(atCommandBuff, '\0', 100);
  sprintf(atCommandBuff, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSIDBeurs, PasswordBeurs);
  uint8_t len = strlen(atCommandBuff);
  char atCommand[len+1];
  memset(atCommand, '\0', len+1);
  strncpy(atCommand, atCommandBuff, len);
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, len)) {
    return true;
  }
  else{
    return false;
  }
}
bool CWMODE3(){
  char* atCommand = "AT+CWMODE=3\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWSTATE(){
  char* atCommand = "AT+CWSTATE?\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWSAP(){
  char* atCommand = "AT+CWSAP=\"WOTS_Config\",\"\",11,0,1\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CIPMUX(){
  char* atCommand = "AT+CIPMUX=0\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
//This command sets the webserver, only necessary for first initialization.
bool WEBSERVER(){
  char* atCommand = "AT+WEBSERVER=1,80,60\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
//These are the commands necesarry for sending data.
bool HTTPCPOST(){
  char atCommandBuff[256];
  memset(atCommandBuff, '\0', 256);
  uint16_t length = CreateMessage(beurs);
  if(beurs){
    sprintf(atCommandBuff, "AT+HTTPCPOST=%s,%d,1,\"content-type: application/json\"\r\n", APIBeurs, length);
  }
  else{
    static uint8_t boxConfig[IdSize];
    static char Buffer[25];
    ReadUint8ArrayEEprom(BoxConfigAddr, boxConfig, IdSize);
    uint8ArrayToString(Buffer, boxConfig);
    sprintf(atCommandBuff, "AT+HTTPCPOST=%s%s/data\",%d,1,\"content-type: application/json\"\r\n", API, Buffer, length);
  }
  uint16_t len = strlen(atCommandBuff);
  if(ESP_Send((uint8_t*)atCommandBuff, len)){
    return true;
  }
  else{
    return false;
  }
}
bool SENDDATA(){
  uint16_t len = strlen(message);
  if(ESP_Send((uint8_t*)message, len)) {
    return true;
  }
  else{
    return false;
  }
}
bool SLEEP(){
  char* atCommand = "AT+GSLP=30000\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CIPSNTPCFG(){
  char* atCommand = "AT+CIPSNTPCFG=1,100,\"nl.pool.ntp.org\",\"time.google.com\",\"time.windows.com\"\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    HAL_Delay(1000);
    return true;
  }
  else{
    return false;
  }
}
bool CIPSNTPTIME(){
  char* atCommand = "AT+CIPSNTPTIME?\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CIPSNTPINTV(){
  char* atCommand = "AT+CIPSNTPINTV=14400\r\n";
  //SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}

Receive_Status DMA_ProcessBuffer(uint8_t expectation) {
    uint16_t pos = ESP_MAX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart4_rx);
    static volatile uint8_t OldPos = 0;
    static volatile uint8_t TempPos = 0;
    Receive_Status status = RECEIVE_STATUS_INCOMPLETE;
    if(pos > ESP_MAX_BUFFER_SIZE) {
      pos = ESP_MAX_BUFFER_SIZE;
    }
    if(pos == OldPos){
      if(retry > ESP_WIFI_WAIT_RESPONSE_TIME_FACTOR){
        retry = 0;
        //EspState = ESP_STATE_SEND;
        if(ATCommand == AT_WAKEUP && testRound == true){
          status = RECEIVE_STATUS_UNPROGGED;
        }
        if(ATCommand == AT_CWJAP){
          EspState = ESP_STATE_MODE_SELECT;
        }
        else{
          status = RECEIVE_STATUS_TIMEOUT;
        }
      }
     else{
       retry ++;
       ESPTimeStamp = HAL_GetTick() + ESP_WIFI_RETRY_TIME;
       status = RECEIVE_STATUS_RETRY;
      }
    }
    if (pos != OldPos) {
      retry = 0;
      if(TempPos == OldPos){
        TempPos = pos;
        status = RECEIVE_STATUS_LOOP;
      }
      else{
        if(TempPos != pos){
          TempPos = pos;
          status = RECEIVE_STATUS_LOOP;
        }
        else{
          if (pos > OldPos) {
              status = ParseBuffer(&RxBuffer[OldPos], (pos - OldPos), expectation);
          }
          else {
              // Buffer wrap-around
              status = ParseBuffer(&RxBuffer[OldPos], ESP_MAX_BUFFER_SIZE - OldPos, expectation);
              if (pos > 0) {
                  status = ParseBuffer(&RxBuffer[0], pos, expectation);
              }
          }
//          Debug("DMA ESP RxBuffer OldPos: %d, pos: %d", OldPos, pos);
          OldPos = pos;
        }
      }
    }
    return status;
}

void clearDMABuffer(){
  memset(RxBuffer, '\0', ESP_MAX_BUFFER_SIZE);
}
//Compares the received status to the expected status (OK, ready, >).
bool ATCompare(uint8_t AT_Command_Received, uint8_t AT_Command_Expected){
  bool value = false;
  if(AT_Command_Expected == RECEIVE_EXPECTATION_OK){
    value = (AT_Command_Received == RECEIVE_STATUS_OK);
  }
  if(AT_Command_Expected == RECEIVE_EXPECTATION_READY){
    value = (AT_Command_Received == RECEIVE_STATUS_READY);
  }
  if(AT_Command_Expected == RECEIVE_EXPECTATION_START){
    value = (AT_Command_Received == RECEIVE_STATUS_START);
  }
  if(AT_Command_Expected == RECEIVE_EXPECTATION_TIME){
    value = (AT_Command_Received == RECEIVE_STATUS_TIME);
  }
  return(value);
}

bool AT_Send(AT_Commands state){
  bool ATCommandSend = false;
  switch (state){

  case AT_WAKEUP:
  if(TimestampIsReached(ESPTimeStamp)){
    ATCommandSend = PollAwake();
    ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_LONG;
  }
  break;

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
    ATCommandSend = HTTPCPOST();
    ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
    break;

  case AT_SENDDATA:
    Debug("Send the data");
    ATCommandSend = SENDDATA();
    ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME; // + 7000;
    break;

  case AT_SLEEP:
    Debug("Setting ESP in sleep mode for 5 min");
    ATCommandSend = SLEEP();
    ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
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

  return(ATCommandSend);
}

void ESP_WakeTest(void) {
  bool ATSend = false;
  static Receive_Status ATReceived = RECEIVE_STATUS_INCOMPLETE;
  switch (TestState){

    case ESP_TEST_INIT:
//      Debug("TestState: ESP_TEST_INIT");
      if(!EspTurnedOn){
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
        ESPTimeStamp = HAL_GetTick() + ESP_START_UP_TIME;
        EspTurnedOn = true;
      }
      if(ESP_Receive(RxBuffer, ESP_MAX_BUFFER_SIZE)) {
        TestState = ESP_TEST_SEND;
      }
      break;

    case ESP_TEST_SEND:
//      Debug("TestState: ESP_TEST_SEND");
      if(TimestampIsReached(ESPTimeStamp)){
        ATSend = AT_Send(ATCommand);
        if(ATSend){
          TestState = ESP_TEST_RECEIVE;
        }
      }
      break;

    case ESP_TEST_RECEIVE:
//      Debug("TestState: ESP_TEST_RECEIVE");
      if(TimestampIsReached(ESPTimeStamp)){
        ATReceived = DMA_ProcessBuffer(ATExpectation);
        bool proceed = ATCompare(ATReceived, ATExpectation);
        if(ATReceived == RECEIVE_STATUS_ERROR){
          TestState = ESP_TEST_SEND;
        }
        if(ATReceived == RECEIVE_STATUS_RETRY){
          //TestState = ESP_TEST_SEND;
          //ESPTimeStamp = HAL_GetTick() + 2*ESP_START_UP_TIME;
        }
        if(ATReceived == RECEIVE_STATUS_UNPROGGED){
          StartProg();
          TestState = ESP_TEST_BOOT;
        }
        if(ATReceived == RECEIVE_STATUS_INCOMPLETE){
          ESPTimeStamp = HAL_GetTick() + 50;
          TestState = ESP_TEST_SEND;
        }
        if(proceed){
          TestState = ESP_TEST_VALIDATE;
        }
      }
      break;

    case ESP_TEST_VALIDATE:
//      Debug("TestState: ESP_TEST_VALIDATE");
      //Set measurement completed
      TIM3 -> CCR1 = LED_OFF;
      TIM3 -> CCR2 = Calculate_LED_ON();
      TIM3 -> CCR3 = LED_OFF;
      TestState = ESP_TEST_DEINIT;

      break;

    case ESP_TEST_DEINIT:
//      Debug("TestState: ESP_TEST_DEINIT");
      testRound = false;
      EspTurnedOn = false;
      HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, 0);
      // Reset ESP, so we're sure that we're in the right state.
      SetESPMeasurementDone();
      break;

    default:
//      Debug("TestState: ESP_TEST_INIT");
      TestState = ESP_TEST_INIT;
      break;

    case ESP_TEST_BOOT:
//      Debug("TestState: ESP_TEST_BOOT");
      TIM3 -> CCR1 = 4000;
      TIM3 -> CCR2 = 4000;
      TIM3 -> CCR3 = Calculate_LED_ON();
      //WAIT FOR RESET;
      break;
  }
}

ESP_States ESP_Upkeep(void) {
  bool ATSend = false;
  static uint32_t timeoutTimer = 0;
  static Receive_Status ATReceived = RECEIVE_STATUS_INCOMPLETE;

  if ((EspState != oldEspState) && (GetVerboseLevel() == VERBOSE_ALL)) {
    oldEspState = EspState;
    if (!((oldEspState == 3) && (ATCommand == AT_HTTPCPOST)) ) {
      Debug("EspState: %d ATcmd: %d Mode: %d ATExp: %d", oldEspState, ATCommand, Mode, ATExpectation);
    }
  }
  switch (EspState) {
    case ESP_STATE_OFF:
      // Turning off the ESP
      // Disable UART

//      EspTurnedOn = false;
      EspState = ESP_STATE_IDLE;
      break;

    case ESP_STATE_IDLE:
      // Waiting for wake up call.
      break;

    case ESP_STATE_INIT:
      if(!EspTurnedOn){
        HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        // Reset ESP, so we're sure that we're in the right state.
        HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, 1);
        HAL_Delay(1);
        HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_SET);
        ESPTimeStamp = HAL_GetTick() + ESP_START_UP_TIME;
        EspTurnedOn = true;
      }
      // Wait for ESP to be ready
      // Start reading DMA buffer for AT commands
      if(ESP_Receive(RxBuffer, ESP_MAX_BUFFER_SIZE)) {
        EspState = ESP_STATE_WAIT_AWAKE;
        timeoutTimer = HAL_GetTick() + 2000;
      }
      break;

    case ESP_STATE_WAIT_AWAKE:
        ATReceived = DMA_ProcessBuffer(RECEIVE_EXPECTATION_READY);
        bool proceed = ATCompare(ATReceived, RECEIVE_EXPECTATION_READY);
        if(proceed || TimestampIsReached(timeoutTimer)){
          EspState = ESP_STATE_MODE_SELECT;
        }
        break;

    case ESP_STATE_MODE_SELECT:
      memset(ATCommandArray, AT_END, 9);
      if(!InitIsDone || WifiReset){
        memcpy(ATCommandArray, AT_INIT, 7);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_INIT;
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(InitIsDone && !ConnectionMade){
        memcpy(ATCommandArray, AT_WIFI_CONFIG, 6);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_CONFIG;
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(InitIsDone && ConnectionMade && !beursTest){
        memcpy(ATCommandArray, AT_BEURSTEST, 2);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_TEST;
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(InitIsDone && ConnectionMade && beursTest && !setTime){
        memcpy(ATCommandArray, AT_SEND, 3);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_SEND;
        start = HAL_GetTick();
        SetESPIndicator();
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(ReconfigSet){
        memcpy(ATCommandArray, AT_WIFI_RECONFIG, 5);
        Debug("Reconfig mode voor local wifi config selected");
        DisableConnectedDevices();
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_RECONFIG;
        SetESPIndicator();
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(InitIsDone && ConnectionMade && beursTest && setTime){
        memcpy(ATCommandArray, AT_SNTP, 4);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_GETTIME;
        start = HAL_GetTick();
        SetESPIndicator();
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
    break;

    case ESP_STATE_SEND:
        ATSend = AT_Send(ATCommand);
        if(ATSend){
          EspState = ESP_STATE_WAIT_FOR_REPLY;
        }
    break;

    case ESP_STATE_WAIT_FOR_REPLY:
      if(TimestampIsReached(ESPTimeStamp)){
        ATReceived = DMA_ProcessBuffer(ATExpectation);
        bool proceed = ATCompare(ATReceived, ATExpectation);
        if(ATReceived == RECEIVE_STATUS_ERROR){
          if(ATCommand == AT_SENDDATA){
            ATCommand = AT_HTTPCPOST;
            ATExpectation = RECEIVE_EXPECTATION_START;
            ATCounter = 1;
          }
          EspState = ESP_STATE_SEND;
          errorcntr++;
          if (errorcntr >= ESP_MAX_RETRANSMITIONS) {
            ESPTimeStamp = HAL_GetTick() + ESP_UNTIL_NEXT_SEND;
            ESPTransmitDone = true;
            ResetESPIndicator();
            clearDMABuffer();
            stop = HAL_GetTick();
            Error("ESP to many retransmits, terminated after %lu ms", (stop-start));
            EspState = ESP_STATE_DEINIT;
          }
        }
        if(ATReceived == RECEIVE_STATUS_INCOMPLETE){
          ESPTimeStamp = HAL_GetTick() + 10;
        }
        if(ATReceived == RECEIVE_STATUS_LOOP){
          ESPTimeStamp = HAL_GetTick() + 10;
        }
        if(ATReceived == RECEIVE_STATUS_TIMEOUT){
          timeoutcntr++;
          Error("In ESP_STATE_WAIT_FOR_REPLY: RECEIVE_STATUS_TIMEOUT reached");
          if (timeoutcntr >= ESP_MAX_RETRANSMITIONS) {
            ESPTimeStamp = HAL_GetTick() + ESP_UNTIL_NEXT_SEND;
            ESPTransmitDone = true;
            ResetESPIndicator();
            clearDMABuffer();
            stop = HAL_GetTick();
            Error("ESP to many timeouts, terminated after %lu ms", (stop-start));
            // TODO hier gaat iets fout, de verzending herstart niet meer
            // in log alleen nog D [01039053] EspState: 4 ATcmd: 20 Mode: 2 ATExp: 0
            EspState = ESP_STATE_DEINIT;
            // mogelijke oplossing door deze twee regels te verwijderen
            // ATCommand = AT_END;
            // ATExpectation = RECEIVE_EXPECTATION_OK;
          }
          if(ATCommand != AT_SENDDATA){
            EspState = ESP_STATE_SEND;
          }
          else{
            ATCommand = AT_HTTPCPOST;
            ATCounter -= 1;
            ATExpectation = RECEIVE_EXPECTATION_START;
            EspState = ESP_STATE_SEND;
          }
        }
        if(proceed){
          EspState = ESP_STATE_NEXT_AT;
        }
      }
      break;

    case ESP_STATE_NEXT_AT:
      ATCounter += 1;
      ATCommand = ATCommandArray[ATCounter];
      if(ATCommand == AT_RESTORE){
         ATExpectation = RECEIVE_EXPECTATION_READY;
      }
      if(ATCommand == AT_HTTPCPOST){
        ATExpectation = RECEIVE_EXPECTATION_START;
      }
      if(ATCommand != AT_HTTPCPOST && ATCommand != AT_RESTORE){
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(ATCommand == AT_CIPSNTPCFG){
         ATExpectation = RECEIVE_EXPECTATION_TIME;
      }
      EspState = ESP_STATE_SEND;
      if(ATCommand == AT_END){
        if(Mode == AT_MODE_SEND){
          ESPTimeStamp = HAL_GetTick() + ESP_UNTIL_NEXT_SEND;
          ResetESPIndicator();
          clearDMABuffer();
          stop = HAL_GetTick();
          Info("Message send in %lu ms", (stop-start));
          ResetdBAmax();
          showTime();
          ESPTransmitDone = true;
          EspState = ESP_STATE_DEINIT;
        }
        else if (Mode == AT_MODE_GETTIME) {
            setTime = false;
            ESPNTPTimeStamp = HAL_GetTick()+ESP_UNTIL_NEXT_NTP;
            Info("Time synchronized by NTP, next NTP should be called at tick: %lu", ESPNTPTimeStamp);
            ESPTimeStamp = savedESPTimeStamp;
            ResetESPIndicator();
            clearDMABuffer();
            stop = HAL_GetTick();
            Info("Message time update in %lu ms", (stop-start));
            EspState = ESP_STATE_DEINIT;
            Mode = AT_MODE_SEND;
          }
        else{
          EspState = ESP_STATE_RESET;
        }
      }
    break;

    case ESP_STATE_DEINIT:
      EspTurnedOn = false;
      HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
      HAL_Delay(1);
      HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
      HAL_Delay(1);
      HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, 0);
      EspState = ESP_STATE_RESET;
      HAL_Delay(1);
      errorcntr = 0;
      timeoutcntr = 0;
      break;

    case ESP_STATE_RESET:
      if(TimestampIsReached(ESPTimeStamp) || ReconfigSet){
        ESPTransmitDone = false;
        if(Mode == AT_MODE_INIT){
          InitIsDone = true;
          EspState = ESP_STATE_MODE_SELECT;
        }
        if(Mode == AT_MODE_CONFIG){
          ConnectionMade = true;
          beurs = true;
          EspState = ESP_STATE_MODE_SELECT;
        }
        if(Mode == AT_MODE_SEND){
          EspState = ESP_STATE_INIT;
        }
        if(Mode == AT_MODE_RECONFIG){
          EspState = ESP_STATE_CONFIG;
          Info("Do nothing until reset");
        }
        if(Mode == AT_MODE_TEST){
          EspState = ESP_STATE_MODE_SELECT;
          beursTest = true;
        }
      }
      else if (TimestampIsReached(ESPNTPTimeStamp)) {
        if(Mode == AT_MODE_SEND ) {
            Mode = AT_MODE_GETTIME;
//          EspState = ESP_STATE_MODE_SELECT;
         EspState = ESP_STATE_INIT;
         savedESPTimeStamp = ESPTimeStamp;
         setTime = true;
 //        Debug("setTime to true");
        }
      }
      break;

    case ESP_STATE_CONFIG:
      Info("Do nothing until reset");
      Process_PC_Config(GetUsbRxPointer());
      break;

    case ESP_STATE_ERROR:
      // Handle error state
      Error("ESP Error occurred");
      EspState = ESP_STATE_INIT;
      break;

    default:
      // Handle unexpected state
      Error("Something unknown went wrong with the ESP_STATE");
      EspState = ESP_STATE_ERROR;
      break;
  }
  return EspState;
}
