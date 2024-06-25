/*
 * humidTemp.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "humidTemp.h"
#include "utils.h"
#include "wsenHIDS.h"

#define HIDS_BUFFER 256
#define HIDS_I2C_ADDRESS 0x5F

static I2C_HandleTypeDef* HumTempI2c = NULL;

static volatile bool I2C_Transfer_Complete = false;
static volatile bool I2C_Transfer_Error = false;

static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);

static volatile bool StartUpDone = false;
static volatile bool DataReady = false;

void HT_Init(I2C_HandleTypeDef* humTempI2c) {
  HumTempI2c = humTempI2c;
  HIDS_Init(ReadI2C, WriteI2C);
}

static void I2C_ResetFlags() {
  I2C_Transfer_Complete = false;
  I2C_Transfer_Error = false;
}

static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  I2C_ResetFlags();
  HAL_StatusTypeDef status =
      HAL_I2C_Master_Receive_DMA(HumTempI2c, (address << 1), buffer, nrBytes);
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
  HAL_StatusTypeDef status =
      HAL_I2C_Master_Transmit_DMA(HumTempI2c, (address << 1), buffer, nrBytes);
  if (status != HAL_OK) {
    return false;
  }

  while (!I2C_Transfer_Complete && !I2C_Transfer_Error) {
    // Wait for the transfer to complete
  }
  return (I2C_Transfer_Complete && !I2C_Transfer_Error);
}

void HT_StartMeasurement(void){
  HIDS_StartMeasurement();
}

bool HT_GetMeasurementValues(float* humidity_perc, float* temperature) {
  return HIDS_GetMeasurementValues(humidity_perc, temperature);
}

// Callback function for I2C transfer complete (reception)
// Need to enable: I2C1 global interrupt through EXTI23 (NVIC) for the callbacks
// to work
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c) {
  if (hi2c != HumTempI2c) {
    return;
  }
  I2C_Transfer_Complete = true;
}

// Callback function for I2C transfer complete (transmission)
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef* hi2c) {
  if (hi2c != HumTempI2c) {
    return;
  }
  I2C_Transfer_Complete = true;
}

// Callback function for I2C error
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef* hi2c) {
  if (hi2c == HumTempI2c) {
    I2C_Transfer_Error = true;
  }
}
