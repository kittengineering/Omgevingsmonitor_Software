/*
 * measurement.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_MEASUREMENT_H_
#define INC_MEASUREMENT_H_

#include "stm32l0xx_hal.h"
#include <stdbool.h>

void Meas_Init(I2C_HandleTypeDef* humidTempI2c, I2S_HandleTypeDef* micI2s);
void Meas_Start(void);
void Meas_Upkeep(void);
bool Meas_CanSleep(int* duration_ms);

#endif /* INC_MEASUREMENT_H_ */
