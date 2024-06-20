/*
 * gadget.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#include "gadget.h"

void Gadget_Init(I2C_HandleTypeDef* humidTempI2c, I2S_HandleTypeDef* micI2s, CRC_HandleTypeDef* sensorCrc){
	Meas_Init(humidTempI2c, micI2s, sensorCrc);
	Info("Gadget initialised.");
}
