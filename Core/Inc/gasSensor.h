/*
 * gasSensor.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_GASSENSOR_H_
#define INC_GASSENSOR_H_

#include "stm32l0xx_hal.h"
#include <stdbool.h>

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

void Gas_Init(I2CReadCb readFunction, I2CWriteCB writeFunction);
void Gas_StartMeasurement(void);
bool Gas_GetMeasurementValues(int32_t* vocIndex);
bool Gas_DeviceConnected(void);

#endif /* INC_GASSENSOR_H_ */
