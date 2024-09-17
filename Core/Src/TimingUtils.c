/*
 * TimingUtils.c
 *
 *  Created on: Sep 3, 2024
 *      Author: andries
 */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"
#include "utils.h"
#include "stm32l0xx_hal.h"





/*  Time to Epoch conversion  */

uint32_t GetEpoch(RTC_HandleTypeDef *hrtc){

/* date and Time structures */
  RTC_DateTypeDef sdateget;
  uint8_t years   = 0 ;
  uint8_t month  = 0 ;
  uint8_t day   = 0 ;

  RTC_TimeTypeDef stimeget;
  uint8_t hour   = 0 ;
  uint8_t min    = 0 ;
  uint8_t sec    = 5 ;

  /* Get the RTC current Time */
if (HAL_RTC_GetTime(&hrtc, &stimeget, RTC_FORMAT_BIN) == HAL_OK){
     hour   = stimeget.Hours   ;
     min    = stimeget.Minutes ;
     sec    = stimeget.Seconds ;
 //    hour   = 0   ;
//     min    = 0 ;
 //    sec    = 7 ;
  }
  else {
    Error_Handler();
  }

  /* Get the RTC current Date */
if ( HAL_RTC_GetDate(&hrtc, &sdateget, RTC_FORMAT_BIN) == HAL_OK){
      years   = sdateget.Year  ;
      month  = sdateget.Month ;
      day   = sdateget.Date  ;
      years   = 24  ;
      month  = 0 ;
      day   = 0  ;
  }
else {
    Error_Handler();
  }

/* Convert ISO time format into Epoch ( Unix  time )  */

  int year = years + 2000; // We use the RTC as if it is started @ 2000

  const short days_since_beginning_of_year[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
  int leap_years = ((year-1)-1968)/4
                  - ((year-1)-1900)/100
                  + ((year-1)-1600)/400;
  long days_since_1970 = (year-1970)*365 + leap_years
                      + days_since_beginning_of_year[month-1] + day-1;
  if ( (month>2) && (year%4==0 && (year%100!=0 || year%400==0)) )
    days_since_1970 += 1; /* +leap day, if year is a leap year */
  //return sec + 60 * ( min + 60 * (hour + 24*days_since_1970) );
  return sec;
}




