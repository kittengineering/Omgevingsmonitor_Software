/*
 * measurement.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include "humidTemp.h"
#include "measurement.h"
#include "microphone.h"
#include "stm32l0xx_hal.h"
#include "utils.h"

float humidity_perc = 0.0;
float temperature = 0.0;

void Meas_Init(I2C_HandleTypeDef* humidTempI2c, I2S_HandleTypeDef* micI2s){
  HT_Init(humidTempI2c);
  //	MIC_Init(micI2s);
}

void Meas_Start(void) {
  HT_StartMeasurement();
  //	MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
}

void Meas_Upkeep(void) {
  Meas_Start();
  if(HT_GetMeasurementValues(&humidity_perc, &temperature)) {
    Info("Humidity value: %3.2f%%, Temperature value: %3.2fC", humidity_perc, temperature);
  }
}

bool Meas_CanSleep(int *duration_ms) { return false; }
