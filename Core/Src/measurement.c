/*
 * measurement.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include "measurement.h"
#include "stm32l0xx_hal.h"
#include "microphone.h"
#include "humidTemp.h"

void Meas_Init(I2C_HandleTypeDef* humidTempI2c, I2S_HandleTypeDef* micI2s, CRC_HandleTypeDef* sensorCrc){
	HT_Init(humidTempI2c, sensorCrc);
//	MIC_Init(micI2s);

}

void Meas_Start(void){

//	MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
}

void Meas_Upkeep(void){
}

bool Meas_CanSleep(int* duration_ms){
	return false;
}

