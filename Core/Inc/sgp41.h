/*
 * sgp41.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_SGP41_H_
#define INC_SGP41_H_

#include <stdbool.h>
#include <stdint.h>


#define SGP_CRC_INIT_VALUE 0xff
#define SGP_CRC_MSB_MASK 0x80
#define SGP_CRC_POLYNOMIAL 0x31

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction);
void SGP_StartMeasurement(void);
bool SGP_MeasurementReady(void);
bool SGP_GetMeasurementValues(float* vocIndex, float* noXIndex);
bool SGP_DeviceConnected(void);

#endif /* INC_SGP41_H_ */
