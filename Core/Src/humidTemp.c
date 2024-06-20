/*
 * humidTemp.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <wsenHIDS.h>
#include "stm32l0xx_hal.h"
#include "humidTemp.h"
#include "utils.h"

#define HIDS_BUFFER 256
#define HIDS_I2C_ADDRESS 0x5F
#define CRC_BIT_LENGTH 16
#define CRC_POLYNOMIAL 0x31 // CRC-8 polynomial: x^8 + x^5 + x^4 + 1

static I2C_HandleTypeDef* HumTempI2c = NULL;
static CRC_HandleTypeDef* SensorCrc = NULL;

static volatile bool I2C_Transfer_Complete = false;
static volatile bool I2C_Transfer_Error = false;

static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
static uint8_t CalcCRC(uint8_t* data, uint8_t length);

static uint32_t StartTime = 0;
static uint32_t StartupDoneTime = 0;

static volatile bool StartUpDone = false;
static volatile bool DataReady = false;


void HT_Init(I2C_HandleTypeDef* humTempI2c, CRC_HandleTypeDef* sensorCrc){
	HumTempI2c = humTempI2c;
	SensorCrc = sensorCrc;
    HIDS_Init(ReadI2C, WriteI2C, CalcCRC);
}

static void I2C_ResetFlags() {
    I2C_Transfer_Complete = false;
    I2C_Transfer_Error = false;
}

static void I2C_StartupTime(void){
	StartTime = HAL_GetTick();
	StartupDoneTime = StartTime + 20;
	StartUpDone = false;
}

// TODO Fix DMA I2C reading, not sure if this is working right. Timings seem to be off.
static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes){
    I2C_ResetFlags();
//    I2C_StartupTime();
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive_DMA(HumTempI2c, (address << 1), buffer, nrBytes);
//  HAL_StatusTypeDef status = HAL_I2C_Master_Receive_IT(HumTempI2c, (address << 1), buffer, nrBytes);
    if (status != HAL_OK) {
        return false;
    }

    while (!I2C_Transfer_Complete && !I2C_Transfer_Error) {
        // Wait for the transfer to complete
    }
    return (I2C_Transfer_Complete && !I2C_Transfer_Error);
}

static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
    I2C_ResetFlags();
//    I2C_StartupTime();
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_DMA(HumTempI2c, (address << 1), buffer, nrBytes);
    if (status != HAL_OK) {
        return false;
    }

    while (!I2C_Transfer_Complete && !I2C_Transfer_Error) {
        // Wait for the transfer to complete
    }
    return (I2C_Transfer_Complete && !I2C_Transfer_Error);
}

static uint8_t CalcCRC(uint8_t* data, uint8_t length){
	HAL_CRCEx_Polynomial_Set(SensorCrc, CRC_POLYNOMIAL, CRC_BIT_LENGTH);
	uint8_t crc = HAL_CRC_Calculate(SensorCrc, data, length);
	return crc;
}

bool HT_GetMeasurementValues(float* humidity_perc, float* temperature) {
	return HIDS_GetMeasurementValues(humidity_perc, temperature);
}

// Callback function for I2C transfer complete (reception)
// Need to enable: I2C1 global interrupt through EXTI23 (NVIC) for the callbacks to work
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c) {
    if (hi2c != HumTempI2c) {
    	return;
    }
	I2C_Transfer_Complete = true;

//    if(StartUpDone){
//    	I2C_Transfer_Complete = true;
//	}
//	else if(TimestampIsReached(StartupDoneTime)){
//		StartUpDone = true;
//	}
}

// Callback function for I2C transfer complete (transmission)
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef* hi2c) {
    if (hi2c != HumTempI2c) {
    	return;
    }
    I2C_Transfer_Complete = true;
//	if(StartUpDone){
//		I2C_Transfer_Complete = true;
//	}
//	else if(TimestampIsReached(StartupDoneTime)){
//		StartUpDone = true;
//	}
}

// Callback function for I2C error
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef* hi2c) {
    if (hi2c == HumTempI2c) {
        I2C_Transfer_Error = true;
    }
}


