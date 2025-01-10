/*
 * statusCheck.c
 *
 *  Created on: Sep 17, 2024
 *      Author: Danny
 */
#include "statusCheck.h"
#include "RealTimeClock.h"
#include "rtc.h"

bool configSet = false;
bool usbPluggedIn = false;
bool userToggle = false;
static bool init = true;
static bool buttonHeld = false;
uint32_t ConfigStamp;
uint32_t PowerStamp = 0;

void InitDone(){
  init = false;
}

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

void SetStatusLED(uint16_t red, uint16_t green, uint16_t blue){
  if(usbPluggedIn || init || userToggle){
    TIM2 -> CCR1 = red;
    TIM2 -> CCR3 = green;
    TIM2 -> CCR4 = blue;
  }
}
// Sets dB LED to (RGB) color
void SetDBLED(bool red, bool green, bool blue){
  // RED LED
  if(usbPluggedIn || init || userToggle){
    HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, !red);
    HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, !green);
    HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, !blue);
  }
}
// Sets VOC LED to (RGB) color
void SetVocLED(uint16_t red, uint16_t green, uint16_t blue){
  if(usbPluggedIn || init || userToggle){
    TIM3 -> CCR1 = red;
    TIM3 -> CCR2 = green;
    TIM3 -> CCR3 = blue;
  }
}
void SetMeasurementIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR3 = LED_ON;
  }
}
void ResetMeasurementIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR3 = LED_OFF;
  }
}
void SetMICIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR1 = LED_ON;
  }
}
void ResetMICIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR1 = LED_OFF;
  }
}
void SetESPIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR4 = LED_ON;
  }
}
void ResetESPIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR4 = LED_OFF;
  }
}

// Sets all LEDs Off
void SetLEDsOff(void){
  SetStatusLED(LED_OFF,LED_OFF,LED_OFF);
  SetDBLED(false,false,false);
  SetVocLED(LED_OFF,LED_OFF,LED_OFF);
return;
}

Battery_Status powerCheck(){
  Battery_Status status;
  if(!Check_USB_PowerOn()){
    status = batteryChargeCheck();
  }
  else{
    status = USB_PLUGGED_IN;
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
    SetDBLED(true, true, true);
  }
  if(!BootButton_Pressed() && UserButton_Pressed() && !buttonHeld){
    SetLEDsOff();
    userToggle = !userToggle;
    buttonHeld = true;
  }
  if(!BootButton_Pressed() && !UserButton_Pressed()){
    buttonHeld = false;
  }
  if(Check_USB_PowerOn()){
    usbPluggedIn = true;
  }
  else{
    if(!userToggle && !init){
      SetLEDsOff();
    }
    usbPluggedIn = false;
  }
}

void GoToSleep(uint32_t sleepTime){
  HAL_Delay(1000);
  HAL_SuspendTick();
  //set wake up timer
  RTC_SetWakeUpTimer(&hrtc, sleepTime);
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
  HAL_ResumeTick();
}

void Status_Upkeep(){
  configCheck();
}

Battery_Status Battery_Upkeep(){
  Battery_Status status;
  status = powerCheck();
  powerDisplay(status);
  return status;

}

