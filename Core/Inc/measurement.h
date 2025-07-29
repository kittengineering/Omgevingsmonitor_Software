/*
 * measurement.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 *              redesigned Bert Havinga dec 2024
 */

#ifndef INC_MEASUREMENT_H_
#define INC_MEASUREMENT_H_
/*
#include "stm32l0xx_hal.h"
#include "ESP.h"
#include "utils.h"
*/
#include <stdbool.h>
#include "I2CSensors.h"

typedef enum{
  MEASURE_STATE_INIT,
  MEASURE_STATE_START,
  MEASURE_STATE_IDLE,
  MEASURE_STATE_BUSY,
} measureStates;


typedef struct {
  bool measurementDone;
  bool resume;
  float measurementValue;
}SensorType1;

typedef struct {
  bool measurementDone;
  bool resume;
  float measurementValue1;
  float measurementValue2;
}SensorType2;

typedef struct {
  bool measurementDone;
  bool resume;
  bool active;
  uint16_t measurementValue1;
  uint16_t measurementValue2;
  uint16_t measurementValue3;
  uint16_t measurementValue4;
}SensorType3;

typedef struct {
  SensorType3 Sens;
  SensorType2 HT;
  SensorType1 VOC;
  SensorType1 MIC;
  measureStates state;
  bool measurementsDone;
} Measurements;

bool AllDevicesReady();
void Device_Test();
void SetESPMeasurementDone();
bool IsSGPPresent();
void SetVOCSensorDIS_ENA(bool setting);
bool IsPMSensorEnabled();
bool GetPMSensorPresence();
void SetPMSensorStatus(bool setting);
void SetVOCSensorStatus(bool setting);
void DisableConnectedDevices();
void EnabledConnectedDevices();
void Device_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, ADC_HandleTypeDef* ADC_HANDLER);
void measurementReset();
bool measurementUpkeep();

#endif /* INC_MEASUREMENT_H_ */

