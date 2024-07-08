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

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

void HT_Init(I2CReadCb readFunction, I2CWriteCB writeFunction);
void HT_StartMeasurement(void);
void HT_SetMeasurementDuration(uint32_t duration);
bool HT_DeviceConnected(void);
bool HT_GetMeasurementValues(float* humidity_perc, float* temperature);

#endif /* INC_HUMIDTEMP_H_ */
