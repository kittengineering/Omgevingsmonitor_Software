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


typedef struct {
    bool HT_measurementEnabled;
    bool VOC_measurementEnabled;
    bool PM_measurementEnabled;
    bool MIC_measurementEnabled;
} EnabledMeasurements;

typedef struct {
  bool HT_Present;
  bool VOC_Present;
  bool PM_Present;
  bool MIC_Present;
  bool ESP_Present;
  bool SGP_Enabled;
}DevicePresent;

extern EnabledMeasurements Sensor;
extern DevicePresent SensorProbe;

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
void Device_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, ADC_HandleTypeDef* ADC_HANDLER, UART_HandleTypeDef* espUart);

#endif /* INC_MEASUREMENT_H_ */

