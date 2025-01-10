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

float      ReadBatteryVoltage(void);   // Returns battery voltage in mV
float      ReadSolarVoltage(void);     // Returns solarpanel voltage in mV
bool          Check_USB_PowerOn(void);    // True if 5V on USB Connector
ChargeStatus  Read_Charge_Status(void);   // Returns Chargestatus



/* LED Indicator operations
 * Status LED
 * dB     LED
 * VOC    LED
 */

                                       // Global switches all LED's off

/* Button operations
 * User Button A  ( Boot0 PIN )
 * User Button B  ( User button PD2 )
 */
bool     BootButton_Pressed(void);   // True if Userbutton A ( Boot ) is pressed
bool     UserButton_Pressed(void);   // True if Userbutton B is pressed


#endif /* INC_POWERUTILS_H_ */
