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

#define MEAS_MAX_RETRY_ATTEMPTS 3

typedef struct {
    float humidity_perc;
    float temperature;
} MeasurementContext;

static MeasurementContext measurement;
static MeasurementState MeasState = MEAS_STATE_START_MEASUREMENT;
static uint32_t MeasurementTimestamp;
static uint32_t TimeOutTimestamp;
static uint32_t MeasurementDuration = 5000; // Standard interval in between checking if the measurements are done.
static uint32_t TimeOutInterval = 100;
static uint8_t ErrorCount = 0;

static bool MeasurementsDone(void) {
  return HT_GetMeasurementValues(&measurement.humidity_perc, &measurement.temperature);
}

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  I2CSensors_Init(sensorI2C);
  HT_SetMeasurementDuration(MeasurementDuration);
  //	MIC_Init(micI2s);
}

void Meas_Start(void) {
  HT_StartMeasurement();
  //	MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
//  Gas_StartMeasurement();
  MeasurementTimestamp = HAL_GetTick() + MeasurementDuration;
}

void Meas_Upkeep(void) {
  switch(MeasState) {
  case MEAS_STATE_INIT:
    measurement.humidity_perc = 0;
    measurement.temperature = 0;
    MeasState = MEAS_STATE_START_MEASUREMENT;
    Info("Measurements running for: %d ms", MeasurementDuration);
    break;

  case MEAS_STATE_START_MEASUREMENT:
    Meas_Start();
    Debug("Measurements started.");
    MeasState = MEAS_STATE_WAIT_FOR_COMPLETION;
    break;

  case MEAS_STATE_WAIT_FOR_COMPLETION:
    if(ErrorCount >= MEAS_MAX_RETRY_ATTEMPTS) {
      Error("Measurements timeout reached, restarting measurements.");
      ErrorCount = 0;
      MeasState = MEAS_STATE_START_MEASUREMENT;
    }
    if(MeasurementsDone()) {
      if(TimestampIsReached(MeasurementTimestamp)) {
        Info("All measurements are done.");
        MeasState = MEAS_STATE_PROCESS_RESULTS;
      }
    }
    else if(TimestampIsReached(TimeOutTimestamp) && TimestampIsReached(MeasurementTimestamp)) {
      // Measurements not done yet,
      // something might be wrong retrying before switching states.
      Debug("Measurements not done yet after interval. Retrying.");
      ErrorCount += 1;
      TimeOutTimestamp = HAL_GetTick() + TimeOutInterval;
    }
    break;

  case MEAS_STATE_PROCESS_RESULTS:
    Debug("Processing results.");
    // TODO: Return values and let gadget handle with too high humidity
    Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", measurement.humidity_perc, measurement.temperature);
    MeasState = MEAS_STATE_INIT;
    break;

  default:
    // Handle unexpected state
    MeasState = MEAS_STATE_INIT;
    break;
  }
}

void Meas_SetInterval(uint32_t interval_ms) {
  MeasurementDuration = interval_ms;
}

MeasurementState Meas_GetState(void) {
    return MeasState;
}
