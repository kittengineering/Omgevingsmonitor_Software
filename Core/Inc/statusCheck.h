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


#define LED_OFF 4000
#define LED_ON 3000
typedef enum {
  BATTERY_CRITICAL,
  USB_PLUGGED_IN,
  BATTERY_LOW,
  BATTERY_GOOD,
  BATTERY_FULL
}Battery_Status;


void Status_Upkeep();
Battery_Status Battery_Upkeep();
void SetStatusLED(uint16_t red, uint16_t green, uint16_t blue);   // Sets Status LED to (RGB) color
void SetDBLED(bool red, bool green, bool blue);       // Sets dB LED to (RGB) color
void SetVocLED(uint16_t red, uint16_t green, uint16_t blue);      // Sets VOC LED to (RGB) color
void SetLEDsOff(void);
void InitDone();
void SetMeasurementIndicator();
void ResetMeasurementIndicator();
void SetMICIndicator();
void ResetMICIndicator();
void SetESPIndicator();
void ResetESPIndicator();
void GoToSleep(uint32_t sleepTime);
#endif /* INC_STATUSCHECK_H_ */
