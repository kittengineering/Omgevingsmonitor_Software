/*
 * measurement.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_MEASUREMENT_H_
#define INC_MEASUREMENT_H_

#include "stm32l0xx_hal.h"
#include <stdbool.h>
#include "ESP.h"
#include "utils.h"


#define MEAS_MAX_RETRY_ATTEMPTS 3
#define MEAS_MEASUREMENT_COUNT 3

typedef enum {
  MIC_STATE_INIT,
  MIC_STATE_START_MEASUREMENT,
  MIC_STATE_WAIT_FOR_COMPLETION,
  MIC_STATE_WAIT,
  MIC_STATE_OFF
}MicrophoneState;

typedef enum {
    MEAS_STATE_INIT,
    MEAS_STATE_START_MEASUREMENTS,
    MEAS_STATE_WAIT_FOR_COMPLETION,
    MEAS_STATE_PROCESS_RESULTS,
    MEAS_STATE_WAIT_FOR_READY,
    MEAS_STATE_OFF,
    MEAS_STATE_WAIT
} MeasurementState;

// TODO: add battery measurement
typedef struct {
    bool HT_measurementEnabled;
    bool VOC_measurementEnabled;
    bool PM_measurementEnabled;
    bool MIC_measurementEnabled;
} EnabledMeasurements;

typedef struct {
  bool HT_Tested;
  bool VOC_Tested;
  bool MIC_Tested;
  bool ESP_Tested;
}MeasurementTested;


void Meas_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, ADC_HandleTypeDef* ADC_HANDLER);
MeasurementState Meas_Upkeep(void);
MeasurementState Meas_GetState(void);
void Meas_SetEnabledSensors(EnabledMeasurements enabled);
void Meas_DeInit(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s);
void SetESPMeasurementDone();
void SetMICMeasurementDone();
void Meas_Test();
MicrophoneState Mic_Upkeep();
#endif /* INC_MEASUREMENT_H_ */

