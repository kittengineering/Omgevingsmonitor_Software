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

#define HIDS_I2C_ADDRESS 0x44
#define HIDS_BUFFER_LENGTH 24
#define MEASURE_BUFFER_LENGTH 6
#define SERIAL_BUFFER_LENGTH 6

HIDSMeasureModes MeasureMode = HIGH_PRECISION;

static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;
static CRC CrcFunction = NULL;

static uint8_t SerialBuffer[SERIAL_BUFFER_LENGTH] = {0};
static uint8_t MeasureBuffer[MEASURE_BUFFER_LENGTH] = {0};

typedef union {
	struct __attribute__((__packed__)) PropertyStructAVG{
		uint8_t AVG_T: 3;
		uint8_t AVG_H: 3;
    }Properties;
    uint8_t RegisterValue: 8;
}AvgRegDef;


//static AvgRegDef AvgReg;

static void ReadRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes){
	if (ReadFunction != NULL) {
		ReadFunction(address, buffer, nrBytes);
	}
}

static void WriteRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes){
    if (WriteFunction != NULL) {
        WriteFunction(address, buffer, nrBytes);
    }
}

static uint8_t CalculateCRC(uint8_t* data, uint8_t length){
	if(CrcFunction != NULL){
		uint8_t crcValue = CrcFunction(data, length);
		Info("CRC calculated value: 0x%X", crcValue);
		return crcValue;
	}
	return 0;
}

//static void InitRegisters(){

//	AvgReg.RegisterValue = 0;
//
//	HidsBuffer[0] = AVG_REG;
//	HidsBuffer[1] = AvgReg.RegisterValue;
//	WriteRegister(HIDS_I2C_ADDRESS, HidsBuffer, 2);
//
//	HidsBuffer[0] = CTRL_1_REG;
//	HidsBuffer[1] = Ctrl1Reg.RegisterValue;
//	WriteRegister(HIDS_I2C_ADDRESS, HidsBuffer, 2);
//
//	HidsBuffer[0] = CTRL_2_REG;
//	HidsBuffer[1] = Ctrl2Reg.RegisterValue;
//	WriteRegister(HIDS_I2C_ADDRESS, HidsBuffer, 2);
//
//	HidsBuffer[0] = CTRL_3_REG;
//	HidsBuffer[1] = Ctrl3Reg.RegisterValue;
//	WriteRegister(HIDS_I2C_ADDRESS, HidsBuffer, 2);
//}

void HIDS_ReadCalibrationRegisters(uint8_t* calibBuffer){
//    for (uint8_t reg = 0; reg < CAL_REGISTERS; ++reg) {
//        ReadRegister(reg, calibBuffer + (reg - CalRegisters[0]), 1);
//    }
}

void HIDS_Init(I2CReadCb readFunction, I2CWriteCB writeFunction, CRC crcFunction){
	ReadFunction = readFunction;
	WriteFunction = writeFunction;
	CrcFunction = crcFunction;
	if(!HIDS_DeviceConnected()){
		Error("HIDS device not connected!");
		return;
	}
	HIDS_StartMeasurement();
}

//void HIDS_SetAverage(HIDSAverageTemperatureModes modeTemp, HIDSAverageHumidityModes modeHum){
//	AvgReg.Properties.AVG_T = modeTemp;
//	AvgReg.Properties.AVG_H = modeHum;
//	HidsBuffer[0] = AVG_REG;
//	HidsBuffer[1] = AvgReg.RegisterValue;
//	WriteRegister(HIDS_I2C_ADDRESS, HidsBuffer, 2);
//}


//void HIDS_SetInterruptMode(HIDSInterruptModes mode){
//	Ctrl3Reg.RegisterValue = mode;
//	HidsBuffer[0] = AVG_REG;
//	HidsBuffer[1] = AvgReg.RegisterValue;
//	WriteRegister(HIDS_I2C_ADDRESS, HidsBuffer, 2);
//}


void HIDS_StartMeasurement(void){
	WriteRegister(HIDS_I2C_ADDRESS, &MeasureMode, 1);
}

void HIDS_SetHeaterEnable(bool heaterEnabled){
//	Ctrl2Reg.Properties.HEATER = heaterEnabled;

}

void HIDS_SetHeaterMode(HIDSHeaterModes modeHeater){

}


static bool checkCRC(uint8_t* data){

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

bool HIDS_DeviceConnected(void){
	uint8_t serialReg = 0x89;
	WriteRegister(HIDS_I2C_ADDRESS, &serialReg, 1);
	HAL_Delay(1);
	ReadRegister(HIDS_I2C_ADDRESS, SerialBuffer, SERIAL_BUFFER_LENGTH);

	for (uint8_t i = 0; i < SERIAL_BUFFER_LENGTH; i++) {
		Info("Device serial ID[%d]: 0x%X", i, SerialBuffer[i]);
	}
	return checkCRC(SerialBuffer);
}

void HIDS_SetMeasurementMode(HIDSMeasureModes modeMeasure){
	MeasureMode = modeMeasure;
}

bool HIDS_MeasurementReady(void){
//	HidsBuffer[0] = STATUS_REG;
//	HidsBuffer[1] = StatusReg.Properties.H_DA;
//	HidsBuffer[2] = StatusReg.Properties.T_DA;
//	ReadRegister(HIDS_I2C_ADDRESS, HidsBuffer, 3);
//	return (HidsBuffer[1] && HidsBuffer[2]);
	return false;
}

bool HIDS_GetMeasurementValues(float* humidity, float* temperature){
	// TODO Bug: Getting weird values from register.
	ReadRegister(HIDS_I2C_ADDRESS, MeasureBuffer, MEASURE_BUFFER_LENGTH);
	if(!checkCRC(MeasureBuffer)){
		Error("GetMeasurementValues CRC check failed.");
		for(uint8_t i = 0; i < MEASURE_BUFFER_LENGTH; i++){
			Debug("Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
		}
		return false;
	}
	// TODO fix these measurements
	*temperature = (float)(-6 +(125 * ((MeasureBuffer[1] << 8) | MeasureBuffer[0]) / (2 ^ 16) - 1));
	*humidity = (MeasureBuffer[4] << 8) | MeasureBuffer[3];
	Info("Humidity value: %9.6f, Temperature value: %9.6f", humidity, temperature);
	return true;
}


