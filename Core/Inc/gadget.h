/*
 * gadget.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_GADGET_H_
#define INC_GADGET_H_

#include "gadget.h"
#include "measurement.h"
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "ESP.h"
#include "statusCheck.h"

void Gadget_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, UART_HandleTypeDef* espUart, ADC_HandleTypeDef* ADC_HANDLER);
bool UpkeepGadget(void);
void Gadget_Test();

#endif /* INC_GADGET_H_ */
