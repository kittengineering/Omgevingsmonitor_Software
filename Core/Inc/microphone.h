/*
 * microphone.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_MICROPHONE_H_
#define INC_MICROPHONE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gpio.h"
#include "ESP.h"
#include "measurement.h"
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "statusCheck.h"

#define NUMBER_OF_SAMPLES 512
#define AUDIO_RX_BUFFER NR_SAMPLES_512*2

typedef enum {
  SAMPLE_RATE_8K = 8000,
  SAMPLE_RATE_16K = 16000,
  SAMPLE_RATE_32K = 32000,
  SAMPLE_RATE_44_1K = 44100,
  SAMPLE_RATE_48K = 48000
} SampleRates;

typedef enum {
  NR_SAMPLES_128 = 128, //<<2 = 32 bit per channel , 2 channels
  NR_SAMPLES_256 = 256,
  NR_SAMPLES_512 = 512,
  NR_SAMPLES_1024 = 1024
} NrOfSamples;


void MIC_Init(I2S_HandleTypeDef* I2SHandle);
void MIC_Start(uint32_t sampleRate, uint16_t nrSamples);
bool MIC_MeasurementDone(void);
bool MIC_TestMeasurementDone();
float MIC_GetDB(void);



#endif /* INC_MICROPHONE_H_ */
