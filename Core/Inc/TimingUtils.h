/*
 * TimingUtils.h
 *
 *  Created on: Sep 3, 2024
 *      Author: andries
 */
/*
RTC_TimeTypeDef:
uint8_t Hours;  0-12  or 0-23
uint8_t Minutes; 0 -59
uint8_t Seconds; 0 -59
uint8_t TimeFormat;
uint32_t SubSeconds;
uint32_t SecondFraction;
uint32_t DayLightSaving;
uint32_t StoreOperation;

RTC_DateTypeDef:
uint8_t WeekDay;
uint8_t Month;
uint8_t Date;  1 -31
uint8_t Year;  0 - 99

*/

#ifndef INC_TIMINGUTILS_H_
#define INC_TIMINGUTILS_H_

#include "utils.h"
#include "stm32l0xx_hal.h"
#include "rtc.h"

uint32_t GetEpoch(RTC_HandleTypeDef *hrtc);

#endif /* INC_TIMINGUTILS_H_ */
