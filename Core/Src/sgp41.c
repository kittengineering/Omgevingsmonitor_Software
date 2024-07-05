/*
 * sgp41.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */
#include "sgp41.h"
#include "utils.h"
#include "stm32l0xx_hal.h"

// sgp41_execute_conditioning command must be called from idle mode
// before the master calls the first sgp41_measure_raw_signals command
// Heat hotplate for 10 seconds then you can measure
#define SGP_I2C_ADDRESS 0x59
#define SGP_CRC_MSB_MASK 0x80
#define SGP_CRC_BIT_LENGTH 8
#define SGP_CRC_POLYNOMIAL 0x31 // CRC-8 polynomial: x^8 + x^5 + x^4 + 1
#define SGP_CRC_INIT_VALUE 0xff
#define LONG_COMMAND_BUFFER_LENGTH 8
#define SHORT_COMMAND_BUFFER_LENGTH 2
#define SENSOR_WAIT_DELAY 20
static bool MeasurementStarted = false;

static bool CheckCRC(uint8_t* data, uint8_t length);
static uint8_t CalculateCRC(uint8_t* data, uint8_t length);

static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;
//static uint8_t ExecuteConditioningBuffer[LONG_COMMAND_BUFFER_LENGTH] = {0x26, 0x12, 0x80, 0x00, 0xA2, 0x66, 0x66, 0x93};
//static uint8_t MeasureRawSignalsBuffer[LONG_COMMAND_BUFFER_LENGTH] = {0x26, 0x19, 0x80, 0x00, 0xA2, 0x66, 0x93};
//static uint8_t ExecuteSelfTestBuffer[SHORT_COMMAND_BUFFER_LENGTH] = {0x28, 0x0E};
//static uint8_t TurnHeaterOffBuffer[SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x15};
//static uint8_t GetSerialNumberBuffer[SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x82};
//static uint8_t SoftResetBuffer[SHORT_COMMAND_BUFFER_LENGTH] = {0x00, 0x06};


static void ReadRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (ReadFunction != NULL) {
    ReadFunction(address, buffer, nrBytes);
//    HAL_Delay(SENSOR_WAIT_DELAY);
  }
}

static void WriteRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (WriteFunction != NULL) {
      WriteFunction(address, buffer, nrBytes);
//      HAL_Delay(SENSOR_WAIT_DELAY);
  }
}

void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
  ReadFunction = readFunction;
  WriteFunction = writeFunction;
  if(!SGP_DeviceConnected()) {
    Error("SGP device not connected!");
    return;
  }
}

void SGP_StartMeasurement(void) {
//  WriteRegister(SGP_I2C_ADDRESS, MeasureRawSignalsBuffer, 2);
}

bool SGP_DeviceConnected(void) {
//  uint8_t serialReg = SERIAL_NUMBER_REG;
//  WriteRegister(HIDS_I2C_ADDRESS, &serialReg, 1);
//  ReadRegister(HIDS_I2C_ADDRESS, SerialBuffer, SERIAL_BUFFER_LENGTH);
//
//  for (uint8_t i = 0; i < SERIAL_BUFFER_LENGTH; i++) {
//    Info("Device serial ID[%d]: 0x%X", i, SerialBuffer[i]);
//  }
//  return CheckCRC(SerialBuffer);
  // TODO: Implement logic to read serial number
  return false;
}

static bool CheckCRC(uint8_t* data, uint8_t length) {
  // Checking crc per segment
  for(uint8_t i = 0; i < length; i += 4) {
    uint8_t crcData[2] = {data[i], data[i + 1]};
    uint8_t crc = data[i + 2];

    if (CalculateCRC(crcData, 2) != crc) {
        Error("CRC check failed for segment: %d.", i + 1);
        return false;
    }
  }
  return true;
}

static uint8_t CalculateCRC(uint8_t* data, uint8_t length) {
  uint8_t crc = SGP_CRC_INIT_VALUE;

  for (uint8_t i = 0; i < length; i++) {
    // XOR byte into least significant byte of crc
    crc ^= data[i];

    for (uint8_t j = 0; j < 8; j++) {
      // If the leftmost (most significant) bit is set
      if (crc & SGP_CRC_MSB_MASK) {
        // Shift left and XOR with polynomial
        crc = (crc << 1) ^ SGP_CRC_POLYNOMIAL;
      } else {
          crc <<= 1;
      }
    }
  }
  Info("CRC calculated value: 0x%X", crc);
  return crc;
}
