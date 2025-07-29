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
#include "main.h"
#include "measurement.h"
// #include "wsenHIDS.h"
//#include "sgp40.h"
#include "microphone.h"
#include "sen5x.h"
#include "sound_measurement.h"
#include "statusCheck.h"

#include "setLED.h"
#include "sgp40.h"
#include "wsenHIDS.h"

//static I2C_HandleTypeDef* sensorI2C = NULL;

Measurements measurementHandler = {
  .state = MEASURE_STATE_INIT
};


void Device_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s, ADC_HandleTypeDef* ADC_HANDLER) {
  I2CSensors_Init(sensorI2C);
  Info("Device_Init calls enableMicrophone");
}

void checkDone(){
  if(measurementHandler.MIC.measurementDone && measurementHandler.HT.measurementDone && measurementHandler.VOC.measurementDone){
    if((!measurementHandler.Sens.active) || measurementHandler.Sens.measurementDone){
      measurementHandler.measurementsDone = true;
    }
  }
}

void measurementReset(){
  measurementHandler.measurementsDone = false;
  measurementHandler.HT.measurementDone = false;
  measurementHandler.MIC.measurementDone = false;
  measurementHandler.VOC.measurementDone = false;
  measurementHandler.Sens.measurementDone = false;
}

bool measurementUpkeep(){
  bool isDone = false;
  switch(measurementHandler.state){

    case MEASURE_STATE_INIT:
      hydroTempInit(&measurementHandler.HT);
      initDB(&measurementHandler.MIC);
      initVOC(&measurementHandler.VOC);
      initSens(&measurementHandler.Sens);
      initVariableLink(&measurementHandler.HT, &measurementHandler.VOC, &measurementHandler.MIC, &measurementHandler.Sens);
      probe_sen5x();
      measurementHandler.state = MEASURE_STATE_START; 
    break;

    case MEASURE_STATE_START:
      measurementHandler.HT.resume = true;
      measurementHandler.MIC.resume = true;
      measurementHandler.VOC.resume = true;
      measurementHandler.Sens.resume = true;
      measurementHandler.state = MEASURE_STATE_BUSY;
    break;

    case MEASURE_STATE_BUSY:
      HIDS_Upkeep();
      petDog();
      Mic_Upkeep();
      petDog();
      SGP_Upkeep();
      petDog();

      if(measurementHandler.Sens.active)
        sen5x_statemachine();

      checkDone();
      if(measurementHandler.measurementsDone){
        measurementHandler.state = MEASURE_STATE_IDLE;
        HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, true);
        HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, false);
      }
    break;

    case MEASURE_STATE_IDLE:
      isDone = true;
      if(!measurementHandler.measurementsDone)
        measurementHandler.state = MEASURE_STATE_START;
    break;
  }
  return isDone;
}




