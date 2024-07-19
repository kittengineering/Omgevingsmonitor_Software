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
static uint8_t RxBuffer[100] = {0};

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
  }
}

// Callback for reception complete
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == EspUart) {
    RxComplete = true;
  }
}

// Callback for UART error
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  if (huart == EspUart) {
    // Handle error
    EspState = ESP_STATE_ERROR;
  }
}

void ESP_TestStartUp(void) {

}

void ESP_Upkeep(void) {
  switch (EspState) {
    case ESP_STATE_OFF:
      // ESP is turned off or inactive
      // TODO: Add sleep mode?
      break;

    case ESP_STATE_INIT:
      // Initialization state
      if (ESP_Send((uint8_t*)"AT\r\n", 8)) {
        EspState = ESP_STATE_WAIT_FOR_RESPONSE;
      } else {
        EspState = ESP_STATE_ERROR;
      }
      break;

    case ESP_STATE_SEND_AT:
      // Send an AT command
      // TODO: Add sequence of commands that you want to send.
      if (ESP_Send((uint8_t*)"AT\r\n", 4)) {
        EspState = ESP_STATE_WAIT_FOR_RESPONSE;
      } else {
        EspState = ESP_STATE_ERROR;
      }
      break;

    case ESP_STATE_WAIT_FOR_RESPONSE:
      // Wait for the response
      if(TxComplete) {
        if(ESP_Receive(RxBuffer, 100)) {
          EspState = ESP_STATE_PROCESS_RESPONSE;
        }
      }
      break;

    case ESP_STATE_PROCESS_RESPONSE:
      if(RxComplete) {
        Debug("RxBuffer: %s", RxBuffer);
//        EspState = ESP_STATE_SEND_AT;
        EspState = ESP_STATE_OFF;
      }
      break;

    case ESP_STATE_ERROR:
      // Handle error state
      Debug("ESP Error occurred");
      // Optionally reset the state machine
      EspState = ESP_STATE_INIT;
      break;

    default:
      // Handle unexpected state
      EspState = ESP_STATE_ERROR;
      break;
  }
}
