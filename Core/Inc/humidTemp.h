/*
 * humidTemp.h
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_HUMIDTEMP_H_
#define INC_HUMIDTEMP_H_

void HT_Init(I2C_HandleTypeDef* humTempI2c, CRC_HandleTypeDef* sensorCrc);
void HT_StartMeasurement(void);
bool HT_GetMeasurementValues(float* humidity_perc, float* temperature);

#endif /* INC_HUMIDTEMP_H_ */
