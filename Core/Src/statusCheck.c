/*
 * statusCheck.c
 *
 *  Created on: Sep 17, 2024
 *      Author: Danny
 */
#include "statusCheck.h"
#include "RealTimeClock.h"
bool configSet = false;
bool energyGood = false;
uint32_t ConfigStamp;
uint32_t PowerStamp = 0;

Battery_Status batteryChargeCheck(){
  Battery_Status status;
  float batteryCharge = ReadBatteryVoltage();
  if(batteryCharge < 3.5){
    status = BATTERY_CRITICAL;
  }
  if(batteryCharge < 3.7 && batteryCharge >= 3.5){
    status = BATTERY_LOW;
  }
  if(batteryCharge < 4.0 && batteryCharge >= 3.7){
    status = BATTERY_GOOD;
  }
  if(batteryCharge >= 4.0){
    status = BATTERY_FULL;
  }
  return(status);
}

Battery_Status powerCheck(){
  PowerStamp = HAL_GetTick() + 10000;
  Battery_Status status;
  if(Check_USB_PowerOn()){
    status = USB_PLUGGED_IN;
  }
  else{
    status = batteryChargeCheck();
  }
  return status;
}

void powerDisplay(Battery_Status status){
  if(status == USB_PLUGGED_IN){
    Debug("LEDS are okay");
  }
  if(status == BATTERY_FULL){
    Debug("Battery fully charged");
  }
  if(status == BATTERY_GOOD){
    Debug("Battery charge is doing well");
  }
  if(status == BATTERY_LOW){
    Debug("Battery is getting low");
  }
  if(status == BATTERY_CRITICAL){
    Debug("Battery is critical, stop processes");
  }
}

void configCheck(){
  if(BootButton_Pressed() && UserButton_Pressed()){
    configSet = true;
  }
  else{
    configSet = false;
    ConfigStamp = HAL_GetTick() + 2000;
  }
  if(configSet && TimestampIsReached(ConfigStamp)){
    SetConfigMode(); //Make config mode wifi
    HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, 0);
    HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, 0);
    HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, 0);
  }
}

void GoToSleep(){
  HAL_Delay(1000);
  HAL_SuspendTick();
  //set wake up timer
  //RTC_SetWakeUpTimer(RTC_Handler, 300000);
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
  HAL_ResumeTick();
}

void status_Upkeep(){
  Battery_Status status;
  configCheck();
  if(TimestampIsReached(PowerStamp)){
    status = powerCheck();
    powerDisplay(status);
  }
}

