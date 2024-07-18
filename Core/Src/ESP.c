/*
 * ESP.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#include "ESP.h"

static UART_HandleTypeDef* EspUart = NULL;

void ESP_Init(UART_HandleTypeDef* espUart) {
  EspUart = espUart;
}

static bool ESP_Send(uint8_t* command, uint8_t length) {

  return true;
}

static bool ESP_Receive(uint8_t* reply, uint8_t length) {
  return true;
}


//void I2CSensors_Init(I2C_HandleTypeDef* sensorI2C) {
//    SensorI2C = sensorI2C;
//    HT_Init(ReadI2C, WriteI2C);
//    Gas_Init(ReadI2C, WriteI2C);
//}
//
//static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
//    HAL_StatusTypeDef status = HAL_I2C_Master_Receive_DMA(SensorI2C, (address << 1), buffer, nrBytes);
//    if (status != HAL_OK) {
//        return false;
//    }
//    return true;
//}
//
//static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
//    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_DMA(SensorI2C, (address << 1), buffer, nrBytes);
//    if (status != HAL_OK) {
//        return false;
//    }
//    return true;
//}
