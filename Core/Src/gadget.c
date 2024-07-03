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
  Meas_SetInterval(5000);
  Info("Gadget initialised.");
}

void UpkeepGadget() {
  // State machine implementation?
  /*
   * Enough power?
   * No -> measurements running? yes -> can finish measurements? No -> cancel measurements + data transfer, yes -> update measurement statemachine
   * Update measurement state machine
   *
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
  // Check if measurements are still running.
  if(Meas_GetState() == MEAS_STATE_START_MEASUREMENT) {
    // Can finish measurements?
    // Check for interval time remaining?
    // Update measurement state machine
  }
  else {
    // GO sleep
    // TODO: implement timer for going to sleep for a certain time.
    // Make sure you think about what if you don't have internet. Then you can't sync the clock.
  }
//  ESP_Send();
}

