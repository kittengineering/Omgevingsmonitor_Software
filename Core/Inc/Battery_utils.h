/*
 * Battery_utils.h
 *
 *  Created on: Sep 5, 2024
 *      Author: Danny
 */

#ifndef INC_BATTERY_UTILS_H_
#define INC_BATTERY_UTILS_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32l0xx_hal.h"
#include "gpio.h"
#include "adc.h"
#include "ESP.h"

typedef enum{
  BATTERY_STATUS_CRITICAL,
  BATTERY_STATUS_LOW,
  BATTERY_STATUS_OK,
  BATTERY_STATUS_GOOD
}BatteryStatus;


#endif /* INC_BATTERY_UTILS_H_ */
void batteryInit(ADC_HandleTypeDef* ADC_HANDLER);
void checkCharges();
