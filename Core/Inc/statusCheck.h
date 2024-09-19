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

typedef enum {
  BATTERY_CRITICAL,
  USB_PLUGGED_IN,
  BATTERY_LOW,
  BATTERY_GOOD,
  BATTERY_FULL
}Battery_Status;

void status_Upkeep();
#endif /* INC_STATUSCHECK_H_ */
