/*
 * ESP.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#include "ESP.h"
#include <String.h>
#include <stdio.h>

static UART_HandleTypeDef* EspUart = NULL;
extern DMA_HandleTypeDef hdma_usart4_rx;


static volatile bool RxComplete = false;

static uint8_t RxBuffer[ESP_MAX_BUFFER_SIZE] = {0};
//static uint8_t LastATResponse[ESP_MAX_BUFFER_SIZE] = {0};
static bool testRound = true;
static bool EspTurnedOn = false;
static bool InitIsDone = false;
static bool WifiReset = false;
static bool ReconfigSet = false;
static bool ConnectionMade = false;
static uint32_t uid[3];

static WifiConfig BeursConfig;
//static APIConfig OpenSenseApi;
static APIConfig BeursApi;

//static bool measurementDone = false;
//char SSID[] = "KITT-guest";
//char Password[] = "ZonderSnoerCommuniceren053";
char SSIDBeurs[] = "25ac316853";
char PasswordBeurs[] = "HalloDitIsDeWifi!2024";
float Temperature = 0;
float Humidity = 0;
float batteryCharge = 0;
float solarCharge = 0;
uint16_t VOCIndex = 0;
float dBC = 0;
static char messagePart1[128];
static char messagePart2[128];
static char messagePart3[128];
static char messagePart4[128];
static char messagePart5[128];
static char APIBeurs[] = "\"https://deomgevingsmonitor.nl//api/set_device_data.php\"";
//static char API[] = "\"https://api.opensensemap.org/boxes/66c7394026df8b0008c359a4/data\"";
static char sensorID1[] = "\"66c7394026df8b0008c359a5\"";
static char sensorID2[] = "\"66c7394026df8b0008c359a6\"";
static char sensorID3[] = "\"66c7394026df8b0008c359a7\"";
static char sensorID4[] = "\"66c7394026df8b0008c359a8\"";
static char sensorID5[] = "\"66c7394026df8b0008c359a9\"";
static char userID[] = "\"55\"";
static char user[] = "\"Piet\"";
static AT_Commands ATCommandArray[10];
static AT_Commands AT_INIT[] = {AT_WAKEUP, AT_SET_RFPOWER, AT_CHECK_RFPOWER, AT_CWINIT, AT_CWMODE3, AT_CIPMUX, AT_WEBSERVER};
static AT_Commands AT_SEND[] = {AT_WAKEUP,  AT_HTTPCPOST, AT_SENDDATA};
static AT_Commands AT_WIFI_CONFIG[] = {AT_WAKEUP, AT_CWINIT, AT_CWMODE1, AT_CWAUTOCONN, AT_CWJAP, AT_CIPMUX};
static AT_Commands AT_WIFI_RECONFIG[] = {AT_WAKEUP, AT_RESTORE, AT_CWMODE3, AT_CWSAP};
uint8_t ATState;
uint8_t ATCounter = 0;
//static bool StartUpDone = false;
//static bool ResponseFound = false;
static volatile uint8_t OldPos = 0;
//static uint16_t TempIndex = 0;
//static uint16_t ATCommandIndex = 0;
static uint32_t ESPTimeStamp = 0;
static uint8_t retry = 0;


//static char TempBuffer[ESP_MAX_BUFFER_SIZE];      // Buffer to build up the received message
static char CommandBuffer[ESP_TX_BUFFER_SIZE]; // Buffer to store the last sent command
static bool CommandEchoed = false;            // Flag to indicate if the command was echoed
/* TODO: Add done function per ATCommand and save the response in there.
 * Response handle functions
*/
//static char* ATCommands[AT_COMMANDS_SIZE] = {};

typedef struct {
    char* ATCommand;
    bool* doneFlag;
} ATCommandsParameters;
void setCharges(float battery, float solar){
  batteryCharge = battery;
  solarCharge = solar;
}
void setMeasurement(float temp, float humid, uint16_t voc){
  Temperature = temp;
  Humidity = humid;
  VOCIndex = voc;
}
void setMic(float dB){
  dBC = dB;
}
// Taken from firmware https://github.com/opendata-stuttgart/sensors-software/blob/master/airrohr-firmware/airrohr-firmware.ino

struct struct_wifiInfo
{
  char ssid[35];
  uint8_t encryptionType;
  int32_t RSSI;
  int32_t channel;
};

static AT_Expectation ATExpectation = RECEIVE_EXPECTATION_OK;
static AT_Commands ATCommand = AT_WAKEUP;
static ESP_States EspState = ESP_STATE_INIT;
static AT_Mode Mode;
static ESP_Test TestState = ESP_TEST_INIT;
//static ATCommandsParameters ATCommands[ESP_AT_COMMANDS_COUNT];

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
}

static bool ESP_Send(uint8_t* command, uint16_t length) {
  HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(EspUart, command, length);
  if (status != HAL_OK) {
    Debug("Error in HAL_UART_Transmit_DMA");
    return false;
  }
  return true;
}
static bool ESP_Receive(uint8_t* reply, uint8_t length) {
//  HAL_UART_DMAStop(EspUart);
  RxComplete = false;
  HAL_StatusTypeDef status = HAL_UART_Receive_DMA(EspUart, reply, length);
  if (status != HAL_OK) {
    Debug("Error in HAL_UART_Receive_DMA.");
    RxComplete = true;
    return false;
  }
  return true;
}

// Callback for reception complete
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == EspUart) {
    RxComplete = true;
    Debug("RxComplete");
  }
}

// Callback for UART error
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  if (huart == EspUart) {
    // Handle error
    EspState = ESP_STATE_ERROR;
  }
}
uint16_t CreateMessage(){
  uint16_t messageLength = 0;
  sprintf(messagePart1, "\"name\":\"temp\", \"id\":\"55\", \"user\":\"piet\", \"sensor\": %s, \"value\":%3.2f, \"unit\": \"graden\"", sensorID1, Temperature);
  messageLength += strlen(messagePart1);
  sprintf(messagePart2, "\"name\":\"humid\", \"id\":\"55\", \"user\":\"piet\", \"sensor\": %s, \"value\":%3.2f, \"unit\": \"%%\"", sensorID2, Humidity);
  messageLength += strlen(messagePart2);
  sprintf(messagePart3, "\"name\":\"Sound\", \"id\":\"55\", \"user\":\"piet\", \"sensor\": %s, \"value\":%3.2f, \"unit\": \"dBC\"", sensorID3, dBC);
  messageLength += strlen(messagePart3);
  sprintf(messagePart4, "\"name\":\"voc\", \"id\":\"55\", \"user\":\"piet\", \"sensor\": %s, \"value\":%d, \"unit\": \"VOC index\"", sensorID4, VOCIndex);
  messageLength += strlen(messagePart4);
  sprintf(messagePart5, "\"name\":\"battery\", \"id\":\"55\", \"user\":\"piet\", \"sensor\": %s, \"value\":%3.2f, \"unit\": \"Volt\"", sensorID5, batteryCharge);
  messageLength += strlen(messagePart5);
  messageLength += 20;
  return(messageLength);
}

void SetCommandBuffer(const char* command) {
    strncpy(CommandBuffer, command, ESP_TX_BUFFER_SIZE);
    CommandEchoed = false; // Reset the flag when a new command is sent
}
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
  char tempBuf[len+1];
  char status = RECEIVE_STATUS_INCOMPLETE;
  for(uint16_t i=0; i<len; i++){
    tempBuf[i] = (char)buffer[i];
  }
  tempBuf[len] = '\0';
  char TestChar = 'N';
  char * ParsePoint;
  char * ParsePoint2;
  char * ParsePoint3;
  const char OK[] = AT_RESPONSE_OK;
  const char ERROR[] = AT_RESPONSE_ERROR;
  const char ready[] = AT_RESPONSE_READY;
  const char start[] = AT_RESPONSE_START;
  const char WIFI[] = AT_RESPONSE_WIFI;
  if(expectation == RECEIVE_EXPECTATION_OK){
    ParsePoint = strstr(tempBuf, OK);
  }
  if(expectation == RECEIVE_EXPECTATION_READY){
    ParsePoint = strstr(tempBuf, ready);
  }
  if(expectation == RECEIVE_EXPECTATION_START){
    ParsePoint = strstr(tempBuf, start);
  }
  ParsePoint2 = strstr(tempBuf, ERROR);
  ParsePoint3 = strstr(tempBuf, WIFI);
  if(len > 1 ){
    TestChar = *ParsePoint;
    if(TestChar == 'O'){
      status = RECEIVE_STATUS_OK;
    }
    if(TestChar == 'r'){
      status = RECEIVE_STATUS_READY;
    }
    if(TestChar == '>'){
      status = RECEIVE_STATUS_START;
    }
    TestChar = *ParsePoint2;
    if(TestChar == 'E'){
      status = RECEIVE_STATUS_ERROR;
    }
    TestChar = *ParsePoint3;
    if(TestChar == 'W'){
      ConnectionMade = true;
    }
  }
  return(status);

}
 //PollAwake, RFPOWER and CheckRFPower necesarry when comming out of sleep mode.
bool PollAwake(){
  char* atCommand = "ATE0\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool RFPower(){
  char* atCommand = "AT+RFPOWER=70\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CheckRFPower(){
  char* atCommand = "AT+RFPOWER?\r\n";
  SetCommandBuffer(atCommand);
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
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWINIT(){
  char* atCommand = "AT+CWINIT=1\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWMODE1(){
  char* atCommand = "AT+CWMODE=1\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWAUTOCONN(){
  char* atCommand = "AT+CWAUTOCONN=1\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWJAP(){
  char atCommandBuff[100];
  memset(atCommandBuff, '\0', 100);
  sprintf(atCommandBuff, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSIDBeurs, PasswordBeurs);
  uint8_t len = strlen(atCommandBuff);
  char atCommand[len+1];
  memset(atCommand, '\0', len+1);
  strncpy(atCommand, atCommandBuff, len);
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, len)) {
    return true;
  }
  else{
    return false;
  }
}
bool CWMODE3(){
  char* atCommand = "AT+CWMODE=3\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CWSAP(){
  char* atCommand = "AT+CWSAP=\"WOTS_Config\",\"\",11,0,1\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
bool CIPMUX(){
  char* atCommand = "AT+CIPMUX=0\r\n";
  SetCommandBuffer(atCommand);
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
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}
//These are the commands necesarry for sending data.
bool HTTPCPOST(){
  char atCommandBuff[600];
  uint16_t length = CreateMessage();
  sprintf(atCommandBuff, "AT+HTTPCPOST=%s,%d,1,\"content-type: application/json\"\r\n", APIBeurs, length);
  uint8_t len = strlen(atCommandBuff);
  char atCommand[len+1];
  strncpy(atCommand, atCommandBuff, len);
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, len)){
    return true;
  }
  else{
    return false;
  }
}
bool SENDDATA(){
  char atCommandBuff[656];
  memset(atCommandBuff, '\0', 656);
  sprintf(atCommandBuff,"[{%s}, {%s}, {%s}, {%s}, {%s}]", messagePart1, messagePart2, messagePart3, messagePart4, messagePart5);
  uint16_t len = strlen(atCommandBuff);
  char atCommand[len+1];
  memset(atCommand, '\0', len+1);
  strncpy(atCommand, atCommandBuff, len);
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, len)) {
    return true;
  }
  else{
    return false;
  }
}
bool SLEEP(){
  char* atCommand = "AT+GSLP=30000\r\n";
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
    return true;
  }
  else{
    return false;
  }
}

uint8_t DMA_ProcessBuffer(uint8_t expectation) {
    uint8_t pos = ESP_MAX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart4_rx);
    uint8_t status = RECEIVE_STATUS_INCOMPLETE;
    if(pos > ESP_MAX_BUFFER_SIZE) {
      pos = ESP_MAX_BUFFER_SIZE;
    }
    if(pos == OldPos){
      if(retry >4){
        retry = 0;
        //EspState = ESP_STATE_SEND;
        if(ATCommand == AT_WAKEUP && testRound == true){
          status = RECEIVE_STATUS_UNPROGGED;
        }
        else{
          status = RECEIVE_STATUS_TIMEOUT;
        }
      }
     else{
       retry ++;
       ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
       status = RECEIVE_STATUS_RETRY;
      }
    }
    if (pos != OldPos) {
      retry = 0;
        if (pos > OldPos) {
            // Direct parsing
            status = ParseBuffer(&RxBuffer[OldPos], (pos - OldPos), expectation);
            if(status != RECEIVE_STATUS_INCOMPLETE){
              //memset(RxBuffer, 0, ESP_MAX_BUFFER_SIZE);
              //pos = 0;
            }
        } else {
            // Buffer wrap-around
            status = ParseBuffer(&RxBuffer[OldPos], ESP_MAX_BUFFER_SIZE - OldPos, expectation);
            if (pos > 0) {
                status = ParseBuffer(&RxBuffer[0], pos, expectation);
            }
        }
    }
    OldPos = pos;
    return status;
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

  case AT_CWMODE1:
    Debug("Setting to station mode");
    ATCommandSend = CWMODE1();
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
    Debug("SET multiple communication channels");
    ATCommandSend = CIPMUX();
    ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
    break;

  case AT_WEBSERVER:
    Debug("SET in station/soft-ap mode");
    ATCommandSend = WEBSERVER();
    ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
    break;

  case AT_HTTPCPOST:
    Debug("SET in station/soft-ap mode");
    ATCommandSend = HTTPCPOST();
    ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
    break;

  case AT_SENDDATA:
    Debug("Send the data");
    ATCommandSend = SENDDATA();
    ESPTimeStamp = HAL_GetTick() + ESP_WIFI_INIT_TIME;
    break;

  case AT_SLEEP:
    Debug("Setting ESP in sleep mode for 5 min");
    ATCommandSend = SLEEP();
    ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
    break;
  }

  return(ATCommandSend);
}

void ESP_WakeTest(void) {
  bool ATSend = false;
  static Receive_Status ATReceived = RECEIVE_STATUS_INCOMPLETE;
  switch (TestState){

    case ESP_TEST_INIT:
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
      if(TimestampIsReached(ESPTimeStamp)){
        ATSend = AT_Send(ATCommand);
        if(ATSend){
          TestState = ESP_TEST_RECEIVE;
        }
      }
      break;

    case ESP_TEST_RECEIVE:
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
      //Set measurement completed
      TIM3 -> CCR1 = 4000;
      TIM3 -> CCR2 = 0;
      TIM3 -> CCR3 = 4000;
      TestState = ESP_TEST_DEINIT;

      break;

    case ESP_TEST_DEINIT:
      testRound = false;
      EspTurnedOn = false;
      HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(ESP32_BOOT_GPIO_Port, ESP32_BOOT_Pin, 0);
      // Reset ESP, so we're sure that we're in the right state.
      SetESPMeasurementDone();
      break;

    default:
      TestState = ESP_TEST_INIT;
      break;



    case ESP_TEST_BOOT:
      TIM3 -> CCR1 = 4000;
      TIM3 -> CCR2 = 4000;
      TIM3 -> CCR3 = 0;
      //WAIT FOR RESET;
      break;
  }
}

void ESP_Upkeep(void) {
  bool ATSend = false;
  static Receive_Status ATReceived = RECEIVE_STATUS_INCOMPLETE;
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
      // Wait for ESP to be ready
      // Start reading DMA buffer for AT commands
      if(ESP_Receive(RxBuffer, ESP_MAX_BUFFER_SIZE)) {
        EspState = ESP_STATE_MODE_SELECT;
      }
      break;

    case ESP_STATE_MODE_SELECT:
      memset(ATCommandArray, AT_END, 10);
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
      if(InitIsDone && ConnectionMade && !WifiReset){
        memcpy(ATCommandArray, AT_SEND, 3);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_SEND;
        TIM2 -> CCR4 = 3000;
        ATCommand = ATCommandArray[ATCounter];
        ATExpectation = RECEIVE_EXPECTATION_OK;
      }
      if(ReconfigSet){
        memcpy(ATCommandArray, AT_WIFI_RECONFIG, 3);
        EspState = ESP_STATE_SEND;
        ATCounter = 0;
        Mode = AT_MODE_SEND;
        TIM2 -> CCR4 = 3000;
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
          EspState = ESP_STATE_SEND;
        }
        if(ATReceived == RECEIVE_STATUS_INCOMPLETE){
          ESPTimeStamp = HAL_GetTick() + 10;
        }
        if(ATReceived == RECEIVE_STATUS_TIMEOUT){
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
      EspState = ESP_STATE_SEND;
      if(ATCommand == AT_END){
        if(Mode == AT_MODE_SEND){
          ESPTimeStamp = HAL_GetTick() + 300000;
          TIM2 -> CCR4 = 4000;
        }
        EspState = ESP_STATE_RESET;
      }
    break;

    case ESP_STATE_RESET:
      if(TimestampIsReached(ESPTimeStamp) || ReconfigSet){
        if(Mode == AT_MODE_INIT){
          InitIsDone = true;
        }
        if(Mode == AT_MODE_CONFIG){
          ConnectionMade = true;
        }
        TIM2 -> CCR1 = 40000;
        TIM2 -> CCR3 = 40000;
        TIM2 -> CCR4 = 40000;
        EspState = ESP_STATE_MODE_SELECT;
      }

      break;

    case ESP_STATE_ERROR:
      // Handle error state
      Debug("ESP Error occurred");
      EspState = ESP_STATE_INIT;
      break;

    default:
      // Handle unexpected state
      EspState = ESP_STATE_ERROR;
      break;
  }
}
