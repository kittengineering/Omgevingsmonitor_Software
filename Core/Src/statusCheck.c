/*
 * statusCheck.c
 *
 *  Created on: Sep 17, 2024
 *      Author: Danny
 *
 *      tim clock = APB tim clock / prescaler
 *      frequency = tim clock / auto reload register
 *      duty cycle in % = (Capture Compare Register CCRx / auto reload register) * 100%
 *
 *
 */
#include "statusCheck.h"
#include "PowerUtils.h"
#include "RealTimeClock.h"
#include "rtc.h"
#include "sen5x.h"

#include "setLED.h"

bool ConfigSet = false;
bool usbPluggedIn = true; //false;
bool userToggle = false;
static bool init = true;
uint32_t ConfigStamp;
uint32_t UserbuttonStamp;
uint32_t PowerStamp = 0;

typedef struct {
  float batteryVoltage;
  float solarVoltage;
} powerVariables;

powerVariables Charges = {
  .batteryVoltage = 0,
  .solarVoltage = 0,
};

void InitDone(){
  init = false;
}

/*
  100%----4.20V
  90%-----4.06V
  80%-----3.98V
  70%-----3.92V
  60%-----3.87V
  50%-----3.82V
  40%-----3.79V
  30%-----3.77V
  20%-----3.74V
  10%-----3.68V
  5%------3.45V
  0%------3.00V
 */

Battery_Status batteryChargeCheck(float batteryCharge){
  if(Check_USB_PowerOn()){
    return USB_PLUGGED_IN;
  }
  if(batteryCharge >= 3.7){
    return BATTERY_GOOD;
  }
  if(batteryCharge < 3.7 && batteryCharge >= 3.5){
    return BATTERY_LOW;
  }
  return BATTERY_CRITICAL;
}
/*
//==========================
// code om de pwm helderheid van de leds te testen
for (int b=40 ; b>0 ; b--) {
  SetStatusLED(4000, 4000, b*100);  // 0 is on | 4000 is off
  HAL_Delay(1000);
}
//====================
*/

bool UsbPowered()
{
    return HAL_GPIO_ReadPin(VusbDetect_GPIO_Port, VusbDetect_Pin);
}

uint16_t Calculate_LED_ON() {
  static uint16_t solmV;
  solmV = ReadSolarVoltage();
  if (solmV < 2900) {
    solmV = 2900;
  }
  if (solmV > 4700) {
    solmV = 4700;
  }
  return (solmV+(3566-solmV)*1.5);
}


void LEDSOff(){
  		TIM2->CCR1 = LED_OFF;
			TIM2->CCR3 = LED_OFF;
			TIM2->CCR4 = LED_OFF;
			TIM3->CCR1 = LED_OFF;
			TIM3->CCR2 = LED_OFF;
			TIM3->CCR3 = LED_OFF;
      HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, true);
      HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, true);
      HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, true);
}

void GoToSleep(uint16_t sleepTime){
  Debug("Entering sleep mode for %d seconds", sleepTime);
  HAL_Delay(100);
  HAL_SuspendTick();
  //set wake up timer
  RTC_SetWakeUpTimer(sleepTime);
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
  SystemClock_Config();
  HAL_ResumeTick();
}

void processButtonPressed(){
  static uint32_t pressTime;
  static uint32_t holdTime;
  if(UserButton_Pressed() && BootButton_Pressed()){
    holdTime = HAL_GetTick();
    if((holdTime - pressTime) > 2000){
      while(1){
        Process_PC_Config(GetUsbRxPointer());
        SetStatusLED_T(LED_FULL_ON, LED_FULL_ON, LED_FULL_ON);
        petDog();
      }
    }
  }
  else{
    pressTime = HAL_GetTick();
    holdTime = HAL_GetTick();
  }
}

/*
void Status_Upkeep(){
  configCheck();
}
*/
Battery_Status Battery_Upkeep(){
  Battery_Status status;
  Charges.batteryVoltage = ReadBatteryVoltage();
  Charges.solarVoltage = ReadSolarVoltage();
  status = batteryChargeCheck(Charges.batteryVoltage);
  return status;
}
