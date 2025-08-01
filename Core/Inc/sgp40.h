/*
 * sgp41.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_SGP40_TEUN_H_
#define INC_SGP40_TEUN_H_

#include <stdbool.h>
#include <stdint.h>
#include "statusCheck.h"

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
// #define SGP_SENSOR_DUTYCYCLE (SGP_SENSOR_HEATUP_TIME + SGP_SENSOR_IDLE_TIME) * (100 / 20) // Duty cycle of 20% (100 / 20)
#define SGP_SENSOR_HEATUP_TIME 170
#define SGP_SENSOR_IDLE_TIME 30
#define SGP_SELF_TEST_WAIT_TIME 320 // 320ms before the self test is ready
#define SGP_SELF_TEST_RESPONSE_LENGTH 3
#define SGP_SELF_TEST_SEGMENT_LENGTH 3 // 2 bytes + 1 crc byte
#define SGP_SELF_TEST_SUCCESS 0x4d

#define SGP_OLD_COMPENSATION 30*1000    //after 30 seconds compensation values should be updated

typedef bool (*I2CReadCb)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CWriteCB)(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
typedef bool (*I2CTransmissionDoneCB)();

typedef enum {
    SGP_STATE_INIT,
    SGP_STATE_START_MEASUREMENTS,
    SGP_STATE_WAIT_FOR_COMPLETION,
    SGP_STATE_PROCESS_RESULTS,
    SGP_STATE_WAIT_FOR_READY,
    SGP_STATE_OFF,
    SGP_WAIT_STATE_MODE,
    SGP_STATE_WAIT,
    SGP_STATE_DONE,
    SGP_STATE_START_FIRST_MEASUREMENT,
    SGP_STATE_WAIT_FOR_HEAT_UP
} SGP40State;

typedef struct {
    uint16_t temperatureComp;
    uint16_t humidityComp;
    uint32_t lastUpdate;
} Compensation_t;

// void forceVOCstart(void);
void SGP40_Resume(bool value);
void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction, I2CTransmissionDoneCB statusFunction);
// void SGP_StartMeasurement(void);
// bool SGP_GetMeasurementValues(int32_t* vocIndex);
// bool SGP_DeviceConnected(void);
// bool SGP_SelfTest(void);
void SGP_SoftReset(void);
// void SGP_GetHT(float* temperature, float* humidity);
// SGP40State SGP_Upkeep(void);
void setSGP40TimeStamp(uint32_t ticks);
// void ResetSGP40samplecounter();

void SGP_SetCompensation(float temperature, float humidity);
void initVOC(SensorType1* vocout);
SGP40State SGP_Upkeep();//State gadgetState);
void UpdateAlgorithmInterval(uint32_t interval);

#endif /* INC_SGP40_H_ */
