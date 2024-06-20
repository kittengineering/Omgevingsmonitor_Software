/*
 * wsenHIDS.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_WSENHIDS_H_
#define INC_WSENHIDS_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	HIGH_PRECISION_1S_200MW = 0x39,
	HIGH_PRECISION_100MS_200MW = 0x32,
	HIGH_PRECISION_1S_110MW = 0x2F,
	HIGH_PRECISION_100MS_110MW = 0x24,
	HIGH_PRECISION_1S_20MW = 0x1E,
	HIGH_PRECISION_100MS_20MW = 0x15
} HIDSHeaterModes;

typedef enum {
	HIGH_PRECISION = 0xFD,
	MEDIUM_PRECISION = 0xF6,
	LOW_PRECISION = 0xE0
} HIDSMeasureModes;

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef uint8_t (*CRC)(uint8_t* data, uint8_t length);

void HIDS_Init(I2CReadCb readFunction, I2CWriteCB writeFunction, CRC crcFunction);
//void HIDS_SetAverage(HIDSAverageTemperatureModes modeTemp, HIDSAverageHumidityModes modeHum);
//void HIDS_SetInterruptMode(HIDSInterruptModes mode);
//void HIDS_SetContinuousMode(void);
//void HIDS_SetOneShotMode(void);
//void HIDS_StartOneShotMeasurement(void);
void HIDS_SetMeasurementMode(HIDSMeasureModes modeMeasure);
void HIDS_StartMeasurement(void);
bool HIDS_MeasurementReady(void);
bool HIDS_GetMeasurementValues(float* humidity, float* temperature);
bool HIDS_DeviceConnected(void);
void HIDS_SetHeaterMode(HIDSHeaterModes modeHeater);
void HIDS_PowerDown(void);

#endif /* INC_WSENHIDS_H_ */
