#include "rtc.h"
#include "RealTimeClock.h"

typedef struct {
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
}Clock;

static Clock RealTime = {.Hours = 0, .Minutes = 0, .Seconds = 0};
static Clock NextAction = {.Hours = 0, .Minutes = 0, .Seconds = 0};
RTC_HandleTypeDef* RealTime_Handle = NULL;

// Functie om de tijd in te stellen
void RTC_SetTime(RTC_HandleTypeDef *hrtc, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_TimeTypeDef sTime = {0};

    sTime.Hours = hours;
    sTime.Minutes = minutes;
    sTime.Seconds = seconds;
    sTime.TimeFormat = RTC_HOURFORMAT_24;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    

    if (HAL_RTC_SetTime(hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
    }
}

void InitClock(RTC_HandleTypeDef *hrtc){
  RealTime_Handle = hrtc;
  RTC_SetTime(RealTime_Handle, RealTime.Hours, RealTime.Minutes, RealTime.Seconds);
}
// Functie om de tijd uit te lezen
void RTC_GetTime(RTC_HandleTypeDef *hrtc, uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
    RTC_TimeTypeDef gTime = {0};

    if (HAL_RTC_GetTime(hrtc, &gTime, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
    }

    *hours = gTime.Hours;
    *minutes = gTime.Minutes;
    *seconds = gTime.Seconds;
}
// Functie om de datum in te stellen
void RTC_SetDate(RTC_HandleTypeDef *hrtc, uint8_t weekday, uint8_t day, uint8_t month, uint8_t year) {
    RTC_DateTypeDef sDate = {0};

    sDate.WeekDay = weekday;
    sDate.Date = day;
    sDate.Month = month;
    sDate.Year = year;  // Jaartal zonder eeuw (bv. 2024 -> 24)

    if (HAL_RTC_SetDate(hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
    }
}

// Functie om de datum uit te lezen
void RTC_GetDate(RTC_HandleTypeDef *hrtc, uint8_t *weekday, uint8_t *day, uint8_t *month, uint8_t *year) {
    RTC_DateTypeDef gDate = {0};

    if (HAL_RTC_GetDate(hrtc, &gDate, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
    }

    *weekday = gDate.WeekDay;
    *day = gDate.Date;
    *month = gDate.Month;
    *year = gDate.Year;
}

// Functie om een alarm in te stellen
void RTC_SetAlarm(RTC_HandleTypeDef *hrtc, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_AlarmTypeDef sAlarm = {0};

    sAlarm.AlarmTime.Hours = hours;
    sAlarm.AlarmTime.Minutes = minutes;
    sAlarm.AlarmTime.Seconds = seconds;
    sAlarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    sAlarm.Alarm = RTC_ALARM_A;

    if (HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
    }
}

// // Callback voor als het alarm afgaat
// void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
//     // Doe iets wanneer het alarm afgaat
//     HAL_GPIO_TogglePin(LED_C_Red_GPIO_Port, LED_C_Red_Pin);
// }

void RTC_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t secondsOfSleep)
{
    //Switch of the timer to reset it
    HAL_RTCEx_DeactivateWakeUpTimer(hrtc);

    //Set the prescale so that the clock will be 1Hz
    HAL_RTCEx_SetWakeUpTimer_IT(hrtc, secondsOfSleep, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);

    HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
}

void Enter_Standby_Mode(void)
{
    // Schakel de clock voor de Power Controller in
    __HAL_RCC_PWR_CLK_ENABLE();

    // Schakel Standby Mode in
    HAL_PWR_EnterSTANDBYMode();
}

void Enter_Stop_Mode(void)
{
    // Schakel de clock voor de Power Controller in
    __HAL_RCC_PWR_CLK_ENABLE();

    // Instellen op Stop mode met low-power regulator
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}
