/*
 * humidTemp.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "humidTemp.h"
#include "utils.h"
#include "wsenHIDS.h"

void HT_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
  HIDS_Init(readFunction, writeFunction);
}

void HT_StartMeasurement() {
  HIDS_StartMeasurement();
}

void HT_SetMeasurementDuration(uint32_t duration) {
  HIDS_SetMeasurementDuration(duration);
}

bool HT_GetMeasurementValues(float* humidity_perc, float* temperature) {
  return HIDS_GetMeasurementValues(humidity_perc, temperature);
}

bool HT_DeviceConnected() {
  return HIDS_DeviceConnected();
}


