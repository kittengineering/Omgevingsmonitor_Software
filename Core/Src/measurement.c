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

typedef struct {
    float humidity_perc;
    float temperature;
} MeasurementContext;

static MeasurementContext measurement;
static MeasurementState MeasState = MEAS_STATE_START_MEASUREMENT;
static uint32_t MeasurementTimestamp;
static uint32_t MeasurementInterval = 5000; // Standard interval


static bool MeasurementsDone(void) {
  return HT_GetMeasurementValues(&measurement.humidity_perc, &measurement.temperature);
}

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
//  HT_Init(humidTempI2c);
  I2CSensors_Init(sensorI2C);
  //	MIC_Init(micI2s);
//  Gas_Init(airQI2C);
}

void Meas_Start(void) {
  HT_StartMeasurement();
  //	MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
//  Gas_StartMeasurement();
  MeasurementTimestamp = HAL_GetTick() + MeasurementInterval;
}

void Meas_Upkeep(void) {
  switch(MeasState) {
  case MEAS_STATE_INIT:
    measurement.humidity_perc = 0;
    measurement.temperature = 0;
    MeasState = MEAS_STATE_START_MEASUREMENT;
    break;

  case MEAS_STATE_START_MEASUREMENT:
    Meas_Start();
    Info("Measurements running.");
    MeasState = MEAS_STATE_WAIT_FOR_COMPLETION;
    break;

  case MEAS_STATE_WAIT_FOR_COMPLETION:
    if(MeasurementsDone() && TimestampIsReached(MeasurementTimestamp)) {
      Info("Measurements done.");
      MeasState = MEAS_STATE_PROCESS_RESULTS;
    }
    break;

  case MEAS_STATE_PROCESS_RESULTS:
    Info("Processing results.");
    Info("Humidity value: %3.2f%%, Temperature value: %3.2fC", measurement.humidity_perc, measurement.temperature);
    MeasState = MEAS_STATE_INIT;
    break;

  default:
    // Handle unexpected state
    MeasState = MEAS_STATE_INIT;
    break;
  }
}

void Meas_SetInterval(uint32_t interval_ms) {
  MeasurementInterval = interval_ms;
}

MeasurementState Meas_GetState(void) {
    return MeasState;
}
