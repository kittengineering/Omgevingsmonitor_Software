/*
 * statusCheck.h
 *
 *  Created on: Sep 17, 2024
 *      Author: Danny
 */

#ifndef INC_STATUSCHECK_H_
#define INC_STATUSCHECK_H_

#include "PowerUtils.h"
#include "ESP.h"
#include "gpio.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_gpio.h"


typedef enum {
  BATTERY_CRITICAL,
  BATTERY_LOW,
  BATTERY_GOOD,
  USB_PLUGGED_IN
  }Battery_Status;

Battery_Status Battery_Upkeep();
uint16_t Calculate_LED_ON();
void InitDone();
void GoToSleep(uint16_t sleepTime);
void processButtonPressed();
bool UsbPowered();
void LEDSOff();
#endif /* INC_STATUSCHECK_H_ */
