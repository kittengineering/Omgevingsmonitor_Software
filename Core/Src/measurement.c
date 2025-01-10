/*
 * measurement.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */
/*
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "statusCheck.h"
#include "print_functions.h"
*/
#include "measurement.h"
#include "wsenHIDS.h"
#include "sgp40.h"
#include "microphone.h"
#include "sen5x.h"
#include "sound_measurement.h"
#include "statusCheck.h"

//static I2C_HandleTypeDef* sensorI2C = NULL;

EnabledMeasurements Sensor = {
    .HT_measurementEnabled = true,
    .VOC_measurementEnabled = true,
    .PM_measurementEnabled = true,
    .MIC_measurementEnabled = true
};

EnabledMeasurements Sensor;
DevicePresent SensorProbe;

void testInit(){
  SensorProbe.HT_Present = false;
  SensorProbe.VOC_Present = false;
  SensorProbe.PM_Present = false;
  SensorProbe.MIC_Present = false;
  SensorProbe.ESP_Present = false;
  SensorProbe.SGP_Enabled = false;
}

bool GetPMSensorPresence(){
  return SensorProbe.PM_Present;
}

bool IsHTSensorEnabled() {
  return Sensor.HT_measurementEnabled;
}

bool IsSGPSensorEnabled() {
  return SensorProbe.SGP_Enabled;
}

bool IsSGPPresent() {
  return SensorProbe.VOC_Present;
}

void SetVOCSensorDIS_ENA(bool setting) {
  SensorProbe.SGP_Enabled = setting;
//  SensorProbe.VOC_Present = setting;
  Sensor.VOC_measurementEnabled = setting;
  Debug("on-board SGP40 %s", setting?"enabled":"disabled");
}


bool IsVOCSensorEnabled() {
  return Sensor.VOC_measurementEnabled;
}

bool IsPMSensorEnabled() {
  return Sensor.PM_measurementEnabled;
}

bool IsMICSensorEnabled() {
  return Sensor.MIC_measurementEnabled;
}

void SetHTSensorStatus(bool setting) {
  Sensor.HT_measurementEnabled =  setting;
}

void SetVOCSensorStatus(bool setting) {
  Sensor.VOC_measurementEnabled = setting;
}

void SetPMSensorStatus(bool setting) {
  Sensor.PM_measurementEnabled = setting;
}

void SetMICSensorStatus(bool setting) {
  Sensor.MIC_measurementEnabled = setting;
}

void SetESPMeasurementDone(){
  SensorProbe.ESP_Present = true;
}

void Device_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, ADC_HandleTypeDef* ADC_HANDLER, UART_HandleTypeDef* espUart) {
  testInit();
  I2CSensors_Init(sensorI2C);
  if(!HIDS_DeviceConnected()) {
     Error("Humidity / Temperature sensor NOT connected!");
     SensorProbe.HT_Present = false;
     Sensor.HT_measurementEnabled = false;
     // HT Device NOT connected, turning LED on RED.
  }else {
    // HT Device is connected, turning led on GREEN.
    SensorProbe.HT_Present = true;
    Debug("Humidity / Temperature sensor initialised.");
  }
  if(!SGP_DeviceConnected()) {
    SensorProbe.VOC_Present = false;
     Error("SGP device not connected!");
     Sensor.VOC_measurementEnabled = false;
  }
  else{
    SensorProbe.SGP_Enabled = true;
    SensorProbe.VOC_Present = true;
    Debug("SGP sensor initialised.");
  }
  if(SensorProbe.VOC_Present && SensorProbe.HT_Present){
    SetDBLED(false, true, false);
  }
  else{
    SetDBLED(true, false, false);
    HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, 0);
    HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, 1);
    HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, 1);
  }
  if(Sensor.MIC_measurementEnabled) {
    Info("Device_Init calls enableMicrophone");
    if (!enableMicrophone(true)) {
      Error("Microphone device not connected! DMA Error.");
      SensorProbe.MIC_Present = false;
      Sensor.MIC_measurementEnabled = false;
    }
    else{
      SensorProbe.MIC_Present = true;
      Sensor.MIC_measurementEnabled = true;
      Debug("DMA and IRQ armed for Microphone sensor.");
    }
  }
  if (!probe_sen5x()) {
    Debug("PM sensor initialised.");
    SensorProbe.PM_Present = true; // not present
    Sensor.PM_measurementEnabled = true;
    if (((product_name[4] == '4') || (product_name[4] == '5'))) {
      Info("For power saving the SGP40 is disabled, VOCi measurement is done by sen54/sen55");
      Sensor.VOC_measurementEnabled = false;
      SensorProbe.SGP_Enabled = false;
      SGP_SoftReset();
    }
  }
  else {
    sen5x_Power_Off();      // switch off buck converter
    Debug("PM sensor not detected/connected.");
    SensorProbe.PM_Present = false;
    Sensor.PM_measurementEnabled = false;
  }
  Info("SensorProbe.HT_Present: %s", SensorProbe.HT_Present?"yes":"no");
  Info("SensorProbe.VOC_Present: %s", SensorProbe.VOC_Present?"yes":"no");
  Info("SensorProbe.PM_Present: %s", SensorProbe.PM_Present?"yes":"no");
  Info("SensorProbe.MIC_Present: %s", SensorProbe.MIC_Present?"yes":"no");
  ESP_Init(espUart);
  Debug("Sensors initialized, probing ESP.");
}

void Device_Test(){
  if(!SensorProbe.MIC_Present){
    if(MIC_TestMeasurementDone()){
      //when this condition is met, the device is definite operational
//      Debug("MIC_TestMeasurementDone() is true");
      SensorProbe.MIC_Present = true;
      Sensor.MIC_measurementEnabled = true;
      SetStatusLED(LED_OFF, Calculate_LED_ON(), LED_OFF);
    }
    else{
      if (micSettlingComplete()) {
        // his has to be met first
//        Debug("micSettlingComplete() is true");
        Sensor.MIC_measurementEnabled = true;
        SetStatusLED(Calculate_LED_ON(), LED_OFF, LED_OFF);
      }
    }
  }
  if(!SensorProbe.ESP_Present){
    ESP_WakeTest();  // calls in ESP.c  back to SetESPMeasurementDone()
  }
  if((SensorProbe.ESP_Present && SensorProbe.MIC_Present) || TimestampIsReached(deviceTimeOut)){
    Info("Test completed");
    Info("ESP function: %s", SensorProbe.ESP_Present?"passed": "failed");
    Info("MIC function: %s", SensorProbe.MIC_Present?"passed": "failed");
    SetTestDone();
  }
}

bool AllDevicesReady() {
  if (TimestampIsReached(deviceTimeOut)) {
    if (HIDSstate == HIDS_STATE_WAIT) {
      Sensor.HT_measurementEnabled = false;
    }
    if ((SGPstate == SGP_STATE_WAIT) || !SensorProbe.SGP_Enabled) {
      Sensor.VOC_measurementEnabled = false;
    }
    if (PMsamplesState == LIGHT_OUT) {
      Sensor.PM_measurementEnabled = false;
    }
    if (MICstate == MIC_STATE_WAIT){
      Sensor.MIC_measurementEnabled = false;
    }
    if (ESPstate == ESP_STATE_RESET) {
      return !(Sensor.HT_measurementEnabled || Sensor.VOC_measurementEnabled ||
          Sensor.PM_measurementEnabled || Sensor.MIC_measurementEnabled);
    }
  }
  return false;
}

void EnabledConnectedDevices() {
  if (SensorProbe.HT_Present) {
    Sensor.HT_measurementEnabled = true;
  }
  if ((SensorProbe.VOC_Present) && (SensorProbe.SGP_Enabled)) {
    Sensor.VOC_measurementEnabled = true;
  }
  if (SensorProbe.PM_Present) {
    Sensor.PM_measurementEnabled = true;
  }
  if (SensorProbe.MIC_Present) {
    Sensor.MIC_measurementEnabled = true;
  }
}

void DisableConnectedDevices() {
    Sensor.HT_measurementEnabled = false;
    Sensor.VOC_measurementEnabled = false;
    Sensor.PM_measurementEnabled = false;
    Sensor.MIC_measurementEnabled = false;
}
