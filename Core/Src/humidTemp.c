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

static bool ReadI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);
static bool WriteI2C(uint8_t address, uint8_t* buffer, uint8_t nrBytes);


void HT_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
  HIDS_Init(readFunction, writeFunction);
}

void HT_StartMeasurement(void){
  HIDS_StartMeasurement();
}

bool HT_GetMeasurementValues(float* humidity_perc, float* temperature) {
  return HIDS_GetMeasurementValues(humidity_perc, temperature);
}

