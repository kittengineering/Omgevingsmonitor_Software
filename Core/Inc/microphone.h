/*
 * microphone.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_MICROPHONE_H_
#define INC_MICROPHONE_H_

typedef enum {
  SAMPLE_RATE_8K = 8000,
  SAMPLE_RATE_16K = 16000,
  SAMPLE_RATE_32K = 32000,
  SAMPLE_RATE_44_1K = 44100,
  SAMPLE_RATE_48K = 48000,
  SAMPLE_RATE_96K = 96000
} SampleRates;

typedef enum {
  NR_SAMPLES_128 = 128 << 2, //<<2 = 32 bit per channel , 2 channels
  NR_SAMPLES_256 = 256 << 2,
  NR_SAMPLES_512 = 512 << 2,
  NR_SAMPLES_1024 = 1024 << 2,
  NR_SAMPLES_2048 = 2048 << 2,
  NR_SAMPLES_4096 = 4096 << 2
} NrOfSamples;

void MIC_Init(I2S_HandleTypeDef* I2SHandle);
void MIC_Start(uint32_t sampleRate, uint16_t nrSamples);
bool MIC_MeasurementDone(void);
float MIC_GetDB(void);
void MIC_GetSample(void);

#endif /* INC_MICROPHONE_H_ */
