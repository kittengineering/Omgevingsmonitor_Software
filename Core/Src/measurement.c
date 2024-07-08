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

typedef void (*StartMeasurementFunc)(void);
typedef bool (*IsMeasurementDoneFunc)(void);

typedef struct {
    StartMeasurementFunc startFunc;
    IsMeasurementDoneFunc doneFunc;
    bool* doneFlag;
    bool enabled;
} MeasurementInfo;


static MeasurementContext Measurement;
static MeasurementInfo Measurements[MEAS_MEASUREMENT_COUNT];
static EnabledMeasurements MeasEnabled;
static MeasurementState MeasState = MEAS_STATE_INIT;
static uint32_t MeasurementTimestamp;
static uint32_t TimeOutTimestamp;
static uint32_t MeasurementDuration = 2000; // Standard interval in between checking if the measurement is done.
static uint32_t TimeOutInterval = 100;
static uint8_t ErrorCount = 0;
static uint8_t CurrentMeasurementIndex = 0;


static void HT_StartMeasurementWrapper(void) {
  HT_StartMeasurement();
}

static bool HT_IsMeasurementDoneWrapper(void) {
    return HT_GetMeasurementValues(&Measurement.humidityPerc, &Measurement.temperature);
}

static void VOC_StartMeasurementWrapper(void) {
  // TODO: Implement VOC wrapper.
}

static bool VOC_IsMeasurementDoneWrapper(void) {
  return true;
}

static void NO_StartMeasurementWrapper(void) {
  // TODO: Implement NO wrapper.
}

static bool NO_IsMeasurementDoneWrapper(void) {
  return true;
}

static void MIC_StartMeasurementWrapper(void) {
//  MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
}

static bool MIC_IsMeasurementDoneWrapper(void) {
    return true;
}

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // Initialise enabled measurements with standard values
  MeasEnabled.HT_measurementEnabled = true;
  MeasEnabled.VOC_measurementEnabled = false;
  MeasEnabled.NO_measurementEnabled = false;
  MeasEnabled.MIC_measurementEnabled = false;
  I2CSensors_Init(sensorI2C);
  HT_SetMeasurementDuration(MeasurementDuration);
  uint8_t offset = 0;
  // TODO: add functionality so that we can set the enabled measurements. This should be done from gadget.c
  Measurements[offset++] = (MeasurementInfo) {HT_StartMeasurementWrapper, HT_IsMeasurementDoneWrapper, &Measurement.HT_measurementDone, MeasEnabled.HT_measurementEnabled};
  Measurements[offset++] = (MeasurementInfo) {HT_StartMeasurementWrapper, HT_IsMeasurementDoneWrapper, &Measurement.VOC_measurementDone, MeasEnabled.VOC_measurementEnabled};
  Measurements[offset++] = (MeasurementInfo) {HT_StartMeasurementWrapper, HT_IsMeasurementDoneWrapper, &Measurement.NO_measurementDone, MeasEnabled.NO_measurementEnabled};
  Measurements[offset++] = (MeasurementInfo){MIC_StartMeasurementWrapper, MIC_IsMeasurementDoneWrapper, &Measurement.MIC_measurementDone, MeasEnabled.MIC_measurementEnabled};
  //	MIC_Init(micI2s);
}

void StartNextMeasurement(void) {
  if(Measurements[CurrentMeasurementIndex].enabled) {
    Measurements[CurrentMeasurementIndex].startFunc();
  }
  CurrentMeasurementIndex++;
}

void Meas_Upkeep(void) {
  switch(MeasState) {
  // TODO: Make check if sensor is available and then don't init if sensor is not found.
  // So first we take the temperature, humidity and microphone first, then the voc

  case MEAS_STATE_INIT:
      Measurement.humidityPerc = 0;
      Measurement.temperature = 0;
      Measurement.HT_measurementDone = false;
      Measurement.VOC_measurementDone = false;
      Measurement.NO_measurementDone = false;
      Measurement.MIC_measurementDone = false;
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
    } else if (Measurements[CurrentMeasurementIndex].doneFunc()) {
        *Measurements[CurrentMeasurementIndex].doneFlag = true;
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
    Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", Measurement.humidityPerc, Measurement.temperature);
    MeasState = MEAS_STATE_INIT;
    break;

  default:
    // Handle unexpected state
    MeasState = MEAS_STATE_INIT;
    break;
  }
}

void Meas_SetEnabledSensors(EnabledMeasurements enabled) {
  uint8_t offset = 0;
  MeasEnabled = enabled;
  Measurements[offset++].enabled = enabled.HT_measurementEnabled;
  Measurements[offset++].enabled = enabled.VOC_measurementEnabled;
  Measurements[offset++].enabled = enabled.NO_measurementEnabled;
  Measurements[offset++].enabled = enabled.MIC_measurementEnabled;

}

void Meas_SetInterval(uint32_t interval_ms) {
  MeasurementDuration = interval_ms;
}

MeasurementState Meas_GetState(void) {
    return MeasState;
}
