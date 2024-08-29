/*
 * ESP.h
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_ESP_H_
#define INC_ESP_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "gpio.h"

#define ESP_MAX_UART_RETRIES 2
#define ESP_MAX_BUFFER_SIZE 255
#define ESP_START_UP_TIME 700
#define ESP_RESPONSE_TIME 10
#define ESP_RESPONSE_LONG 50
#define ESP_WIFI_INIT_TIME 500
#define ESP_DMA_TIMEOUT 50
#define ESP_AT_COMMANDS_COUNT 4

#define AT_RESPONSE_OK "OK"
#define AT_RESPONSE_ERROR "ERROR"

#define AT_COMMANDS_SIZE 18

typedef enum {
  ESP_WAKEUP,
  ESP_SET_RFPOWER,
  ESP_CHECK_RFPOWER,
  ESP_RESTORE,
  ESP_CWINIT,
  ESP_CWMODE1,
  ESP_CWAUTOCONN,
  ESP_CWJAP,
  ESP_CWMODE3,
  ESP_CWSAP,
  ESP_CIPMUX,
  ESP_WEBSERVER,
  ESP_HTTPCPOST,
  ESP_STATE_OFF,
  ESP_STATE_IDLE,
  ESP_STATE_INIT,
  ESP_STATE_WAIT_FOR_READY,
  ESP_STATE_SEND_AT,
  ESP_STATE_PROCESS_AT,
  ESP_STATE_ERROR,
  ESP_STATE_WAIT_TO_SEND,
} ESP_States;

typedef enum {
  AT_WAKEUP,
  AT_SET_RFPOWER,
  AT_CHECK_RFPOWER,
  AT_RESTORE,
  AT_CWINIT,
  AT_CWMODE1,
  AT_CWAUTOCONN,
  AT_CWJAP,
  AT_CWMODE3,
  AT_CWSAP,
  AT_CIPMUX,
  AT_WEBSERVER,
  AT_HTTPCPOST
} AT_Commands;

void ESP_Init(UART_HandleTypeDef* espUart);
void ESP_Upkeep(void);
void ESP_Reset(void);
void ESP_Sleep(void);
void ESP_DeInit(void);

#endif /* INC_ESP_H_ */
