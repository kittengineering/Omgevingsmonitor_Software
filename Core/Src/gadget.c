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


static EnabledMeasurements SensorSetPower = {
    .HT_measurementEnabled = true,
    .VOC_measurementEnabled = true,
    .NO_measurementEnabled = false,
    .MIC_measurementEnabled = false
};
static EnabledMeasurements SensorSetBatt = {
    .HT_measurementEnabled = true,
    .VOC_measurementEnabled = true,
    .NO_measurementEnabled = false,
    .MIC_measurementEnabled = false
};

void Gadget_Init(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // TODO: Add gadget re-init. So it works after sleep mode again.
  // Check battery power
  // Init sensor + peripherals
  Meas_SetEnabledSensors(SensorSetPower);
  Meas_Init(sensorI2C, micI2s);
//  Gadget_SetSleepDuration();
  Info("Gadget initialised.");
}

void Gadget_DeInit(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {
  // Turn radio off
  // Turn off communication
  Meas_DeInit(sensorI2C, micI2s);
}

void Gadget_ReInit(I2C_HandleTypeDef* sensorI2C, I2S_HandleTypeDef* micI2s) {

}

void UpkeepGadget() {
  // State machine implementation?
  /*
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
  Meas_Upkeep();

  // Check if measurements aren't still running.

//  if(!EnoughPower){
//    if(Meas_GetState() == MEAS_STATE_INIT) {
//        Debug("Going into sleep mode.");
//      }
//  }
  if(Meas_GetState() == MEAS_STATE_PROCESS_RESULTS) {
    // Processing results
    // Turning Radio on
    // WIFI available?
      // Yes -> Post sensor data to server.
      // NO -> Check grid power available
        // YES -> Use leds for status
        // NO -> De-init sensors and Radio off.
        // Go to sleep
  }




//    // Can finish measurements?
//    // Check for interval time remaining?
//    // Update measurement state machine
//  }
//  else {
//    // Before going to sleep check if humidity sensor needs to heat up.
//    // GO sleep
//    // TODO: implement timer for going to sleep for a certain time.
//    // Make sure you think about what if you don't have internet. Then you can't sync the clock.
//    // Use latest synced time as reference then.
  // If no internet is available -> Don't do anything.
//  }
//  ESP_Send();
  // If you don't have wifi don't do anything with the data.
  // Use sleeping as interval between measuring.
  // Before going to sleep make sure you de-init the sensors.

//  if(Meas_GetState() == MEAS_STATE_WAIT_FOR_COMPLETION) {
//    // Can finish measurement?
//  }
//  if(GridPower) {
//    Meas_SetEnabledSensors(SensorSetPower);
//  }
//  if(Battery) {
//    Meas_SetEnabledSensors(SensorSetBatt);
//  }

}

