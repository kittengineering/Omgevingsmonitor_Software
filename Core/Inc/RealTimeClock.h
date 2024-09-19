#ifndef RTC_H
#define RTC_H

#include "stm32l0xx_hal.h"  // Inclusie van de benodigde HAL-bibliotheken
#include "stm32l0xx_hal_rcc.h"
#include "utils.h"

// Functies voor het instellen en uitlezen van de tijd
void RTC_SetTime(RTC_HandleTypeDef *hrtc, uint8_t hours, uint8_t minutes, uint8_t seconds);
void RTC_GetTime(RTC_HandleTypeDef *hrtc, uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

// Functies voor het instellen en uitlezen van de datum
void RTC_SetDate(RTC_HandleTypeDef *hrtc, uint8_t weekday, uint8_t day, uint8_t month, uint8_t year);
void RTC_GetDate(RTC_HandleTypeDef *hrtc, uint8_t *weekday, uint8_t *day, uint8_t *month, uint8_t *year);

// Functie om een alarm in te stellen
void RTC_SetAlarm(RTC_HandleTypeDef *hrtc, uint8_t hours, uint8_t minutes, uint8_t seconds);

// Functie om een wakeup timer in te stellen
void RTC_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t secondsOfSleep);
void Enter_Standby_Mode(void);
void Enter_Stop_Mode(void);

void InitClock(RTC_HandleTypeDef *hrtc);
void UpdateClock();

#endif  // RTC_H

