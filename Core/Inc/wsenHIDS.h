/*
 * wsenHIDS.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_WSENHIDS_H_
#define INC_WSENHIDS_H_

#include <stdbool.h>
#include <stdint.h>

#define HIDS_I2C_ADDRESS 0x44
#define HIDS_SERIAL_NUMBER_REG 0x89
#define HIDS_SOFT_RESET_REG 0x94
#define HIDS_BUFFER_LENGTH 24
#define HIDS_MEASURE_BUFFER_LENGTH 6
#define HIDS_SERIAL_BUFFER_LENGTH 6
#define HIDS_SENSOR_WAIT_TIME_HIGH 9
#define HIDS_SENSOR_WAIT_TIME_MEDIUM 5
#define HIDS_SENSOR_WAIT_TIME_LOW 2
#define HIDS_CRC_MSB_MASK 0x80
#define HIDS_CRC_BIT_LENGTH 16
#define HIDS_CRC_POLYNOMIAL 0x31 // CRC-8 polynomial: x^8 + x^5 + x^4 + 1
#define HIDS_CRC_INIT_VALUE 0xff
#define HIDS_POW_2_16_MINUS_1 65535.0
#define HIDS_SENSOR_INITIAL_INTERVAL 1200

typedef enum {
  HHM_HighPrecision1S200MW = 0x39,
  HHM_HighPrecision100MS200MW = 0x32,
  HHM_HighPrecision1S110MW = 0x2F,
  HHM_HighPrecision100MS110MW = 0x24,
  HHM_HighPrecision1S20MW = 0x1E,
  HHM_HighPrecision100MS20MW = 0x15
} HIDSHeaterModes;

typedef enum {
  HMM_HighPrecision = 0xFD,
  HMM_MediumPrecision = 0xF6,
  HMM_LowPrecision = 0xE0
} HIDSMeasureModes;

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

void HIDS_Init(I2CReadCb readFunction, I2CWriteCB writeFunction);
void HIDS_SetMeasurementMode(HIDSMeasureModes modeMeasure);
void HIDS_StartMeasurement(void);
bool HIDS_MeasurementReady(void);
bool HIDS_GetMeasurementValues(float* humidity, float* temperature);
bool HIDS_DeviceConnected(void);
void HIDS_SetHeaterMode(HIDSHeaterModes modeHeater);
void HIDS_SoftReset(void);

#endif /* INC_WSENHIDS_H_ */
