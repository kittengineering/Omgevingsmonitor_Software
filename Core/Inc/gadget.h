/*
 * gadget.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_GADGET_H_
#define INC_GADGET_H_

#include "gadget.h"
#include "measurement.h"
#include "stm32l0xx_hal.h"
#include "utils.h"

void Gadget_Init(I2C_HandleTypeDef* humidTempI2c, I2S_HandleTypeDef* micI2s);
void UpkeepGadget(void);

#endif /* INC_GADGET_H_ */
