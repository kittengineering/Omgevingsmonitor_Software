/*
 * wsenHIDS.c
 *
 *  Created on: Jun 11, 2024
 *      Author: Joris Blankestijn
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "wsenHIDS.h"
#include "utils.h"
#include "stm32l0xx_hal.h"

#define HIDS_I2C_ADDRESS 0x44
#define SERIAL_NUMBER_REG 0x89
#define SOFT_RESET_REG 0x94
#define HIDS_BUFFER_LENGTH 24
#define MEASURE_BUFFER_LENGTH 6
#define SERIAL_BUFFER_LENGTH 6
#define SENSOR_WAIT_TIME_HIGH 9
#define SENSOR_WAIT_TIME_MEDIUM 5
#define SENSOR_WAIT_TIME_LOW 2
#define CRC_MSB_MASK 0x80
#define CRC_BIT_LENGTH 16
#define CRC_POLYNOMIAL 0x31 // CRC-8 polynomial: x^8 + x^5 + x^4 + 1
#define CRC_INIT_VALUE 0xff
#define POW_2_16_MINUS_1 65535.0
#define SENSOR_INITIAL_INTERVAL 1200

HIDSMeasureModes MeasureMode = HIGH_PRECISION;
HIDSHeaterModes HeaterMode = HIGH_PRECISION_1S_200MW;
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;

static uint8_t SerialBuffer[SERIAL_BUFFER_LENGTH] = {0};
static uint8_t MeasureBuffer[MEASURE_BUFFER_LENGTH] = {0};

uint32_t HIDSNextRunTime = SENSOR_INITIAL_INTERVAL;
uint32_t HIDSInterval_ms = SENSOR_INITIAL_INTERVAL;
static bool MeasurementStarted = false;


static void ReadRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
	if (ReadFunction != NULL) {
		ReadFunction(address, buffer, nrBytes);
		HAL_Delay(SENSOR_WAIT_TIME_HIGH);
	}
}

static void WriteRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (WriteFunction != NULL) {
      WriteFunction(address, buffer, nrBytes);
      HAL_Delay(SENSOR_WAIT_TIME_HIGH);
  }
}

static uint8_t CalculateCRC(uint8_t* data, uint8_t length) {
  uint8_t crc = CRC_INIT_VALUE;

  for (uint8_t i = 0; i < length; i++) {
    // XOR byte into least significant byte of crc
    crc ^= data[i];

    for (uint8_t j = 0; j < 8; j++) {
      // If the leftmost (most significant) bit is set
      if (crc & CRC_MSB_MASK) {
        // Shift left and XOR with polynomial
        crc = (crc << 1) ^ CRC_POLYNOMIAL;
      } else {
          crc <<= 1;
      }
    }
  }
  Info("CRC calculated value: 0x%X", crc);
  return crc;
}

void HIDS_EnableHeater(void) {
  // During heater operation, the sensor’s specifications are not valid.
  uint8_t heaterReg = HeaterMode;
  WriteRegister(HIDS_I2C_ADDRESS, &heaterReg, 1);
  Info("Started the heater in mode: %d", heaterReg);
}

void HIDS_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
	ReadFunction = readFunction;
	WriteFunction = writeFunction;
	if(!HIDS_DeviceConnected()) {
		Error("HIDS device not connected!");
		return;
	}
	HIDS_SetMeasurementMode(MeasureMode);
	HIDS_SetHeaterMode(HeaterMode);
	HIDS_EnableHeater();
}

void HIDS_StartMeasurement(void) {
  if(MeasurementStarted) return;
  MeasurementStarted = true;
  WriteRegister(HIDS_I2C_ADDRESS, &MeasureMode, 1);
}

void HIDS_SetHeaterMode(HIDSHeaterModes modeHeater) {
  HeaterMode = modeHeater;
}


static bool checkCRC(uint8_t* data) {
  // Data format: 2 bytes for data, followed by an 8-bit CRC,
  // and then 2 bytes for data with another 8-bit CRC.

	// Check CRC for the first segment
	uint8_t crcData1[2] = {data[0], data[1]};
	uint8_t crc1 = data[2];
	if (CalculateCRC(crcData1, 2) != crc1) {
		Info("CRC check failed for the first segment.");
		return false;
	}

	// Check CRC for the second segment
	uint8_t crcData2[2] = {data[3], data[4]};
	uint8_t crc2 = data[5];
	if (CalculateCRC(crcData2, 2) != crc2) {
		Info("CRC check failed for the second segment.");
		return false;
	}
	return true;
}

bool HIDS_DeviceConnected(void) {
	uint8_t serialReg = SERIAL_NUMBER_REG;
	WriteRegister(HIDS_I2C_ADDRESS, &serialReg, 1);
	ReadRegister(HIDS_I2C_ADDRESS, SerialBuffer, SERIAL_BUFFER_LENGTH);

	for (uint8_t i = 0; i < SERIAL_BUFFER_LENGTH; i++) {
		Info("Device serial ID[%d]: 0x%X", i, SerialBuffer[i]);
	}
	return checkCRC(SerialBuffer);
}

void HIDS_SetMeasurementMode(HIDSMeasureModes modeMeasure) {
	MeasureMode = modeMeasure;
}

bool HIDS_MeasurementReady(void) {
  if(!MeasurementStarted || !TimestampIsReached(HIDSNextRunTime)){
    return false;
  }
  HIDSNextRunTime += HIDSInterval_ms;
  return true;
}

void HIDS_SoftReset(void){
  uint8_t resetReg = SOFT_RESET_REG;
  WriteRegister(HIDS_I2C_ADDRESS, &resetReg, 1);
}

bool HIDS_GetMeasurementValues(float* humidity, float* temperature) {
  if(!HIDS_MeasurementReady()) return false;
  MeasurementStarted = false;
  Info("=-=-=-=New values incoming.=-=-=-=");
  ReadRegister(HIDS_I2C_ADDRESS, MeasureBuffer, MEASURE_BUFFER_LENGTH);
	if(!checkCRC(MeasureBuffer)) {
		Error("GetMeasurementValues CRC check failed.");
		Info("Measure buffer structure:");
		for(uint8_t i = 0; i < MEASURE_BUFFER_LENGTH; i++) {
			Debug("Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
		}
		return false;
	}

	// Humidity formula in percentage:
	//  RH = ((-6 + 125 * SRH) / (2^16 - 1))
	// Temperature formula in degrees Celsius:
	//  T = ((-45 + (175 * ST) / (2^16 - 1)))
	for(uint8_t i = 0; i < MEASURE_BUFFER_LENGTH; i++) {
	      Debug("Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
  }
	*temperature = (((175 * (MeasureBuffer[0] << 8) | MeasureBuffer[1])) / POW_2_16_MINUS_1);
	*temperature += -45;
	*humidity = ((125 * ((MeasureBuffer[3] << 8) | MeasureBuffer[4]) / POW_2_16_MINUS_1));
	*humidity += -6;
	return true;
}
