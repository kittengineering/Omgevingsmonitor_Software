/*
 * sgp41.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_SGP40_H_
#define INC_SGP40_H_

#include <stdbool.h>
#include <stdint.h>

#define SGP_I2C_ADDRESS 0x59
#define SGP_CRC_MSB_MASK 0x80
#define SGP_CRC_BIT_LENGTH 8
#define SGP_CRC_POLYNOMIAL 0x31 // CRC-8 polynomial: x^8 + x^5 + x^4 + 1
#define SGP_CRC_INIT_VALUE 0xff
#define SGP_CRC_SEGMENT 4
#define SGP_LONG_COMMAND_BUFFER_LENGTH 8
#define SGP_SHORT_COMMAND_BUFFER_LENGTH 2
#define SGP_SERIAL_NUMBER_RESPONSE_LENGTH 9
#define SGP_MEASURE_BUFFER_LENGTH 6
#define SGP_MEASURE_BUFFER_RESPONSE_LENGTH 3
#define SGP_SERIAL_NUMBER_SEGMENT_SIZE 3 // 2 bytes + 1 crc byte
#define SGP_SENSOR_INTERVAL 1000
#define SGP_SENSOR_MEASURE_WAIT_TIME 30 //30ms before the raw signal measurement is ready
#define SGP_SELF_TEST_WAIT_TIME 320 // 320ms before the self test results are ready
#define SGP_SELF_TEST_RESPONSE_LENGTH 3
#define SGP_SELF_TEST_SEGMENT_LENGTH 3 // 2 bytes + 1 crc byte

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction);
void SGP_StartMeasurement(void);
bool SGP_MeasurementReady(void);
bool SGP_GetMeasurementValues(float* vocIndex);
bool SGP_DeviceConnected(void);
bool SGP_SelfTest(void);

#endif /* INC_SGP40_H_ */
