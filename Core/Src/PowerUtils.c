/*
 * PowerUtils.c
 *
 *  Created on: Sep 4, 2024
 *      Author: andri
 */


#include "PowerUtils.h"



/* function to read the actual battery voltage */

  ADC_ChannelConfTypeDef sConfig = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  uint32_t Vref = 2915;   // reference voltage in mV

float ReadBatteryVoltage(void){
  /* Channel 14 is de battery voltage */
  static uint32_t value = 0;
  static float trueValue = 0;
   sConfig.Channel = ADC_CHANNEL_14;
   sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
   if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
   {
     Error_Handler();
   }
   HAL_ADC_Start(&hadc);
   HAL_ADC_PollForConversion(&hadc, 1);
   value = (HAL_ADC_GetValue(&hadc)*Vref*2)/4095;
   trueValue = (float)value/1000.0;
   /* Disable Channel 14 */
   sConfig.Channel = ADC_CHANNEL_14;
   sConfig.Rank = ADC_RANK_NONE;
   if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
   {
     Error_Handler();
   }
   return trueValue;
 }

/* function to read the actual battery voltage */

float ReadSolarVoltage(void){
  /* Channel 15 is the Solar voltage */
  static uint32_t value = 0;
  static float trueValue = 0;
   sConfig.Channel = ADC_CHANNEL_15;
   sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
   if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
   {
     Error_Handler();
   }
   HAL_ADC_Start(&hadc);
   HAL_ADC_PollForConversion(&hadc, 1);
   value = (HAL_ADC_GetValue(&hadc)*Vref*3)/4095;
   trueValue = (float)value / 1000.0;
   /* Disable Channel 14 */
   sConfig.Channel = ADC_CHANNEL_15;
   sConfig.Rank = ADC_RANK_NONE;
   if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
   {
     Error_Handler();
   }
   return trueValue;
 }

// True if 5V on USB Connector
bool   Check_USB_PowerOn(void){
return   (HAL_GPIO_ReadPin(VusbDetect_GPIO_Port, VusbDetect_Pin));
}

// Retruns Battery status in TypeDef
// TypeDef ChargeStatus:
//  CHARGING_OFF  = 0
//  CHARGING_ON   = 1
//  CHARGING_FULL = 2
//  Function returns Chargestatus

ChargeStatus Read_Charge_Status(void){


bool PulledUpStatus   = true  ;
bool PulledDownStatus = false ;

 //Read with Pull Up
 //Charge_Pin_Up();
 GPIO_InitStruct.Pin = Charger_status_Pin;
 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
 GPIO_InitStruct.Pull = GPIO_PULLUP;
 HAL_GPIO_Init(Charger_status_GPIO_Port, &GPIO_InitStruct);

 PulledUpStatus = (HAL_GPIO_ReadPin(Charger_status_GPIO_Port, Charger_status_Pin));

 //Read with Pull Down
 // Charge_Pin_Down();
 GPIO_InitStruct.Pin = Charger_status_Pin;
 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
 GPIO_InitStruct.Pull = GPIO_PULLDOWN;
 HAL_GPIO_Init(Charger_status_GPIO_Port, &GPIO_InitStruct);

 PulledDownStatus = (HAL_GPIO_ReadPin(Charger_status_GPIO_Port, Charger_status_Pin));

  if (PulledUpStatus==false) {
    return CHARGING_ON;
  }
  if (PulledDownStatus==true){
    return CHARGING_FULL;
  }
  return CHARGING_OFF;
}





/* Button operations
 * User Button A  ( Boot0 PIN )
 * User Button B  ( User button PD2 )
 */

// True if Userbutton A ( Boot ) is pressed
// It is NOT Possible to read the Boot0 pin after powerup / Reset!!
// So a copy is hard wired to PA15

bool     BootButton_Pressed(void){
  return   (HAL_GPIO_ReadPin(BOOT0_GPIO_Port, BOOT0_Pin));
}

// True if Userbutton B is pressed
bool     UserButton_Pressed(void){
  return   (!HAL_GPIO_ReadPin(User_Button_GPIO_Port, User_Button_Pin));
}

