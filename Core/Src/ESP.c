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
static bool EspTurnedOn = false;
char SSID[] = "KITT-guest";
char Password[] = "ZonderSnoerCommuniceren053";
char API[] = "\"https://api.opensensemap.org/boxes/66c7394026df8b0008c359a4/data\", 508, 1, \"content-type: application/json\"";
uint8_t ATState;
//static bool StartUpDone = false;
//static bool ResponseFound = false;
static volatile uint8_t OldPos = 0;
//static uint16_t TempIndex = 0;
//static uint16_t ATCommandIndex = 0;
static uint32_t ESPTimeStamp = 0;
static uint8_t retry = 0;
static uint8_t ATExpectation = RECEIVE_EXPECTATION_OK;
static uint8_t nextATCommand = AT_WAKEUP;

//static char TempBuffer[ESP_MAX_BUFFER_SIZE];      // Buffer to build up the received message
static char CommandBuffer[ESP_MAX_BUFFER_SIZE]; // Buffer to store the last sent command
static bool CommandEchoed = false;            // Flag to indicate if the command was echoed

/* TODO: Add done function per ATCommand and save the response in there.
 * Response handle functions
*/
//static char* ATCommands[AT_COMMANDS_SIZE] = {};

typedef struct {
    char* ATCommand;
    bool* doneFlag;
} ATCommandsParameters;

// Taken from firmware https://github.com/opendata-stuttgart/sensors-software/blob/master/airrohr-firmware/airrohr-firmware.ino

struct struct_wifiInfo
{
  char ssid[35];
  uint8_t encryptionType;
  int32_t RSSI;
  int32_t channel;
};


static ESP_States EspState = ESP_STATE_INIT;
static AT_Commands ATCommands = AT_WAKEUP;
//static ATCommandsParameters ATCommands[ESP_AT_COMMANDS_COUNT];

//TODO: Add de-init if ESP is off. Otherwise there is going to be 3.3V on the ESP.


void ESP_Init(UART_HandleTypeDef* espUart) {
  EspUart = espUart;
  EspState = ESP_STATE_INIT;
}

static bool ESP_Send(uint8_t* command, uint8_t length) {
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

void SetCommandBuffer(const char* command) {
    strncpy(CommandBuffer, command, ESP_MAX_BUFFER_SIZE);
    CommandEchoed = false; // Reset the flag when a new command is sent
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
  const char OK[] = AT_RESPONSE_OK;
  const char ERROR[] = AT_RESPONSE_ERROR;
  const char ready[] = AT_RESPONSE_READY;
  if(expectation == RECEIVE_EXPECTATION_OK){
    ParsePoint = strstr(tempBuf, OK);
  }
  if(expectation == RECEIVE_EXPECTATION_READY){
    ParsePoint = strstr(tempBuf, ready);
  }
  ParsePoint2 = strstr(tempBuf, ERROR);
  if(len > 1 ){
    TestChar = *ParsePoint;
    if(TestChar == 'O'){
      status = RECEIVE_STATUS_OK;
    }
    if(TestChar == 'r'){
      status = RECEIVE_STATUS_READY;
    }
    TestChar = *ParsePoint2;
    if(TestChar == 'E'){
      status = RECEIVE_STATUS_ERROR;
    }
  }
  return(status);

//    for (uint16_t i = 0; i < len; i++) {
//        char c = buffer[i];
//        // TODO: Add logic to parsebuffer depending on sent AT command
//        // Make sure to keep track of beginning /r/n of the OK response: /r/nOK/r/n
//        // Add the new character to the temp buffer
//        //TempBuffer[TempIndex++] = c;
//
//        // Check if we've reached the end of a line (i.e., "\r\n")
//        if (c == '\n' && TempIndex > 1 && TempBuffer[TempIndex - 2] == '\r') {
//            // Null-terminate the string
//            TempBuffer[TempIndex] = '\0';
//            if (CommandEchoed) {
//              // Command is echoed.
//              // Copying last response to buffer.
//              if(strstr(TempBuffer, AT_RESPONSE_OK) != NULL) {
//                Debug("Found OK, stop parsing.");
//                ATCommandIndex += 1;
//                EspState = ESP_STATE_SEND_AT;
//                break;
//              }
//              if(strstr(TempBuffer, AT_RESPONSE_OK) != NULL) {
//                Debug("Found ERROR, stop parsing.");
//                EspState = ESP_STATE_ERROR;
//                break;
//              }
//              memcpy(LastATResponse, TempBuffer, ESP_MAX_BUFFER_SIZE);
//              // Response handled, resetting buffer.
//              TempIndex = 0;
//              // Clear the buffer
//              memset(TempBuffer, 0, ESP_MAX_BUFFER_SIZE);
//            }
//            // Check if the received string matches the last sent command (echo)
//            if (!CommandEchoed && strstr(TempBuffer, CommandBuffer) != NULL) {
//                CommandEchoed = true;
//                // Reseting index and clearing buffer.
//                TempIndex = 0;
//                memset(TempBuffer, 0, ESP_MAX_BUFFER_SIZE);
//            }
//
//          // If TempIndex reaches TEMP_BUFFER_SIZE, reset to prevent overflow
//          if (TempIndex >= ESP_MAX_BUFFER_SIZE) {
//              TempIndex = 0;
//          }
//       }
//    }
}
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
  sprintf(atCommandBuff, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, Password);
  uint8_t len = strlen(atCommandBuff);
  char atCommand[len+1];
  strncpy(atCommand, atCommandBuff, len);
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
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
  char* atCommand = "AT+CWSAP=\"WOTS_Config\",\"\", 11,0,1\r\n";
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
bool HTTPCPOST(){
  char atCommandBuff[255];
  sprintf(atCommandBuff, "AT+HTTPCPOST=%s\r\n", API);
  uint8_t len = strlen(atCommandBuff);
  char atCommand[len+1];
  strncpy(atCommand, atCommandBuff, len);
  SetCommandBuffer(atCommand);
  if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))){
    return true;
  }
  else{
    return false;
  }
}
uint8_t DMA_ProcessBuffer(uint8_t expectation) {
    uint16_t pos = ESP_MAX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart4_rx);
    uint8_t status = RECEIVE_STATUS_INCOMPLETE;
    if(pos > ESP_MAX_BUFFER_SIZE) {
      pos = ESP_MAX_BUFFER_SIZE;
    }
    if(pos == OldPos){
      if(retry >4){
        EspState = ESP_STATE_SEND;
        retry = 0;
        status = RECEIVE_STATUS_RETRY;
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
            }
        } else {
            // Buffer wrap-around
            status = ParseBuffer(&RxBuffer[OldPos], ESP_MAX_BUFFER_SIZE - OldPos, expectation);
            if (pos > 0) {
                status = ParseBuffer(&RxBuffer[0], pos, expectation);
            }
        }
        OldPos = pos;
        return status;
    }
}
bool ATCompare(uint8_t AT_Command_Received, uint8_t AT_Command_Expected){
  bool value = false;
  if(AT_Command_Expected == RECEIVE_EXPECTATION_OK){
    value = (AT_Command_Received == RECEIVE_STATUS_OK);
  }
  if(AT_Command_Expected == RECEIVE_EXPECTATION_READY){
    value = (AT_Command_Received == RECEIVE_STATUS_READY);
  }
  return(value);
}

bool AT_Send(state){
  bool ATCommandSend = false;
  switch (state){

  case AT_WAKEUP:
  if(TimestampIsReached(ESPTimeStamp)){
    ATCommandSend = PollAwake();
    ESPTimeStamp = HAL_GetTick() + ESP_RESPONSE_TIME;
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
  }

  return(ATCommandSend);
}

void ESP_Upkeep(void) {
  bool ATSend = false;
  uint8_t ATReceived = RECEIVE_STATUS_INCOMPLETE;
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
      uint8_t offset = 0;
//      ATCommands[offset++] = (ATCommands) {};
      // TODO: Add turning on the ESP32 and wait for ready after, so we know for sure that the ESP is on.
      // Initialization state
//      StartUpTime = GetCurrentHalTicks() + ESP_START_UP_TIME;
//      StartUpDone = false;
      if(!EspTurnedOn) {

        HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
//        // Turn ESP on.
        HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_SET);
        // Reset ESP, so we're sure that we're in the right state.
        HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_SET);
//        HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);
        ESPTimeStamp = HAL_GetTick() + ESP_START_UP_TIME;

        EspTurnedOn = true;
      }
      // Wait for ESP to be ready
      // Start reading DMA buffer for AT commands
      if(ESP_Receive(RxBuffer, ESP_MAX_BUFFER_SIZE)) {
        EspState = ESP_STATE_SEND;
      }
      break;

    case ESP_STATE_SEND:
      ATSend = AT_Send(nextATCommand);
      if(ATSend){
        EspState = ESP_STATE_WAIT_FOR_REPLY;
      }

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
        if(proceed){
          EspState = ESP_STATE_NEXT_AT;
        }
      }
      break;

    case ESP_STATE_NEXT_AT:
      if(ATCommands < AT_HTTPCPOST){
        ATCommands = ATCommands+1;
        if(ATCommands == AT_RESTORE){
            ATExpectation = RECEIVE_EXPECTATION_READY;
        }
        else{
          ATExpectation = RECEIVE_EXPECTATION_OK;
        }
      }
      else{
        //Start data sending.
      }
      EspState = ESP_STATE_SEND;
      nextATCommand = ATCommands;

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
