#include "rtc.h"
#include "RealTimeClock.h"
#include "sen5x.h"
#include "main.h"
#include "microphone.h"
#include "ESP.h"
#include "sgp40.h"
#include "wsenHIDS.h"
#include "statusCheck.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
  uint16_t Day;
  uint8_t Hour;
  uint8_t Minutes;
  uint8_t Seconds;
}Clock;


bool firstTimeUpdate = true;
static Clock myUpTime = {.Day = 0, .Hour = 0, .Minutes = 0, .Seconds = 0};
static const char *dayNames[7] = {  "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}; // 1 to 7
static const char *monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; // 1 to 12
static RTC_HandleTypeDef * RealTime_Handle;
static uint32_t posixBootTime = 0;

//char systemUptime[16] = {0};
char strbuf[24] = {0}; //22-jan-24 23h:12m:23s

uint32_t makeTime(RTC_DateTypeDef* currentDate, RTC_TimeTypeDef* currentTime);
void breakPosixTime(uint32_t timeInput, RTC_DateTypeDef* currentDate, RTC_TimeTypeDef* currentTime);

void showTime() {
  if (posixBootTime == 0) {
    return;
  }
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  RTC_GetTime(&currentTime, &currentDate);
  UpdateSystemUptime();
  printf("System time: %02d-%s-%02d %02dh:%02dm:%02ds, system uptime is: %dd %02dh:%02dm:%02ds\r\n",
      currentDate.Date, monthNames[currentDate.Month-1], currentDate.Year, currentTime.Hours, currentTime.Minutes,
      currentTime.Seconds, myUpTime.Day, myUpTime.Hour, myUpTime.Minutes, myUpTime.Seconds);
}

/*
void setBootTime(void) {
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  RTC_GetTime(&currentTime, &currentDate);
  posixBootTime = makeTime(&currentDate, &currentTime);
}
*/

void UpdateSystemUptime() {
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  uint32_t uxUptime;
  uint32_t time;
  RTC_GetTime(&currentTime, &currentDate);
  uxUptime = makeTime(&currentDate, &currentTime) - posixBootTime;
  time = uxUptime;
  myUpTime.Seconds = time % 60;
  time /= 60; // now it is minutes
  myUpTime.Minutes = time % 60;
  time /= 60; // now it is hours
  myUpTime.Hour = time % 24;
  time /= 24; // now it is days
  myUpTime.Day = time; // now it is days
//  Info("Current time is: %02d:%02d:%02d System uptime is: %dd %02dh:%02dm:%02ds",
//      currentTime.Hours, currentTime.Minutes, currentTime.Seconds, myUpTime.Day, myUpTime.Hour, myUpTime.Minutes, myUpTime.Seconds);
}

//  0         1         2         3  3
//  0         0         0         0  3
//  +CIPSNTPTIME:Thu Jan  1 01:00:03 1970
//OK
uint8_t aBuff2int(char* aBuff, uint8_t start, uint8_t stop) {
  char iBuff[5];
  uint8_t i;
  uint8_t pos = 0;
  for (i = start; i <= stop ; i++){
    iBuff[pos] = aBuff[i];
    pos++;
  }
  iBuff[pos] = '\0';
  if (start < 20) {
    if (start == 17) { //month
      for (i = 0; i < 12; i++) {
        if (strcmp( iBuff, monthNames[i]) == 0) {
          return i+1;
        }
      }
    }
    else {
      //day
      for (i = 0; i < 7; i++) {
        if (strcmp( iBuff, dayNames[i]) == 0) {
          return i+1;
        }
      }
    }
  }
  return atoi(iBuff);
}

void ParseTime(char* buffer) {
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  RTC_GetTime(&currentTime, &currentDate);
  currentTime.Hours = aBuff2int(buffer, 24, 25);
  currentTime.Minutes = aBuff2int(buffer, 27, 28);
  currentTime.Seconds = aBuff2int(buffer, 30, 31);
  currentDate.Year = aBuff2int(buffer, 35, 36);
  currentDate.Month = aBuff2int(buffer, 17, 19);
  currentDate.Date = aBuff2int(buffer, 21,22);
  currentDate.WeekDay = aBuff2int(buffer, 13, 15);
  Debug("Current RTC time before update is: %02dh:%02dm:%02ds", currentTime.Hours , currentTime.Minutes, currentTime.Seconds);
  Debug("Current RTC date before update is: %02d-%02d-%02d", currentDate.Date , currentDate.Month, currentDate.Year  );
  RTC_SetTime(&currentTime);
  RTC_SetDate(&currentDate);
  if (currentDate.WeekDay == 2) {
    reset_fanCleaningDone();
  }
//  Debug("PARSETIME parameters => weekday: %d, year: %d, month: %d, day: %d, hours: %d, minutes: %d, seconds: %d", weekday, year, month, day, hours, minutes, seconds);
  if (posixBootTime == 0) {
    posixBootTime = makeTime(&currentDate, &currentTime);
//    Debug("posixBootTime: %lu", posixBootTime);
  }
}

// Functie om de tijd in te stellen
void RTC_SetTime(RTC_TimeTypeDef* sTime) {
    sTime->TimeFormat = RTC_HOURFORMAT_24;
    sTime->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime->StoreOperation = RTC_STOREOPERATION_RESET;
    
    if (HAL_RTC_SetTime(RealTime_Handle, sTime, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
      Error("Error setting time to RTC");
    }
}

// Functie om de datum in te stellen
void RTC_SetDate(RTC_DateTypeDef* sDate) {
    if (HAL_RTC_SetDate(RealTime_Handle, sDate, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
      Error("Error setting date to RTC");
    }
    //check the backup register
    if (HAL_RTCEx_BKUPRead(RealTime_Handle, RTC_BKP_DR1) != 0xBEBE) {
      // Write Back Up Register 1 Data
      Debug("writing backup register");
      HAL_PWR_EnableBkUpAccess();
      // Writes a data in a RTC Backup data Register 1
      HAL_RTCEx_BKUPWrite(RealTime_Handle, RTC_BKP_DR1, 0xBEBE);
      HAL_PWR_DisableBkUpAccess();
    }
}

// Functie om de tijd uit te lezen
void RTC_GetTime(RTC_TimeTypeDef* gTime, RTC_DateTypeDef* gDate) {
uint8_t t = 1;
uint8_t prevValue = 0;
Battery_Status status;
  status = powerCheck();
  if ( status == BATTERY_CRITICAL) {
//    To be able to read the RTC calendar register when the APB1 clock frequency is less than
//    seven times the RTC clock frequency (7*RTCLCK), the software must read the calendar
//    time and date registers twice.
    t++; //
  }
  for (uint8_t i= 0; i < t; i++) {
    if (HAL_RTC_GetTime(RealTime_Handle, gTime, RTC_FORMAT_BIN) != HAL_OK) {
      Error("Error getting time from RTC");
    }
    if (HAL_RTC_GetDate(RealTime_Handle, gDate, RTC_FORMAT_BIN) != HAL_OK) {
      Error("Error getting date from RTC");
    }
    if ( status == BATTERY_CRITICAL) {
      if (prevValue != gTime->Hours) {
        prevValue = gTime->Hours;
        t++;
      }
      else {
        return;
      }
    }
  }
}

uint8_t RTC_GetWeekday(void) {
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  RTC_GetTime(&currentTime, &currentDate);
  return currentDate.WeekDay;
}

uint32_t getPosixTime(void) {
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
  RTC_GetTime(&currentTime, &currentDate);
  return makeTime(&currentDate, &currentTime);
}

void getUTCfromPosixTime(uint32_t posixTime, char* strbuf1) {
  RTC_TimeTypeDef currentTime;
  RTC_DateTypeDef currentDate;
//  RTC_GetTime(&currentTime, &currentDate);
  breakPosixTime(posixTime, &currentDate, &currentTime);
//  printf("%s %d-%d-%d %dh:%dm:%ds\r\n", dayNames[currentDate.WeekDay - 1], currentDate.Date, currentDate.Month, currentDate.Year,
//      currentTime.Hours, currentTime.Minutes, currentTime.Seconds);
  sprintf(strbuf1, "%02d-%02d-%02d %02dh:%02dm:%02ds\r\n", currentDate.Date, currentDate.Month, currentDate.Year,
      currentTime.Hours, currentTime.Minutes, currentTime.Seconds);
}

// Functie om een alarm in te stellen
void RTC_SetAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_AlarmTypeDef sAlarm = {0};

/*
// alarm elk uur
sAlarm.AlarmMask  = (RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS) ;
sAlarm.AlarmTime.Seconds = 0;
sAlarm.AlarmTime.Minutes = 0;
sAlarm.AlarmTime.SubSeconds = 0;
sAlarm.AlarmSubSecondMask   = RTC_ALARMSUBSECONDMASK_NONE;
ALARM_ActivateAlarm(&sAlarm);

 */

    sAlarm.AlarmTime.Hours = hours;
    sAlarm.AlarmTime.Minutes = minutes;
    sAlarm.AlarmTime.Seconds = seconds;
    sAlarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    sAlarm.Alarm = RTC_ALARM_A;

    if (HAL_RTC_SetAlarm_IT(RealTime_Handle, &sAlarm, RTC_FORMAT_BIN) != HAL_OK) {
        // Foutafhandeling
      Error("Error activating interrupt voor RTC Alarm time");
    }
}


// // Callback voor als het alarm afgaat
// void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
//     // Doe iets wanneer het alarm afgaat
//     HAL_GPIO_TogglePin(LED_C_Red_GPIO_Port, LED_C_Red_Pin);
// }

void RTC_SetWakeUpTimer(uint32_t secondsOfSleep)
{
    //Switch of the timer to reset it

    //Set the prescale so that the clock will be 1Hz
//    HAL_RTCEx_SetWakeUpTimer_IT(RealTime_Handle, secondsOfSleep, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);

//    HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(RTC_IRQn);

    // ==== sleep insert
//    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
    HAL_RTCEx_DeactivateWakeUpTimer(RealTime_Handle);
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(RealTime_Handle, RTC_FLAG_WUTF);
    __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
// for testing 60 seconds => 60 - 1 = 59
//    HAL_RTCEx_SetWakeUpTimer_IT(RealTime_Handle, 0x003D, RTC_WAKEUPCLOCK_CK_SPRE_16BITS); //ck_spre ~1 Hz (40 kHz div127 div 315) used as clock for the RTC wake-up timer
    HAL_RTCEx_SetWakeUpTimer_IT(RealTime_Handle, secondsOfSleep-1, RTC_WAKEUPCLOCK_CK_SPRE_16BITS); //ck_spre ~1 Hz (40 kHz div127 div 315) used as clock for the RTC wake-up timer
     // ==== end sleep insert
}

void Enter_Standby_Mode(void)
{
    // Schakel de clock voor de Power Controller in
    //__HAL_RCC_PWR_CLK_ENABLE();
  Debug("Entering STANDBY mode, deepsleep");
    // prevent waking up by RTC
  HAL_Delay(100);
    HAL_RTCEx_DeactivateWakeUpTimer(RealTime_Handle);
    // Schakel Standby Mode in only is battery is drained
    HAL_SuspendTick();
    HAL_PWR_EnterSTANDBYMode();
    SystemClock_Config();
    HAL_ResumeTick(); // Enable SysTick after wake-up
}

void Enter_Stop_Mode(uint16_t sleepTime)
{
  if (sen5x_On) {
    sen5x_Power_Off();
  }
  Info("Battery voltage %.02fV", ReadBatteryVoltage());
  Debug("Entering STOP mode for %d seconds", sleepTime);
  getUTCfromPosixTime(getPosixTime() + sleepTime, strbuf);
  Info("The system will wake up at %s.", strbuf);
  HAL_Delay(100);
  HAL_SuspendTick();
  RTC_SetWakeUpTimer(sleepTime);
//  HAL_PWREx_EnableFlashPowerDown();  // is default stopped in l0xx cpu's
//  SET_BIT(PWR->CR, PWR_CR_ULP); seems of no influence
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  SystemClock_Config();
  if (sen5x_enable((uint32_t)sleepTime)) {
    showTime();
    set_light_on_state();
    if (!userToggle) {
      RTC_SetWakeUpTimer(SEN5X_START_UP_TIME); // go sleep for 27 + 3s measurement time is approx 30 seconds
      Debug("Entering STOP mode for %d seconds", SEN5X_START_UP_TIME);
      HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
      SystemClock_Config();
//      setsen5xReadTimer(2000);
      setsen5xReadTimer(0);
    }
  }
  HAL_ResumeTick(); // Enable SysTick after wake-up
  showTime();
  ResetDBACalculator();  // reset the DBA average calculation
  ResetSGP40samplecounter();
  setsen5xSamplecounter(0);
//  setESPTimeStamp(3000);
  setESPTimeStamp(2500);
  setSGP40TimeStamp(0);
  setHIDSTimeStamp(0);
  setMICTimeStamp(0);
  ESPTransmitDone = false;
  deviceTimeOut = HAL_GetTick() + 2300;
}

void InitClock(RTC_HandleTypeDef* h_hrtc){
  RealTime_Handle = h_hrtc;
}

/* functions to convert to and from system time */

// leap year calculator expects year argument as years offset from 1970
#define LEAP_YEAR(Y)     ( ((1970+(Y))>0) && !((1970+(Y))%4) && ( ((1970+(Y))%100) || !((1970+(Y))%400) ) )

static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

uint32_t makeTime(RTC_DateTypeDef* currentDate, RTC_TimeTypeDef* currentTime){
// assemble time elements into time_t
// note year argument is offset from 1970 (see macros in time.h to convert to other formats)
// previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9

  int i;
  uint32_t seconds;

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds= currentDate->Year*(SECS_PER_DAY * 365);
  for (i = 0; i < currentDate->Year; i++) {
    if (LEAP_YEAR(i)) {
      seconds += SECS_PER_DAY;   // add extra days for leap years
    }
  }

  // add days for this year, months start from 1
  for (i = 1; i < currentDate->Month; i++) {
    if ( (i == 2) && LEAP_YEAR(currentDate->Year)) {
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
    }
  }
  seconds+= (currentDate->Date-1) * SECS_PER_DAY;
  seconds+= currentTime->Hours * SECS_PER_HOUR;
  seconds+= currentTime->Minutes * SECS_PER_MIN;
  seconds+= currentTime->Seconds;
  return seconds;
}

void breakPosixTime(uint32_t timeInput, RTC_DateTypeDef* currentDate, RTC_TimeTypeDef* currentTime){
// break the given time_t into time components
// this is a more compact version of the C library localtime function
// note that year is offset from 1970 !!!

  uint8_t year;
  uint8_t month, monthLength;
  uint32_t time;
  uint32_t days;

  time = timeInput;
  currentTime->Seconds = time % 60;
  time /= 60; // now it is minutes
  currentTime->Minutes = time % 60;
  time /= 60; // now it is hours
  currentTime->Hours = time % 24;
  time /= 24; // now it is days
  currentDate->WeekDay = ((time - 1) % 7) + 1;  // Monday is day 1, since sat 1-1-2000
  year = 0;
  days = 0;
  while((days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
    year++;
  }
  currentDate->Year = year; // year is offset from 1970

  days -= LEAP_YEAR(year) ? 366 : 365;
  time  -= days; // now it is days in this year, starting at 0

  days=0;
  month=0;
  monthLength=0;
  for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
        monthLength=29;
      } else {
        monthLength=28;
      }
    } else {
      monthLength = monthDays[month];
    }

    if (time >= monthLength) {
      time -= monthLength;
    } else {
        break;
    }
  }
  currentDate->Month = month + 1;  // jan is month 1
  currentDate->Date = time + 1;     // day of month
//  printf("breakPosixTime: daynr: %d, %s %02d-%02d-%d %02d:%02d:%02d\r\n", currentDate->WeekDay, dayNames[currentDate->WeekDay - 1],
//      currentDate->Date, currentDate->Month, currentDate->Year, currentTime->Hours, currentTime->Minutes, currentTime->Seconds);
}

