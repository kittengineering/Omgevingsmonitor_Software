/*
 * humidTemp.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_HUMIDTEMP_H_
#define INC_HUMIDTEMP_H_

#include "stm32l0xx_hal.h"
#include <stdbool.h>

void HT_Init(I2C_HandleTypeDef* humTempI2c);
void HT_StartMeasurement(void);
bool HT_GetMeasurementValues(float* humidity_perc, float* temperature);

#endif /* INC_HUMIDTEMP_H_ */
