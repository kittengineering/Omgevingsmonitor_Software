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

typedef enum {
  ESP_STATE_OFF,
  ESP_STATE_IDLE,
  ESP_STATE_WAIT_FOR_READY,
  ESP_STATE_PROCESS_READY,
  ESP_STATE_INIT,
  ESP_STATE_SEND_AT,
  ESP_STATE_WAIT_FOR_RESPONSE,
  ESP_STATE_PROCESS_RESPONSE,
  ESP_STATE_ERROR
} ESP_States;

void ESP_Init(UART_HandleTypeDef* espUart);
void ESP_Upkeep(void);
void ESP_Reset(void);
void ESP_Sleep(void);

#endif /* INC_ESP_H_ */
