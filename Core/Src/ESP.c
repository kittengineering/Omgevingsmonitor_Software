/*
 * ESP.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#include "ESP.h"

static UART_HandleTypeDef* EspUart = NULL;
static volatile bool TxComplete = false;
static volatile bool RxComplete = false;
static uint8_t RxBuffer[10] = {0};
static bool EspTurnedOn = false;
static uint8_t RxNotCompletedCount = 0;
static uint8_t TxNotCompletedCount = 0;
static char* AT_OkResponse = "OK\r\n";

static ESP_States EspState = ESP_STATE_OFF;


void ESP_Init(UART_HandleTypeDef* espUart) {
  EspUart = espUart;
  EspState = ESP_STATE_INIT;
}

static bool ESP_Send(uint8_t* command, uint8_t length) {
  TxComplete = false;
  HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(EspUart, command, length);
  if (status != HAL_OK) {
    Debug("Error in HAL_UART_Transmit_DMA");
    TxComplete = true;
    return false;
  }
  return true;
}

static bool ESP_Receive(uint8_t* reply, uint8_t length) {
  RxComplete = false;
  HAL_StatusTypeDef status = HAL_UART_Receive_DMA(EspUart, reply, length);
  if (status != HAL_OK) {
    Debug("Error in HAL_UART_Receive_DMA.");
    RxComplete = true;
    return false;
  }
  return true;
}

// Callback for transmission complete
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == EspUart) {
    TxComplete = true;
    Debug("TxComplete");
  }
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

static bool ESP_TranceivingDone(void) {
  if(TxComplete) {
    return true;
  }else {
    if(TxNotCompletedCount >= ESP_MAX_UART_RETRIES) {
      TxNotCompletedCount = 0;
      EspState = ESP_STATE_ERROR;
    }
    TxNotCompletedCount += 1;
    return false;
  }
}

static bool ESP_ReceivingDone(void) {
  if(RxComplete) {
    return true;
  }else {
    if(RxNotCompletedCount >= ESP_MAX_UART_RETRIES) {
      RxNotCompletedCount = 0;
      EspState = ESP_STATE_ERROR;
    }
    RxNotCompletedCount += 1;
    return false;
  }
}

static bool ESP_ResponseMatch(uint8_t* rxBuffer, char* expectedResponse) {
  return(strstr((char*)rxBuffer, expectedResponse) != NULL);
}

void ESP_Upkeep(void) {
  switch (EspState) {
    case ESP_STATE_OFF:
      // Turning off the ESP
      HAL_GPIO_WritePin(Wireless_EN_GPIO_Port, Wireless_EN_Pin, GPIO_PIN_RESET);
      EspTurnedOn = false;
      EspState = ESP_STATE_IDLE;
      break;

    case ESP_STATE_IDLE:
      // Waiting for wake up call.
      break;

    case ESP_STATE_INIT:
        // Initialization state
      if(!EspTurnedOn) {
        HAL_GPIO_WritePin(Wireless_EN_GPIO_Port, Wireless_EN_Pin, GPIO_PIN_SET);
        EspTurnedOn = true;
      }
      // Wait for ESP to be ready
      if (ESP_Send((uint8_t*)"AT\r\n", 4)) {
          EspState = ESP_STATE_WAIT_FOR_READY;
      } else {
          EspState = ESP_STATE_ERROR;
      }
      break;

    case ESP_STATE_WAIT_FOR_READY:
      if(ESP_TranceivingDone()) {
        if (ESP_Receive(RxBuffer, 4)) {
          Debug("Checking rx");
          EspState = ESP_STATE_PROCESS_READY;
        }
      }
      break;

    case ESP_STATE_PROCESS_READY:
      if(ESP_ReceivingDone()) {
        if(ESP_ResponseMatch(RxBuffer, AT_OkResponse)) {
          EspState = ESP_STATE_SEND_AT;
        }else {
          EspState = ESP_STATE_ERROR;
        }
      }
      break;
    case ESP_STATE_SEND_AT:

      // Send an AT command
      // TODO: Add sequence of commands that you want to send.
      // Similar to the measurements, with done flag etc.
      if (ESP_Send((uint8_t*)"AT\r\n", 4)) {
        EspState = ESP_STATE_WAIT_FOR_RESPONSE;
      } else {
        EspState = ESP_STATE_ERROR;
      }
      break;

    case ESP_STATE_WAIT_FOR_RESPONSE:
      // Wait for the response
      if(TxComplete) {
        if(ESP_Receive(RxBuffer, 4)) {
          EspState = ESP_STATE_PROCESS_RESPONSE;
        }
      }
      break;

    case ESP_STATE_PROCESS_RESPONSE:
      if(RxNotCompletedCount >= ESP_MAX_UART_RETRIES) {
        RxNotCompletedCount = 0;
        EspState = ESP_STATE_ERROR;
      }
      if(RxComplete) {
        Debug("RxBuffer: %s", RxBuffer);
//        EspState = ESP_STATE_SEND_AT;
        EspState = ESP_STATE_OFF;
      } else {
        RxNotCompletedCount += 1;
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
