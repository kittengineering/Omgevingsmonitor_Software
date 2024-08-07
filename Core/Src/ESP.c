/*
 * ESP.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#include "ESP.h"

static UART_HandleTypeDef* EspUart = NULL;
static volatile bool RxComplete = false;
static uint8_t RxBuffer[ESP_MAX_BUFFER_SIZE] = {0};
static bool EspTurnedOn = false;
static uint8_t RxNotCompletedCount = 0;
static char AT_OkResponse[8] = "AT\r\nOK\r\n";
static uint32_t StartUpTime = ESP_START_UP_TIME;
static uint32_t DMATimeout = ESP_DMA_TIMEOUT;
static bool StartUpDone = false;

static ESP_States EspState = ESP_STATE_OFF;

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
  HAL_UART_DMAStop(EspUart);
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

//static bool ESP_ReceivingDone(void) {
//  if(RxComplete) {
//    return true;
//  }else {
//    if(RxNotCompletedCount >= ESP_MAX_UART_RETRIES) {
//      RxNotCompletedCount = 0;
//      EspState = ESP_STATE_ERROR;
//    }
//    RxNotCompletedCount += 1;
//    return false;
//  }
//}

//static bool ESP_ResponseMatch(uint8_t* rxBuffer, char* expectedResponse) {
////  // Ensure the buffer is null-terminated
////  uint8_t tempBuffer[ESP_MAX_BUFFER_SIZE] = {0};
////  strncpy((char*)tempBuffer, (char*)rxBuffer, sizeof(tempBuffer) - 1);
//
//  // Use strstr to check if the expected response is within the buffer
//  return (strstr((char*)rxBuffer, expectedResponse) != NULL);
//}

void ESP_Upkeep(void) {
  switch (EspState) {
    case ESP_STATE_OFF:
      // Turning off the ESP
//      HAL_GPIO_WritePin(Wireless_EN_GPIO_Port, Wireless_EN_Pin, GPIO_PIN_RESET);
      EspTurnedOn = false;
      EspState = ESP_STATE_IDLE;
      break;

    case ESP_STATE_IDLE:
      // Waiting for wake up call.
      break;

    case ESP_STATE_INIT:
      // Initialization state
      StartUpTime = GetCurrentHalTicks() + ESP_START_UP_TIME;
      StartUpDone = false;
      if(!EspTurnedOn) {
//        HAL_GPIO_WritePin(Wireless_EN_GPIO_Port, Wireless_EN_Pin, GPIO_PIN_SET);
        EspTurnedOn = true;
      }
      // Wait for ESP to be ready
      EspState = ESP_STATE_WAIT_FOR_READY;
      break;

    case ESP_STATE_WAIT_FOR_READY:
      if (TimestampIsReached(StartUpTime) && !StartUpDone) {
        if(ESP_Send((uint8_t*)"AT\r\n", 4)) {
          StartUpDone = true;
        }else {
          EspState = ESP_STATE_ERROR;
        }
      }
      if(StartUpDone) {
        // Startup is done and we've sent a command, now we want to receive that command.

        if(ESP_Receive(RxBuffer, 10)) {
          // TODO: Add timeout for dma to stop reading and then return that data.
          Debug("RxBuffer contents: %s", (char*)RxBuffer);
//          EspState = ESP_STATE_PROCESS_READY;
          EspState = ESP_STATE_PROCESS_READY;
        }
      }
      break;

    case ESP_STATE_PROCESS_READY:
      if(RxComplete) {
        if(strstr((char*)RxBuffer, AT_OkResponse)) {
          Debug("SUCCESFUL AT command received.");
          EspState = ESP_STATE_INIT;
        }
      }
      break;

    case ESP_STATE_SEND_AT:
      break;

    case ESP_STATE_WAIT_FOR_RESPONSE:
      break;

//    case ESP_STATE_PROCESS_READY:
////      if(ESP_ReceivingDone()) {
////        if(ESP_ResponseMatch(RxBuffer, AT_OkResponse)) {
//        if(strstr((char*)RxBuffer, AT_OkResponse) != NULL) {
//          EspState = ESP_STATE_SEND_AT;
//        }else {
//          EspState = ESP_STATE_ERROR;
//        }
////      }
//      break;
//    case ESP_STATE_SEND_AT:
//
//      // Send an AT command
//      // TODO: Add sequence of commands that you want to send.
//      // Similar to the measurements, with done flag etc.
//      if (ESP_Send((uint8_t*)"AT\r\n", 4)) {
//        EspState = ESP_STATE_WAIT_FOR_RESPONSE;
//      } else {
//        EspState = ESP_STATE_ERROR;
//      }
//      break;
//
//    case ESP_STATE_WAIT_FOR_RESPONSE:
//      // Wait for the response
//      if(TxComplete) {
//        if(ESP_Receive(RxBuffer, 4)) {
//          EspState = ESP_STATE_PROCESS_RESPONSE;
//        }
//      }
//      break;
//
//    case ESP_STATE_PROCESS_RESPONSE:
//      if(RxNotCompletedCount >= ESP_MAX_UART_RETRIES) {
//        RxNotCompletedCount = 0;
//        EspState = ESP_STATE_ERROR;
//      }
//      if(RxComplete) {
//        Debug("RxBuffer: %s", RxBuffer);
////        EspState = ESP_STATE_SEND_AT;
//        EspState = ESP_STATE_OFF;
//      } else {
//        RxNotCompletedCount += 1;
//      }
//      break;
//
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
