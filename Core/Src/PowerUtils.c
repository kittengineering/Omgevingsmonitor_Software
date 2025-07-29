/*
 * PowerUtils.c
 *
 *  Created on: Sep 4, 2024
 *      Author: andri
 *
 */

#include "PowerUtils.h"

#define Vref   2915
/* function to read the actual battery voltage */

  ADC_ChannelConfTypeDef sConfig = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};

float ReadBatteryVoltage(void){
  uint32_t value = 0;
  float trueValue = 0;
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
    Error_Handler();
  }
  HAL_ADC_Start(&hadc);
  HAL_ADC_PollForConversion(&hadc, 10); //1
  value = (HAL_ADC_GetValue(&hadc)*Vref*2)/4095;
  trueValue = (float)value/1000.0;
  /* Disable Channel 14 */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_RANK_NONE;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
    Error_Handler();
  }
  return trueValue;
 }


float ReadSolarVoltage(void){
  /* Channel 15 is the Solar voltage */
  uint32_t solarvalue = 0;
  float trueValue = 0;
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
    Error_Handler();
  }
  HAL_ADC_Start(&hadc);
  HAL_ADC_PollForConversion(&hadc, 1);
  solarvalue = (HAL_ADC_GetValue(&hadc)*Vref*3)/4095;
  trueValue = (float)solarvalue / 1000.0;
  /* Disable Channel 15 */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_RANK_NONE;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
    Error_Handler();
  }
 return trueValue;
 }


bool Check_USB_PowerOn(void){
  return (HAL_GPIO_ReadPin(VusbDetect_GPIO_Port, VusbDetect_Pin));
}

bool BootButton_Pressed(void){
  return   (HAL_GPIO_ReadPin(BOOT0_GPIO_Port, BOOT0_Pin));
}

bool     UserButton_Pressed(void){
  return   (!HAL_GPIO_ReadPin(User_Button_GPIO_Port, User_Button_Pin));
}
