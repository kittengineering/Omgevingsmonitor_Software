/*
 * I2CSensors.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include "I2CSensors.h"
#include "humidTemp.h"
#include "gasSensor.h"

static I2C_HandleTypeDef* SensorI2C = NULL;

static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

void I2CSensors_Init(I2C_HandleTypeDef* sensorI2C) {
    SensorI2C = sensorI2C;
    HT_Init(ReadI2C, WriteI2C);
    Gas_Init(ReadI2C, WriteI2C);
}

static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive_DMA(SensorI2C, (address << 1), buffer, nrBytes);
    if (status != HAL_OK) {
        return false;
    }
    return true;
}

static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_DMA(SensorI2C, (address << 1), buffer, nrBytes);
    if (status != HAL_OK) {
        return false;
    }
    return true;
}
