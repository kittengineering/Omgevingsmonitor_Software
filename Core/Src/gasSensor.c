/*
 * gasSensor.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gasSensor.h"
#include "stm32l0xx_it.h"
#include "sgp41.h"
#include "utils.h"

void Gas_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
  SGP_Init(readFunction, writeFunction);
}

void Gas_StartMeasurement(void){
  SGP_StartMeasurement();
}

bool Gas_GetMeasurementValues(float* vocIndex, float* noXIndex) {
  return SGP_GetMeasurementValues(vocIndex, noXIndex);
}

bool Gas_DeviceConnected(void) {
  return SGP_DeviceConnected();
}

