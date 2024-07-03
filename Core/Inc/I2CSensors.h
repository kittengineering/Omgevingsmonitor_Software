/*
 * I2CSensors.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_I2CSENSORS_H_
#define INC_I2CSENSORS_H_

#include "stm32l0xx_hal.h"
#include <stdbool.h>

void I2CSensors_Init(I2C_HandleTypeDef* sensorI2C);

#endif /* INC_I2CSENSORS_H_ */
