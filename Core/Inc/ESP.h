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

void ESP_Init(UART_HandleTypeDef* espUart);
void ESP_Reset(void);
void ESP_Sleep(void);

#endif /* INC_ESP_H_ */
