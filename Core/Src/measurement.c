/*
 * measurement.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */
#include "stm32l0xx_hal.h"
#include "utils.h"

#include "measurement.h"
#include "I2CSensors.h"
#include "microphone.h"
#include "gasSensor.h"
#include "humidTemp.h"

// TODO context struct instead of seperate variables
static float humidity_perc = 0.0;
static float temperature = 0.0;

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
//  HT_Init(humidTempI2c);
  I2CSensors_Init(sensorI2C);
  //	MIC_Init(micI2s);
//  Gas_Init(airQI2C);
}

void Meas_Start(void) {
  HT_StartMeasurement();
  //	MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
  Gas_StartMeasurement();
}

void Meas_Upkeep(void) {
  Meas_Start();
  if(HT_GetMeasurementValues(&humidity_perc, &temperature)) {
    Info("Humidity value: %3.2f%%, Temperature value: %3.2fC", humidity_perc, temperature);
  }
}

bool Meas_CanSleep(uint32_t* duration_ms) {
  return TimestampIsReached(*duration_ms);
}
