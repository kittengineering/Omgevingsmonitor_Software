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
#include "stm32l0xx_hal.h"
#include "utils.h"

#define AUDIO_RX_BUFFER NR_SAMPLES_128 * 4 // * 4 because of 32 bit per channel, 2 channels

typedef enum {
  SAMPLE_RATE_8K = 8000,
  SAMPLE_RATE_16K = 16000,
  SAMPLE_RATE_32K = 32000,
  SAMPLE_RATE_44_1K = 44100
} SampleRates;

typedef enum {
  NR_SAMPLES_128 = 128, //<<2 = 32 bit per channel , 2 channels
  NR_SAMPLES_256 = 256,
  NR_SAMPLES_512 = 512
} NrOfSamples;

void MIC_Init(I2S_HandleTypeDef* I2SHandle);
void MIC_Start(uint32_t sampleRate, uint16_t nrSamples);
bool MIC_MeasurementDone(void);
float MIC_GetDB(void);


#endif /* INC_MICROPHONE_H_ */
