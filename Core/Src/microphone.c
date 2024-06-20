/*
 * microphone.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include "stm32l0xx_hal.h"
#include "microphone.h"
#include "utils.h"
#include "gpio.h"

#define AUDIO_RX_BUFFER NR_SAMPLES_128

static I2S_HandleTypeDef* I2SHandle = NULL;

static uint16_t AudioRxBuffer[AUDIO_RX_BUFFER] = {0};

static uint32_t StartTime = 0;
static uint32_t StartupDoneTime = 0;
static volatile bool StartUpDone = false;
static volatile bool DataReady = false;

void MIC_Init(I2S_HandleTypeDef* i2SHandle) {
	I2SHandle = i2SHandle;
}

static void UpdateSampleRate(uint32_t sampleRate){
	if(I2SHandle -> Init.AudioFreq == sampleRate)
		return;

	HAL_I2S_DeInit(I2SHandle);
	I2SHandle -> Init.AudioFreq = sampleRate;
	HAL_I2S_Init(I2SHandle);
}

static uint32_t ConvertAudio(uint16_t* data){
	uint32_t audioValue = data[1] | (data[0]<<16);
	audioValue = audioValue>>7;
	return audioValue;
}

void MIC_Start(uint32_t sampleRate, uint16_t nrSamples) {
	Info("In MIC start.");

	if(I2SHandle == NULL){
		Warning("Microphone is not initialised.");
		return;
	}

//	UpdateSampleRate(sampleRate);

	StartTime = HAL_GetTick();
	StartupDoneTime =StartTime + 20;
	StartUpDone = false;
	DataReady = false;

	HAL_StatusTypeDef status = HAL_I2S_Receive_DMA(I2SHandle, (uint16_t*)AudioRxBuffer, AUDIO_RX_BUFFER>>1); //>>1 because reading half word

	Info("Status %d", status);
}

bool MIC_MeasurementDone(void){
	return DataReady;
}

void MIC_Print(void){
	// TODO: Implement to FFT instead of printing
	Info("New samples");
	//for(int i=2;i<AUDIO_RX_BUFFER;i+=4){
	for(int i=0;i<AUDIO_RX_BUFFER;i+=2){
		uint32_t sample = ConvertAudio(&AudioRxBuffer[i]);
		Info("0x%08x", sample);
	}
}

// #TODO Also include half full callback
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s){
	if(hi2s!=I2SHandle) return;

	if(StartUpDone){
		HAL_I2S_DMAStop(I2SHandle);
		DataReady = true;
		HAL_GPIO_WritePin(MIC_Trigger_GPIO_Port, MIC_Trigger_Pin, GPIO_PIN_RESET);
	}
	else if(TimestampIsReached(StartupDoneTime)){
		StartUpDone = true;
		HAL_GPIO_WritePin(MIC_Trigger_GPIO_Port, MIC_Trigger_Pin, GPIO_PIN_SET);
	}
}

float MIC_GetDB(void) {
	return 0;
}
