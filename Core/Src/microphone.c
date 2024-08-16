/*
 * microphone.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include "microphone.h"


// TODO: include arm math libraries differently.
#define CORTEX_M0
//#include "arm_math.h"
//#include "arm_const_structs.h"

static I2S_HandleTypeDef* I2SHandle = NULL;
static NrOfSamples Samples = NR_SAMPLES_128;

static uint16_t AudioRxBuffer[AUDIO_RX_BUFFER] = {0};

static volatile uint32_t StartTime = 0;
static volatile uint32_t StartupDoneTime = 0;
static volatile bool StartUpDone = false;
static volatile bool DataReady = false;
static uint8_t MIC_InitRetries = 0;
static uint8_t MIC_MaxRetries = 3;

void MIC_Init(I2S_HandleTypeDef* i2SHandle) {
  I2SHandle = i2SHandle;
  if (I2SHandle == NULL) {
     Error("Microphone is not initialised.");
     return;
  }
  // Start data receiving to check if MIC is connected.
  HAL_StatusTypeDef status = HAL_I2S_Receive_DMA(I2SHandle, (uint16_t*)AudioRxBuffer, Samples);
  if(status == HAL_ERROR) {
    Error("Microphone NOT initialised.");
    // Setting LED to RED to show mic is not working.
    TIM3 -> CCR1 = 2000;
    TIM3 -> CCR2 = 4000;
    TIM3 -> CCR3 = 4000;
  }
  if(status == HAL_BUSY) {
    Debug("Microphone is BUSY, retrying.");
    // Setting LED to YELLOW to show mic is busy.
    // CCR1 = Red, CCR2 = Green, CCR3 = Blue.
    TIM3 -> CCR1 = 2000;
    TIM3 -> CCR2 = 2000;
    TIM3 -> CCR3 = 4000;
    if(MIC_InitRetries <= MIC_MaxRetries) {
      MIC_InitRetries += 1;
      // Calling function again.
      MIC_Init(i2SHandle);
    }else {
      Debug("Microphone is BUSY and is NOT working after retrying.");
      // Setting LED to RED to show mic is not working.
      // CCR1 = Red, CCR2 = Green, CCR3 = Blue.
      TIM3 -> CCR1 = 2000;
      TIM3 -> CCR2 = 4000;
      TIM3 -> CCR3 = 4000;
    }
  }else {
    Debug("Microphone initialised.");
    // Setting LED to GREEN to show mic is working.
    // CCR1 = Red, CCR2 = Green, CCR3 = Blue.
    TIM3 -> CCR1 = 4000;
    TIM3 -> CCR2 = 2000;
    TIM3 -> CCR3 = 4000;
  }
  // Stop DMA
  HAL_I2S_DMAStop(I2SHandle);
}

//static void CalculateFFT(void) {
//  float32_t IQ[NR_SAMPLES_128 * 2] ={0};      /*! I/Q interleave buffer Required 2x FFT-Size */
//
//  // Hanning window
//  float32_t energyCorrectionFactor = 1.63;
//  float32_t windowingFunc[NR_SAMPLES_128] = {0, 0.00061179, 0.0024457, 0.0054971, 0.0097588, 0.01522, 0.021868, 0.029685,
//  0.038654, 0.048752, 0.059954, 0.072232, 0.085558, 0.099898, 0.11522, 0.13148, 0.14864, 0.16666, 0.1855, 0.20511,
//  0.22544, 0.24644, 0.26806, 0.29025, 0.31295, 0.33611, 0.35967, 0.38358, 0.40777, 0.43218, 0.45676, 0.48145,
//  0.50618, 0.5309, 0.55554, 0.58005, 0.60436, 0.62841, 0.65215, 0.67552, 0.69846, 0.72091, 0.74283, 0.76414,
//  0.78481, 0.80479, 0.82402, 0.84245, 0.86005, 0.87677, 0.89256, 0.9074, 0.92123, 0.93404, 0.94578, 0.95644,
//  0.96597, 0.97437, 0.9816, 0.98766, 0.99252, 0.99618, 0.99862, 0.99985, 0.99985, 0.99862, 0.99618, 0.99252,
//  0.98766, 0.9816, 0.97437, 0.96597, 0.95644, 0.94578, 0.93404, 0.92123, 0.9074, 0.89256, 0.87677, 0.86005,
//  0.84245, 0.82402, 0.80479,0.78481, 0.76414, 0.74283, 0.72091, 0.69846, 0.67552, 0.65215, 0.62841, 0.60436,
//  0.58005, 0.55554, 0.5309, 0.50618, 0.48145, 0.45676, 0.43218, 0.40777, 0.38358, 0.35967, 0.33611, 0.31295,
//  0.29025, 0.26806, 0.24644, 0.22544, 0.20511, 0.1855, 0.16666, 0.14864, 0.13148, 0.11522, 0.099898, 0.085558,
//  0.072232, 0.059954, 0.048752, 0.038654, 0.029685, 0.021868, 0.01522, 0.0097588, 0.0054971, 0.0024457, 0.00061179, 0};
//
//  // Apply the windowing function
//  for(uint16_t i = 0; i < NR_SAMPLES_128; i++) {
//    IQ[i] = (float32_t)(AudioRxBuffer[i] * windowingFunc[i]);
//  }
//
//  uint8_t ifftFlag = 0;
//  uint8_t doBitReverse = 1;
//
//  /* Process the data through the CFFT/CIFFT module */
//  arm_cfft_f32(&arm_cfft_sR_f32_len512, IQ, ifftFlag, doBitReverse);
//  /* Process the data through the Complex Magnitude Module for
//  calculating the magnitude at each bin */
//  arm_cmplx_mag_f32(IQ, FFTResult, NR_SAMPLES_128);
//
//  for(uint8_t i = 0;i < NR_SAMPLES_128; i++) {
//    FFTResult[i] *= energyCorrectionFactor;
//  }
//}

static void UpdateSampleRate(uint32_t sampleRate) {
  if (I2SHandle->Init.AudioFreq == sampleRate) {
    return;
  }
  HAL_I2S_DeInit(I2SHandle);
  I2SHandle->Init.AudioFreq = sampleRate;
  HAL_I2S_Init(I2SHandle);
}

static uint32_t ConvertAudio(uint16_t* data) {
  uint32_t audioValue = data[1] | (data[0] << 16);
  audioValue = audioValue >> 7;
  return audioValue;
}

void MIC_Start(uint32_t sampleRate, uint16_t nrSamples) {
  if (I2SHandle == NULL) {
    Error("Microphone is not initialised.");
    return;
  }
  Debug("In mic start");
  UpdateSampleRate(sampleRate);
  Samples = (NrOfSamples)nrSamples;

  StartTime = GetCurrentHalTicks();
  StartupDoneTime = StartTime + 20;
  StartUpDone = false;
  DataReady = false;

  HAL_StatusTypeDef status = HAL_I2S_Receive_DMA(I2SHandle, (uint16_t*)AudioRxBuffer, Samples >> 1);
//      HAL_I2S_Receive_DMA(I2SHandle, (uint16_t*)AudioRxBuffer,
//          Samples >> 1); //>>1 because reading half word

//  Info("Status %d", status);

}

//static void MIC_ProcessFFT() {
//  CalculateFFT();
//}


void MIC_Print(void) {
  Info("New samples");
  for (uint32_t i = 0; i < Samples; i += 2) {
    uint32_t sample = ConvertAudio(&AudioRxBuffer[i]);
    Info("0x%08x", sample);
  }
}

bool MIC_MeasurementDone(void) {
  if(DataReady) {
    MIC_Print();
    Debug("MIC measurement is done with %i samples.", Samples >> 1);
    return true;
  }
  return false;
}


// #TODO Also include half full callback
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s) {
  if (hi2s != I2SHandle)
    return;

  if (StartUpDone) {
    HAL_I2S_DMAStop(I2SHandle);
    DataReady = true;
    // MIC trigger pin is used to debug when the measurement has started.
//    HAL_GPIO_WritePin(MIC_Trigger_GPIO_Port, MIC_Trigger_Pin, GPIO_PIN_RESET);
    // TODO: Use different pin for MIC_Trigger.
  } else if (TimestampIsReached(StartupDoneTime)) {
    StartUpDone = true;
//    HAL_GPIO_WritePin(MIC_Trigger_GPIO_Port, MIC_Trigger_Pin, GPIO_PIN_SET);
  }
}

//float MIC_GetDB(void) {
//    float sum = 0.0f;
//    float dBValue = 0.0f;
//
//    // Calculate the sum of the magnitudes in FFTResult
//    for (uint16_t i = 0; i < NR_SAMPLES_128; i++) {
//      // Sum of squares of magnitudes
//      sum += FFTResult[i] * FFTResult[i];
//    }
//
//    // Calculate the root mean square (RMS)
//    float rms = sqrtf(sum / NR_SAMPLES_128);
//
//    // Convert the RMS value to dB
//    dBValue = 20.0f * log10f(rms);
//
//    return dBValue;
//}
