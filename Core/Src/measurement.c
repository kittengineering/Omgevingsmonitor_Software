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
    int32_t vocIndex;
    bool HT_measurementDone;
    bool VOC_measurementDone;
    bool PM_measurementDone;
    bool MIC_measurementDone;
} MeasurementContext;

typedef void (*StartMeasurementFunc)(void);
typedef bool (*IsMeasurementDoneFunc)(void);

typedef struct {
    StartMeasurementFunc startFunc;
    IsMeasurementDoneFunc doneFunc;
    bool* doneFlag;
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

static void VOC_StartMeasurementWrapper(void) {
  Gas_StartMeasurement();
}

static bool VOC_IsMeasurementDoneWrapper(void) {
  return Gas_GetMeasurementValues(&MeasurementCtx.vocIndex);
}

static void PM_StartMeasurementWrapper(void) {
}

static bool PM_IsMeasurementDoneWrapper(void) {
  return true;
}

static void MIC_StartMeasurementWrapper(void) {
  MIC_Start(SAMPLE_RATE_8K, NR_SAMPLES_128);
}

static bool MIC_IsMeasurementDoneWrapper(void) {
  return MIC_MeasurementDone();
}

void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, ADC_HandleTypeDef* ADC_HANDLER) {
  MeasState = MEAS_STATE_INIT;
  batteryInit(ADC_HANDLER);
  if(MeasEnabled.HT_measurementEnabled || MeasEnabled.VOC_measurementEnabled) {
    I2CSensors_Init(sensorI2C);
    if(!HT_DeviceConnected()) {
       Error("Humidity / Temperature sensor NOT connected!");
       MeasEnabled.HT_measurementEnabled = false;
       // HT Device NOT connected, turning LED on RED.
       // CCR1 = Red, CCR3 = Green, CCR4 = Blue.
       TIM2 -> CCR1 = 0;
       TIM2 -> CCR3 = 4000;
       TIM2 -> CCR4 = 4000;
    }else {
      // HT Device is connected, turning led on GREEN.
      // CCR1 = Red, CCR3 = Green, CCR4 = Blue.
      Debug("Humidity / Temperature sensor initialised.");
      TIM2 -> CCR1 = 4000;
      TIM2 -> CCR3 = 0;
      TIM2 -> CCR4 = 4000;
    }
    if(!Gas_DeviceConnected()) {
       Error("SGP device not connected!");
       // SGP Device is NOT connected, turning led on RED.
       HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, 0);
       HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, 1);
       HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, 1);
       MeasEnabled.VOC_measurementEnabled = false;
    }else{
      Debug("SGP sensor initialised.");
      // HT Device is connected, turning led on GREEN.
      HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, 1);
      HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, 0);
      HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, 1);
    }
  }
  if(MeasEnabled.MIC_measurementEnabled) {
    MIC_Init(micI2s);
  }
  uint8_t offset = 0;
  Measurements[offset++] = (MeasurementParameters) {HT_StartMeasurementWrapper, HT_IsMeasurementDoneWrapper, &MeasurementCtx.HT_measurementDone, MeasEnabled.HT_measurementEnabled};
  Measurements[offset++] = (MeasurementParameters) {VOC_StartMeasurementWrapper, VOC_IsMeasurementDoneWrapper, &MeasurementCtx.VOC_measurementDone, MeasEnabled.VOC_measurementEnabled};
  Measurements[offset++] = (MeasurementParameters) {PM_StartMeasurementWrapper, PM_IsMeasurementDoneWrapper, &MeasurementCtx.PM_measurementDone, MeasEnabled.PM_measurementEnabled};
  Measurements[offset++] = (MeasurementParameters) {MIC_StartMeasurementWrapper, MIC_IsMeasurementDoneWrapper, &MeasurementCtx.MIC_measurementDone, MeasEnabled.MIC_measurementEnabled};
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
  MeasurementCtx.vocIndex = 0;
  MeasurementCtx.HT_measurementDone = false;
  MeasurementCtx.VOC_measurementDone = false;
  MeasurementCtx.PM_measurementDone = false;
  MeasurementCtx.MIC_measurementDone = false;
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

    // TODO: Return values and let gadget handle with too high humidity and the sensor values
    // TODO: Check if all measurements are ready for the next measurement before switching states. Only check for the enabled measurements.
    Debug("Processing results.");
    Debug("SGP40 index value: %d", MeasurementCtx.vocIndex);
    Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", MeasurementCtx.humidityPerc, MeasurementCtx.temperature);
    setMeasurement(MeasurementCtx.temperature, MeasurementCtx.humidityPerc, MeasurementCtx.vocIndex);
    checkCharges();
    MeasState = MEAS_STATE_INIT;
    break;

  default:
    // Handle unexpected state
    MeasState = MEAS_STATE_INIT;
    break;
  }
}
float getTemperature(){
  float Temperature = MeasurementCtx.temperature;
  return Temperature;
}

float getHumidity(){
  float Humidity = MeasurementCtx.humidityPerc;
  return Humidity;
}

void Meas_SetEnabledSensors(EnabledMeasurements enabled) {
  uint8_t offset = 0;
  MeasEnabled = enabled;
  Measurements[offset++].enabled = enabled.HT_measurementEnabled;
  Measurements[offset++].enabled = enabled.VOC_measurementEnabled;
  Measurements[offset++].enabled = enabled.PM_measurementEnabled;
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
