/*
 * ESP.h
 *
 *  Created on: Jun 28, 2024
 *      Author: Joris Blankestijn
 */

#ifndef INC_ESP_H_
#define INC_ESP_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "gpio.h"
#include "measurement.h"
#include "PC_Config.h"
#include "statusCheck.h"

//#define LONGMESSAGES true  // show long messages f.i. the datagram on debug UART
#define LONGDATAGRAM
#define ESP_MAX_UART_RETRIES 2
#define ESP_MAX_BUFFER_SIZE 256
#define ESP_TX_BUFFER_SIZE 512
#define ESP_START_UP_TIME 700
#define ESP_RESPONSE_TIME 10
#define ESP_RESPONSE_LONG 50
#define ESP_WIFI_INIT_TIME 1000
#define ESP_DMA_TIMEOUT 100
//#define ESP_AT_COMMANDS_COUNT 4
#define ESP_WIFI_RETRY_TIME 750
#define ESP_WIFI_WAIT_RESPONSE_TIME_FACTOR 3
#define ESP_UNTIL_NEXT_SEND 10000//120000 //240000  // about every 5 minutes (to keep from sending every run, when not in sleep mode)
#define ESP_UNTIL_NEXT_NTP 75398223  //about every 24 hours
#define ESP_MAX_RETRANSMITIONS 3
#define ESP_SEND_TEMP "\"temp\""
#define ESP_SEND_HUMID "\"humid\""
#define ESP_SEND_SOUND "\"sound\""
#define ESP_SEND_VOC "\"voc\""
#define ESP_SEND_BAT "\"Bat\""
#define ESP_SEND_SOL "\"sol\""

#define AT_RESPONSE_OK "OK"
#define AT_RESPONSE_ERROR "ERROR"
#define AT_RESPONSE_FAIL "FAIL"
#define AT_RESPONSE_READY "ready"
#define AT_RESPONSE_START ">"
#define AT_RESPONSE_WIFI "WIFI CONNECTED"
#define AT_RESPONSE_TIME_UPDATED "+TIME_UPDATED"
#define AT_RESPONSE_CIPSNTPTIME "+CIPSNTPTIME:"

#define AT_COMMANDS_SIZE 21

typedef enum {
  AT_MODE_INIT,
  AT_MODE_CONFIG,
  AT_MODE_SEND,
  AT_MODE_RECONFIG,
  AT_MODE_TEST,
  AT_MODE_GETTIME
}AT_Mode;

typedef enum {
  RECEIVE_STATUS_OK,
  RECEIVE_STATUS_ERROR,
  RECEIVE_STATUS_READY,
  RECEIVE_STATUS_INCOMPLETE,
  RECEIVE_STATUS_RETRY,
  RECEIVE_STATUS_START,
  RECEIVE_STATUS_TIMEOUT,
  RECEIVE_STATUS_UNPROGGED,
  RECEIVE_STATUS_HOME,
  RECEIVE_STATUS_SSID,
  RECEIVE_STATUS_TIME
}Receive_Status;

typedef enum {
  RECEIVE_EXPECTATION_OK,
  RECEIVE_EXPECTATION_READY,
  RECEIVE_EXPECTATION_START,
  RECEIVE_EXPECTATION_TIME
} AT_Expectation;

typedef enum {
  AT_WAKEUP,
  AT_SET_RFPOWER,
  AT_CHECK_RFPOWER,
  AT_RESTORE,
  AT_CWINIT,
  AT_CWMODE1,
  AT_CWMODE2,
  AT_CWAUTOCONN,
  AT_CWJAP,
  AT_CWSTATE,
  AT_CWMODE3,
  AT_CWSAP,
  AT_CIPMUX,
  AT_WEBSERVER,
  AT_HTTPCPOST,
  AT_SENDDATA,
  AT_CIPSNTPCFG,
  AT_CIPSNTPTIME,
  AT_CIPSNTPINTV,
  AT_END,
  /// @brief AT commands for debugging /////////////////////////
  // AT_ECHO,
  // AT_SYSLOG
} AT_Commands;

typedef struct {
  char SSID[32];
  char Password[64];
}WifiConfig;

typedef struct {
  char User[30];
  char ChipId[32];
  char BoxAddress[30];
  char TempAddress[30];
  char HumidAddress[30];
  char SoundAddress[30];
  char VOCAddress[30];
  char BatteryChargeAddress[30];
}APIConfig;

typedef enum {
	ESP_STATE_IDLE,
	ESP_STATE_INIT,
	ESP_STATE_WAIT_FOR_REPLY,
	ESP_STATE_SEND,
	ESP_STATE_NEXT_AT,
	ESP_STATE_PROCESS_AT,
	ESP_STATE_ERROR,
	ESP_STATE_WAIT_TO_SEND,
	ESP_STATE_RESET,
	ESP_STATE_RECEIVE_DATA,
	ESP_STATE_MODE_SELECT,
	ESP_STATE_FAULT,
	ESP_STATE_DEINIT,
	ESP_STATE_WAIT_AWAKE,
	ESP_STATE_SEND_DONE,
	ESP_STATE_WAIT_RESET
} ESP_States;


void ESP_Init(UART_HandleTypeDef* espUart);
ESP_States ESP_Upkeep();
void initESPHandler(ESPHandler* ESPHand);
void initUart(UART_HandleTypeDef* espUart);
void ESP_Reset(void);
void ESP_Sleep(void);
void DisableESP(void);
void ESP_WakeTest();
void getWifiCred(void);
void initVariableLink(SensorType2* HT, SensorType1* VOC, SensorType1* DB, SensorType3* Sens);
void SetConfigMode();
void forceNTPupdate();

#endif /* INC_ESP_H_ */

