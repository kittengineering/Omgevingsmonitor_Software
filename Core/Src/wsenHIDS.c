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

static HIDSHeaterModes HeaterMode = HHM_HIGH_PRECISION_1S_200MW;
static HIDSMeasureModes MeasureMode = HMM_HIGH_PRECISION;
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;

static uint8_t SerialBuffer[HIDS_SERIAL_BUFFER_LENGTH] = {0};
static uint8_t MeasureBuffer[HIDS_MEASURE_BUFFER_LENGTH] = {0};

static uint32_t HIDSNextRunTime = HIDS_SENSOR_INITIAL_INTERVAL;
static uint32_t HIDSInterval_ms = HIDS_SENSOR_INITIAL_INTERVAL;
//static uint32_t SensorNextRunTime = HIDS_SENSOR_WAIT_TIME_HIGH;
//static uint32_t SensorWaitTime_ms = HIDS_SENSOR_WAIT_TIME_HIGH;
static bool MeasurementStarted = false;

static void ReadRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
	if (ReadFunction != NULL) {
		ReadFunction(address, buffer, nrBytes);
	}
}

static void WriteRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (WriteFunction != NULL) {
    WriteFunction(address, buffer, nrBytes);
  }
}

static uint8_t CalculateCRC(uint8_t* data, uint8_t length) {
  uint8_t crc = HIDS_CRC_INIT_VALUE;

  for (uint8_t i = 0; i < length; i++) {
    // XOR byte into least significant byte of crc
    crc ^= data[i];

    for (uint8_t j = 0; j < 8; j++) {
      // If the leftmost (most significant) bit is set
      if (crc & HIDS_CRC_MSB_MASK) {
        // Shift left and XOR with polynomial
        crc = (crc << 1) ^ HIDS_CRC_POLYNOMIAL;
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
//	HIDS_EnableHeater();
	// TODO: Enable heater after measurement is done and humidity is above a certain percentage, use formula.
}

void HIDS_StartMeasurement(void) {
  if(MeasurementStarted) return;
  HIDSNextRunTime += GetCurrentHalTicks() + HIDSInterval_ms;
  MeasurementStarted = true;
  WriteRegister(HIDS_I2C_ADDRESS, &MeasureMode, 1);
}

void HIDS_SetHeaterMode(HIDSHeaterModes modeHeater) {
  HeaterMode = modeHeater;
}

static bool CheckCRC(uint8_t* data) {
  // Data format: 2 bytes for data, followed by an 8-bit CRC

	// Check CRC for the first segment
	uint8_t crcData1[2] = {data[0], data[1]};
	uint8_t crc1 = data[2];
	if (CalculateCRC(crcData1, 2) != crc1) {
		Error("CRC check failed for the first segment.");
		return false;
	}

	// Check CRC for the second segment
	uint8_t crcData2[2] = {data[3], data[4]};
	uint8_t crc2 = data[5];
	if (CalculateCRC(crcData2, 2) != crc2) {
		Error("CRC check failed for the second segment.");
		return false;
	}
	return true;
}

bool HIDS_DeviceConnected(void) {
	uint8_t serialReg = HIDS_SERIAL_NUMBER_REG;
	WriteRegister(HIDS_I2C_ADDRESS, &serialReg, 1);
	HAL_Delay(30);
	ReadRegister(HIDS_I2C_ADDRESS, SerialBuffer, HIDS_SERIAL_BUFFER_LENGTH);

	for (uint8_t i = 0; i < HIDS_SERIAL_BUFFER_LENGTH; i++) {
		Info("Device serial ID[%d]: 0x%X", i, SerialBuffer[i]);
	}
	return CheckCRC(SerialBuffer);
}

void HIDS_SetMeasurementMode(HIDSMeasureModes modeMeasure) {
	MeasureMode = modeMeasure;
}

bool HIDS_MeasurementReady(void) {
  if(!TimestampIsReached(HIDSNextRunTime)){
    return false;
  }
  if(!MeasurementStarted){
    HIDS_StartMeasurement();
    return false;
  }
  return true;
}

void HIDS_SoftReset(void){
  uint8_t resetReg = HIDS_SOFT_RESET_REG;
  WriteRegister(HIDS_I2C_ADDRESS, &resetReg, 1);
}

bool HIDS_GetMeasurementValues(float* humidity, float* temperature) {
  // TODO: fix measurement ready so it doesn't start new measurement from here, but from measurement.c

  if(!HIDS_MeasurementReady()) return false;
  MeasurementStarted = false;
  Info("=-=-=-=New values incoming.=-=-=-=");
  ReadRegister(HIDS_I2C_ADDRESS, MeasureBuffer, HIDS_MEASURE_BUFFER_LENGTH);
	if(!CheckCRC(MeasureBuffer)) {
		Error("GetMeasurementValues CRC check failed.");
		Info("Measure buffer structure:");
		for(uint8_t i = 0; i < HIDS_MEASURE_BUFFER_LENGTH; i++) {
			Debug("Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
		}
		return false;
	}

	// Humidity formula in percentage:
	//  RH = ((-6 + 125 * SRH) / (2^16 - 1))
	// Temperature formula in degrees Celsius:
	//  T = ((-45 + (175 * ST) / (2^16 - 1)))
	for(uint8_t i = 0; i < HIDS_MEASURE_BUFFER_LENGTH; i++) {
	  Debug("Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
  }
	*temperature = (((175 * (MeasureBuffer[0] << 8) | MeasureBuffer[1])) / HIDS_POW_2_16_MINUS_1);
	*temperature += -45;
	*humidity = ((125 * ((MeasureBuffer[3] << 8) | MeasureBuffer[4]) / HIDS_POW_2_16_MINUS_1));
	*humidity += -6;
	return true;
}
