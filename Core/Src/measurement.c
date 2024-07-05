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
    float humidityPerc;
    float temperature;
    bool HT_measurementDone;
    bool VOC_measurementDone;
    bool NO_measurementDone;
    bool MIC_measurementDone;
} MeasurementContext;

typedef struct {
  bool HT_measurement_enabled;
  bool VOC_measurement_enabled;
  bool NO_measurement_enabled;
  bool MIC_measurement_enabled;
}EnabledMeasurements;

typedef bool (*StartMeasurementFunc)(void);
typedef bool (*IsMeasurementDoneFunc)(void);

typedef struct {
    StartMeasurementFunc startFunc;
    IsMeasurementDoneFunc doneFunc;
    bool* doneFlag;
    bool enabled;
} MeasurementInfo;

static MeasurementContext measurement;
static EnabledMeasurements enabledMeasurements;
static MeasurementInfo measurements[MEAS_MEASUREMENT_COUNT];
static MeasurementState MeasState = MEAS_STATE_INIT;
static uint32_t MeasurementTimestamp;
static uint32_t TimeOutTimestamp;
static uint32_t MeasurementDuration = 5000; // Standard interval in between checking if the measurements are done.
static uint32_t TimeOutInterval = 100;
static uint8_t ErrorCount = 0;
static uint8_t CurrentMeasurementIndex = 0;

//static bool MeasurementsDone(void) {
//  return HT_GetMeasurementValues(&measurement.humidity_perc, &measurement.temperature);
//}

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // TODO: Add the ability to turn off sensors
  I2CSensors_Init(sensorI2C);
  HT_SetMeasurementDuration(MeasurementDuration);
  //	MIC_Init(micI2s);
}

void Meas_Start(void) {
  HT_StartMeasurement();
  //	MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
//  Gas_StartMeasurement();

}

void StartNextMeasurement(void) {
    for (; CurrentMeasurementIndex < MEAS_MEASUREMENT_COUNT; CurrentMeasurementIndex++) {
      if (measurements[CurrentMeasurementIndex].enabled) {
          measurements[CurrentMeasurementIndex].startFunc();
          break;
      }
    }
}

void Meas_Upkeep(void) {
  switch(MeasState) {

  // TODO: Make sure measuring the sensors is in order.
  // TODO: Make check if sensor is available and then don't init if sensor is not found.
  // So first we take the temperature, humidity and microphone first, then the voc
  // TODO: Make states for every sensor?

  case MEAS_STATE_INIT:
      measurement.humidityPerc = 0;
      measurement.temperature = 0;
      measurement.HT_measurementDone = false;
      measurement.VOC_measurementDone = false;
      measurement.NO_measurementDone = false;
      measurement.MIC_measurementDone = false;
      CurrentMeasurementIndex = 0;
      Info("Measurements running for: %d ms", MeasurementDuration);
      MeasurementTimestamp = HAL_GetTick() + MeasurementDuration;
      MeasState = MEAS_STATE_START_NEXT_MEASUREMENT;
      break;

  case MEAS_STATE_START_NEXT_MEASUREMENT:
    if (CurrentMeasurementIndex < MEAS_MEASUREMENT_COUNT) {
       StartNextMeasurement();
       if (CurrentMeasurementIndex < MEAS_MEASUREMENT_COUNT) {
           MeasState = MEAS_STATE_WAIT_FOR_COMPLETION;
       } else {
           MeasState = MEAS_STATE_PROCESS_RESULTS;
       }
   } else {
       MeasState = MEAS_STATE_PROCESS_RESULTS;
   }
   break;

  case MEAS_STATE_WAIT_FOR_COMPLETION:
    if (ErrorCount >= MEAS_MAX_RETRY_ATTEMPTS) {
        Error("Measurements timeout reached, restarting measurements.");
        ErrorCount = 0;
        MeasState = MEAS_STATE_INIT;
    } else if (measurements[CurrentMeasurementIndex].doneFunc()) {
        *measurements[CurrentMeasurementIndex].doneFlag = true;
        Info("Measurement %d completed.", CurrentMeasurementIndex);
        CurrentMeasurementIndex++;
        MeasState = MEAS_STATE_START_NEXT_MEASUREMENT;
    } else if (TimestampIsReached(TimeOutTimestamp) && TimestampIsReached(MeasurementTimestamp)) {
        Debug("Measurement %d not done yet after interval. Retrying.", CurrentMeasurementIndex);
        ErrorCount += 1;
        TimeOutTimestamp = HAL_GetTick() + TimeOutInterval;
    }
    break;

  case MEAS_STATE_PROCESS_RESULTS:
    Debug("Processing results.");
    // TODO: Return values and let gadget handle with too high humidity
    Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", measurement.humidityPerc, measurement.temperature);
    MeasState = MEAS_STATE_INIT;
    break;

  default:
    // Handle unexpected state
    MeasState = MEAS_STATE_INIT;
    break;
  }
}

void Meas_SetEnabledSensors(EnabledMeasurements enabled) {
    enabledMeasurements = enabled;
    measurements[0].enabled = enabled.HT_measurement_enabled;
    measurements[1].enabled = enabled.MIC_measurement_enabled;
    // Set other measurements' enabled status similarly
}

void Meas_SetInterval(uint32_t interval_ms) {
  MeasurementDuration = interval_ms;
}

MeasurementState Meas_GetState(void) {
    return MeasState;
}
