/*
 * gadget.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include "gadget.h"
//static uint32_t LastWakeupTime = 0;

//static bool ShouldSleep(void){
//  uint32_t awakeTime = TimerGetCurrentTime() - LastWakeupTime;
//  // Wait at least MINIMUM_AWAKE_TIME_SECONDS seconds before going to sleep
//  if(awakeTime < MINIMUM_AWAKE_TIME_SECONDS * 1000) return false;
//  return true;
//}

void Gadget_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // Check battery power
  // Init sensor + peripherals
  Meas_Init(sensorI2C, micI2s);
  Info("Gadget initialised.");
}

void UpkeepGadget() {
  // State machine implementation?
  /*
   * Update measurement state machine
   *
   * 	Process results <-> update measurements
   *
   * Update data transfer state machine
   * 	Idle
   * 	Should send data?
   * 	Yes: Enable ESP
   * 	Connect wifi
   * 	Connected?
   * 	Yes: create data format
   * 	Transmit data
   * 	Close connection
   * 	Disable ESP
   */
//  if(ShouldSleep()){
//        Sleep();
//        return;
//  }
  Meas_Upkeep();
}

