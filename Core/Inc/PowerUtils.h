/*
 * PowerUtils.h
 *
 *  Created on: Sep 4, 2024
 *  Author: andries
 */

#ifndef INC_POWERUTILS_H_
#define INC_POWERUTILS_H_

#include "adc.h"
#include "utils.h"
#include "gpio.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_gpio.h"

typedef enum {
  CHARGING_OFF,
  CHARGING_ON,
  CHARGING_FULL
} ChargeStatus;

uint32_t      ReadBatteryVoltage(void);   // Returns battery voltage in mV
uint32_t      ReadSolarVoltage(void);     // Returns solarpanel voltage in mV
bool          Check_USB_PowerOn(void);    // True if 5V on USB Connector
ChargeStatus  Read_Charge_Status(void);   // Returns Chargestatus



/* LED Indicator operations
 * Status LED
 * dB     LED
 * VOC    LED
 */

void SetStatusLED(uint8_t red, uint8_t green, uint8_t blue);   // Sets Status LED to (RGB) color
void SetDBLED(bool red, bool green, bool blue);       // Sets dB LED to (RGB) color
void SetVocLED(uint8_t red, uint8_t green, uint8_t blue);      // Sets VOC LED to (RGB) color
void SetLEDsOff(void);                                         // Global switches all LED's off

/* Button operations
 * User Button A  ( Boot0 PIN )
 * User Button B  ( User button PD2 )
 */
bool     BootButton_Pressed(void);   // True if Userbutton A ( Boot ) is pressed
bool     UserButton_Pressed(void);   // True if Userbutton B is pressed


#endif /* INC_POWERUTILS_H_ */
