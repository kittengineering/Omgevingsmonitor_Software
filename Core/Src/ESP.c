/*
 * ESP.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#include "ESP.h"

static UART_HandleTypeDef* EspUart = NULL;
extern DMA_HandleTypeDef hdma_usart4_rx;

static uint8_t RxBufferLength = 256;

static volatile bool RxComplete = false;
static uint8_t RxBuffer[ESP_MAX_BUFFER_SIZE] = {0};
static uint8_t LastATResponse[ESP_MAX_BUFFER_SIZE] = {0};
static bool EspTurnedOn = false;
//static bool StartUpDone = false;
//static bool ResponseFound = false;
static volatile uint8_t OldPos = 0;
static uint16_t TempIndex = 0;

static char TempBuffer[ESP_MAX_BUFFER_SIZE];      // Buffer to build up the received message
static char CommandBuffer[ESP_MAX_BUFFER_SIZE]; // Buffer to store the last sent command
static bool CommandEchoed = false;            // Flag to indicate if the command was echoed

/* TODO: Add done function per ATCommand and save the response in there.
 * Response handle functions
*/
//static char* ATCommands[AT_COMMANDS_SIZE] = {};
static ESP_States EspState = ESP_STATE_INIT;

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

void ParseBuffer(uint8_t* buffer, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        char c = buffer[i];

        // Add the new character to the temp buffer
        TempBuffer[TempIndex++] = c;

        // Check if we've reached the end of a line (i.e., "\r\n")
        if (c == '\n' && TempIndex > 1 && TempBuffer[TempIndex - 2] == '\r') {
            // Null-terminate the string
            TempBuffer[TempIndex] = '\0';

            // Check if the received string matches the last sent command (echo)
            if (!CommandEchoed && strstr(TempBuffer, CommandBuffer) != NULL) {
                CommandEchoed = true;
            }
            if (CommandEchoed) {
              // Command is echoed.
              // Copying last response to buffer.
              if(strstr(TempBuffer, AT_RESPONSE_OK) != NULL) {
                Debug("Found OK, stop parsing.");
                EspState = ESP_STATE_SEND_AT;
                break;
              }
              if(strstr(TempBuffer, AT_RESPONSE_OK) != NULL) {
                Debug("Found ERROR, stop parsing.");
                EspState = ESP_STATE_ERROR;
                break;
              }

              memcpy(LastATResponse, TempBuffer, ESP_MAX_BUFFER_SIZE);
              TempIndex = 0;
              // Clear the buffer
              memset(TempBuffer, 0, ESP_MAX_BUFFER_SIZE);
            }
          // If TempIndex reaches TEMP_BUFFER_SIZE, reset to prevent overflow
          if (TempIndex >= ESP_MAX_BUFFER_SIZE - 1) {
              TempIndex = 0;
          }
       }
    }
}

void DMA_ProcessBuffer(void) {
    uint16_t pos = ESP_MAX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart4_rx);
    if(pos > ESP_MAX_BUFFER_SIZE) {
      pos = ESP_MAX_BUFFER_SIZE;
    }
    if (pos != OldPos) {
        if (pos > OldPos) {
            // Direct parsing
            ParseBuffer(&RxBuffer[OldPos], pos - OldPos);
        } else {
            // Buffer wrap-around
            ParseBuffer(&RxBuffer[OldPos], ESP_MAX_BUFFER_SIZE - OldPos);
            if (pos > 0) {
                ParseBuffer(&RxBuffer[0], pos);
            }
        }
        OldPos = pos;
    }
}

void ESP_Upkeep(void) {
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
      // TODO: Add turning on the ESP32 and wait for ready after, so we know for sure that the ESP is on.
      // Initialization state
//      StartUpTime = GetCurrentHalTicks() + ESP_START_UP_TIME;
//      StartUpDone = false;
      if(!EspTurnedOn) {
//        HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_RESET);
//        // Turn ESP on.
//        HAL_GPIO_WritePin(Wireless_PSU_EN_GPIO_Port, Wireless_PSU_EN_Pin, GPIO_PIN_SET);
        // Reset ESP, so we're sure that we're in the right state.
//        HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_SET);
//        HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_RESET);

        EspTurnedOn = true;
        // Wait for ESP to be ready
        // Start reading DMA buffer for AT commands
        // TODO: Fix the warning for the macro definition
        if(ESP_Receive(RxBuffer, RxBufferLength)) {
          char* atCommand = "AT+GMR\r\n";
          SetCommandBuffer(atCommand);
          if(ESP_Send((uint8_t*)atCommand, strlen(atCommand))) {
            EspState = ESP_STATE_WAIT_FOR_READY;
          }
        }
      }
      break;

    case ESP_STATE_WAIT_FOR_READY:
      // Start parsing to read startup response.
      DMA_ProcessBuffer();
      // If startup is received send the AT commands
//      const char* atCommand = "AT+RST\r\n";
//      // Set reset command
//      SetCommandBuffer(atCommand);
//      if(ESP_Send(atCommand)) {
//      }
      // Start parsing again, repeat
      break;

    case ESP_STATE_SEND_AT:
      Debug("Succesfully parsed buffer");
      // TODO:
      break;


    case ESP_STATE_PROCESS_AT:

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
