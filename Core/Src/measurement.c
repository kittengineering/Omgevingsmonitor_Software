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
    bool HT_measurementReady;
    bool VOC_measurementReady;
    bool NO_measurementReady;
    bool MIC_measurementReady;
} MeasurementContext;

typedef void (*StartMeasurementFunc)(void);
typedef bool (*IsMeasurementDoneFunc)(void);
typedef bool (*IsMeasurementReadyFunc)(void);

typedef struct {
    StartMeasurementFunc startFunc;
    IsMeasurementDoneFunc doneFunc;
    IsMeasurementReadyFunc readyFunc;
    bool* doneFlag;
    bool* readyFlag;
    bool enabled;
} MeasurementParameters;

static MeasurementContext MeasurementCtx;
static MeasurementParameters Measurements[MEAS_MEASUREMENT_COUNT];
static EnabledMeasurements MeasEnabled;
static MeasurementState MeasState = MEAS_STATE_INIT;
static uint8_t CurrentMeasurementIndex = 0;

static void HT_StartMeasurementWrapper(void) {
  HT_StartMeasurement();
}

static bool HT_IsMeasurementDoneWrapper(void) {
  return HT_GetMeasurementValues(&MeasurementCtx.humidityPerc, &MeasurementCtx.temperature);
}

static bool HT_IsMeasurementReadyWrapper(void) {
//  return HT_GetMeasurementValues(&MeasurementCtx.humidityPerc, &MeasurementCtx.temperature);
  return false;
}

static void VOC_StartMeasurementWrapper(void) {
  // TODO: Implement VOC wrapper.
}

static bool VOC_IsMeasurementDoneWrapper(void) {
  return true;
}

static bool VOC_IsMeasurementReadyWrapper(void) {
  return false;
}

static void NO_StartMeasurementWrapper(void) {
  // TODO: Implement NO wrapper.
}

static bool NO_IsMeasurementDoneWrapper(void) {
  return true;
}

static bool NO_IsMeasurementReadyWrapper(void) {
  return false;
}

static void MIC_StartMeasurementWrapper(void) {
//  MIC_Start(SAMPLE_RATE_48K, NR_SAMPLES_128);
}

static bool MIC_IsMeasurementDoneWrapper(void) {
    return true;
}

static bool MIC_IsMeasurementReadyWrapper(void) {
  return false;
}

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // TODO: Add 1 duty cycle variable.
  MeasState = MEAS_STATE_INIT;
  // TODO: If sensor not found, then disable it and give error.
  if(MeasEnabled.HT_measurementEnabled || MeasEnabled.VOC_measurementEnabled) {
    I2CSensors_Init(sensorI2C);
    if(!HT_DeviceConnected()) {
       Error("HT device not connected!");
       MeasEnabled.HT_measurementEnabled = false;
       return;
    }
    if(!Gas_DeviceConnected()) {
       Error("SGP device not connected!");
       MeasEnabled.VOC_measurementEnabled = false;
       return;
    }
  }
  if(MeasEnabled.MIC_measurementEnabled) {
//    MIC_Init(micI2s);
  }
  uint8_t offset = 0;
  Measurements[offset++] = (MeasurementParameters) {HT_StartMeasurementWrapper, HT_IsMeasurementDoneWrapper, HT_IsMeasurementReadyWrapper, &MeasurementCtx.HT_measurementDone, &MeasurementCtx.HT_measurementReady, MeasEnabled.HT_measurementEnabled};
  Measurements[offset++] = (MeasurementParameters) {VOC_StartMeasurementWrapper, VOC_IsMeasurementDoneWrapper, VOC_IsMeasurementReadyWrapper, &MeasurementCtx.VOC_measurementDone, &MeasurementCtx.VOC_measurementReady, MeasEnabled.VOC_measurementEnabled};
  Measurements[offset++] = (MeasurementParameters) {NO_StartMeasurementWrapper, NO_IsMeasurementDoneWrapper, NO_IsMeasurementReadyWrapper, &MeasurementCtx.NO_measurementDone, &MeasurementCtx.NO_measurementReady, MeasEnabled.NO_measurementEnabled};
  Measurements[offset++] = (MeasurementParameters) {MIC_StartMeasurementWrapper, MIC_IsMeasurementDoneWrapper, MIC_IsMeasurementReadyWrapper, &MeasurementCtx.MIC_measurementDone, &MeasurementCtx.MIC_measurementReady, MeasEnabled.MIC_measurementEnabled};
}

void StartMeasurements(void) {
  for(CurrentMeasurementIndex = 0; CurrentMeasurementIndex < MEAS_MEASUREMENT_COUNT; CurrentMeasurementIndex++) {
    if(Measurements[CurrentMeasurementIndex].enabled) {
      Measurements[CurrentMeasurementIndex].startFunc();
    }
  }
}

void ResetMeasurements(void) {
  MeasurementCtx.humidityPerc = 0;
  MeasurementCtx.temperature = 0;
  MeasurementCtx.HT_measurementDone = false;
  MeasurementCtx.VOC_measurementDone = false;
  MeasurementCtx.NO_measurementDone = false;
  MeasurementCtx.MIC_measurementDone = false;

  MeasurementCtx.HT_measurementReady = false;
  MeasurementCtx.VOC_measurementReady = false;
  MeasurementCtx.NO_measurementReady = false;
  MeasurementCtx.MIC_measurementReady = false;
}

bool MeasurementsCompleted(void) {
  for(CurrentMeasurementIndex = 0; CurrentMeasurementIndex < MEAS_MEASUREMENT_COUNT; CurrentMeasurementIndex++) {
    if(Measurements[CurrentMeasurementIndex].enabled) {
      if(Measurements[CurrentMeasurementIndex].doneFunc()) {
        *Measurements[CurrentMeasurementIndex].doneFlag = true;
      }else {
        return false;
      }
    }
  }
  return true;
}

bool MeasurementsReady(void) {
  for(CurrentMeasurementIndex = 0; CurrentMeasurementIndex < MEAS_MEASUREMENT_COUNT; CurrentMeasurementIndex++) {
     if(Measurements[CurrentMeasurementIndex].enabled) {
       if(Measurements[CurrentMeasurementIndex].readyFunc()) {
         *Measurements[CurrentMeasurementIndex].readyFlag = true;
       }else {
         return false;
       }
     }
   }
   return true;
}

void Meas_Upkeep(void) {
  switch(MeasState) {
  case MEAS_STATE_OFF:
    Debug("Measurements are turned off.");
    break;

  case MEAS_STATE_INIT:
    ResetMeasurements();
    MeasState = MEAS_STATE_START_MEASUREMENTS;
    break;

  case MEAS_STATE_START_MEASUREMENTS:
    StartMeasurements();
    MeasState = MEAS_STATE_WAIT_FOR_COMPLETION;
   break;

  case MEAS_STATE_WAIT_FOR_COMPLETION:
    if(MeasurementsCompleted()) {
      MeasState = MEAS_STATE_PROCESS_RESULTS;
    }
    break;

  case MEAS_STATE_PROCESS_RESULTS:
    Debug("Processing results.");
    // TODO: Return values and let gadget handle with too high humidity and the sensor values
    // TODO: Check if all measurements are ready for the next measurement before switching states. Only check for the enabled measurements.
    Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", MeasurementCtx.humidityPerc, MeasurementCtx.temperature);
    MeasState = MEAS_STATE_INIT;
    break;

  case MEAS_STATE_WAIT_FOR_READY:

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


static void Meas_TurnOff(void) {
  MeasState = MEAS_STATE_OFF;
  // Disabling all sensors
  uint8_t offset = 0;
  Measurements[offset++].enabled = false;
  Measurements[offset++].enabled = false;
  Measurements[offset++].enabled = false;
  Measurements[offset++].enabled = false;
  // TODO: Add the turning off the heater for the sgp40
}

MeasurementState Meas_GetState(void) {
    return MeasState;
}

void Meas_DeInit(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // TODO: Add de-init like the i2c, i2s and all the pins.
  Meas_TurnOff();
  HAL_I2C_DeInit(sensorI2C);
  HAL_I2S_DeInit(micI2s);

}
