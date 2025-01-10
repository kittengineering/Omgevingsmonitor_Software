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

bool configSet = false;
bool usbPluggedIn = false;
bool userToggle = false;
static bool init = true;
static bool buttonHeld = false;
uint32_t ConfigStamp;
uint32_t UserbuttonStamp;
uint32_t PowerStamp = 0;
static float batteryCharge = 0.0;

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

Battery_Status batteryChargeCheck(){
  Battery_Status status;
  batteryCharge = ReadBatteryVoltage();
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
/*
//==========================
// code om de pwm helderheid van de leds te testen
for (int b=40 ; b>0 ; b--) {
  SetStatusLED(4000, 4000, b*100);  // 0 is on | 4000 is off
  HAL_Delay(1000);
}
//====================
*/

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
    TIM2 -> CCR3 = Calculate_LED_ON();
  }
}
void ResetMeasurementIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR3 = LED_OFF;
  }
}
void SetMICIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR1 = Calculate_LED_ON();
  }
  else {
    if (batteryCharge > 3.7) {
      TIM2 -> CCR3 = Calculate_LED_ON();
    }
    else {
      TIM2 -> CCR1 = Calculate_LED_ON();
    }
  }
}
void ResetMICIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR1 = LED_OFF;
  }
  else {
    if (batteryCharge > 3.74) {
      TIM2 -> CCR3 = LED_OFF;
    }
    else {
      TIM2 -> CCR1 = LED_OFF;
    }
  }
}
void SetESPIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR4 = Calculate_LED_ON();
  }
}
void ResetESPIndicator(){
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR4 = LED_OFF;
  }
}

void SetPMIndicator() {
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR4 = Calculate_LED_ON();
    TIM2 -> CCR1 = Calculate_LED_ON();
    TIM2 -> CCR3 = Calculate_LED_ON();
  }
}

void ResetPMIndicator() {
  if(usbPluggedIn||userToggle){
    TIM2 -> CCR4 = LED_OFF;
    TIM2 -> CCR1 = LED_OFF;
    TIM2 -> CCR3 = LED_OFF;
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
    Debug("userToggle flipped");
    userToggle = !userToggle;
    if (userToggle) {
      EnabledConnectedDevices();
    }
    buttonHeld = true;
    UserbuttonStamp = HAL_GetTick() + 2000;
  }
  if (!BootButton_Pressed() && buttonHeld&& TimestampIsReached(UserbuttonStamp)) {
    if (GetPMSensorPresence() && ((product_name[4] == '4') || (product_name[4] == '5'))) {
      uint16_t color;
      VOCNOx = !VOCNOx;
      if (VOCNOx)  color = Calculate_LED_ON();
        else color = 4000;
      Info("VOC and NOx only measurement %s", VOCNOx?"enabled":"disabled");
      for (uint8_t i=0; i<2; i++) {
        TIM3 -> CCR1 = Calculate_LED_ON();
        TIM3 -> CCR2 = color;
        TIM3 -> CCR3 = color;
        HAL_Delay(400);
        TIM3 -> CCR1 = 4000;
        TIM3 -> CCR2 = 4000;
        TIM3 -> CCR3 = 4000;
        HAL_Delay(400);
      }
      Debug("userToggle flipped back to prior status");
      userToggle = !userToggle;
      Info("userToggle status is %s", userToggle?"enabled":"disabled");
      if (usbPluggedIn) {
        set_light_on_state();  // in case of battery operation the mode is picked up by the state machine
      }
    }
    else {
      Info("sen54 or sen55 not present or disabled in system");
    }
    while (UserButton_Pressed()){
    }
    buttonHeld = false;
  }
  if(!BootButton_Pressed() && !UserButton_Pressed()){
    buttonHeld = false;
  }
  if(Check_USB_PowerOn()){
    usbPluggedIn = true;
    EnabledConnectedDevices();
  }
  else{
    if(!userToggle && !init){
      SetLEDsOff();
    }
    usbPluggedIn = false;
  }
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

/*
void Status_Upkeep(){
  configCheck();
}
*/
Battery_Status Battery_Upkeep(){
  Battery_Status status;
  status = powerCheck();
  powerDisplay(status);  // output LEDs are okay
  return status;
}

void setuserToggle(void) {
  if (powerCheck() != USB_PLUGGED_IN) { //operate only in battery operation mode
    userToggle = true;
  }
}
