/*
 * Battery_utils.c
 *
 *  Created on: Sep 5, 2024
 *      Author: Danny
 */
#include "Battery_utils.h"
#include <stdio.h>

static ADC_HandleTypeDef* ADC_Handler = NULL;
float Charge = 0;
float Solar = 0;
uint16_t Vref = 3;

void batteryInit(ADC_HandleTypeDef* ADC_HANDLER){
  ADC_Handler = ADC_HANDLER;
}

void checkCharges(){
  HAL_ADC_Start(ADC_Handler);
  HAL_ADC_PollForConversion(ADC_Handler, 1);
  Charge = ((float)HAL_ADC_GetValue(ADC_Handler)/4095.0)*Vref*2;
  HAL_ADC_Start(ADC_Handler);
  HAL_ADC_PollForConversion(ADC_Handler, 1);
  Solar = ((float)HAL_ADC_GetValue(ADC_Handler)/4095.0)*Vref*2;
  setCharges(Charge, Solar);
}

void checkChargeStatus(){
  //poll Chargeport
  //Chargedt = Charge2 - Charge1
  //
}
