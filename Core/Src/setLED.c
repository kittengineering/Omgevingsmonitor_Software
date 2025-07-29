#include "setLED.h"
#include "main.h"

static LED StatusLED;
static LED DBLED;
static LED VOCLED;


///Use LED_FULL_ON, LED_HALF_ON or LED_OFF
void SetStatusLED_T(uint16_t red, uint16_t green, uint16_t blue){
    TIM2 -> CCR1 = red;
    TIM2 -> CCR3 = green;
    TIM2 -> CCR4 = blue;
}

// Sets dB LED to (RGB) color
void SetDBLED_T(bool red, bool green, bool blue){
    HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, !red);
    HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, !green);
    HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, !blue);;
}

// Sets VOC LED to (RGB) color
///Use LED_FULL_ON, LED_HALF_ON or LED_OFF
void SetVocLED_T(uint16_t red, uint16_t green, uint16_t blue){
    TIM3 -> CCR1 = LED_MAX_VALUE - red;
    TIM3 -> CCR2 = LED_MAX_VALUE - green;
    TIM3 -> CCR3 = LED_MAX_VALUE - blue;
}

void UpdateLEDs()
{
    // Set status LED
    TIM2 -> CCR1 = (uint16_t)(65535 - (256 * StatusLED.red));
    TIM2 -> CCR3 = (uint16_t)(65535 - (256 * StatusLED.green));
    TIM2 -> CCR4 = (uint16_t)(65535 - (256 * StatusLED.blue));

    // Set dB LED
    HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, !DBLED.red);
    HAL_GPIO_WritePin(MCU_LED_C_G_GPIO_Port, MCU_LED_C_G_Pin, !DBLED.green);
    HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, !DBLED.blue);
    
    // Set VOC LED
    TIM3 -> CCR1 = (uint16_t)(65535 - (256 * VOCLED.red));
    TIM3 -> CCR2 = (uint16_t)(65535 - (256 * VOCLED.green));
    TIM3 -> CCR3 = (uint16_t)(65535 - (256 * VOCLED.blue));
}

void ErrorBlinkWiFi(){
    SetStatusLED_T(LED_FULL_ON, LED_OFF, LED_OFF);
    HAL_Delay(500);
    SetStatusLED_T(LED_OFF, LED_OFF, LED_OFF);
    HAL_Delay(500);
    SetStatusLED_T(LED_FULL_ON, LED_OFF, LED_OFF);
    HAL_Delay(500);
    SetStatusLED_T(LED_OFF, LED_OFF, LED_OFF);
    HAL_Delay(500);
    SetStatusLED_T(LED_FULL_ON, LED_OFF, LED_OFF);
    HAL_Delay(500);
    SetStatusLED_T(LED_OFF, LED_OFF, LED_OFF);
}