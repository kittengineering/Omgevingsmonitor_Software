/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "i2s.h"
#include "iwdg.h"
#include "usart.h"
#include "rtc.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "microphone.h"
#include "I2CSensors.h"
#include "utils.h"
#include "measurement.h"
#include "globals.h"
#include "ESP.h"
#include "PowerUtils.h"
#include "usbd_cdc_if.h"
#include "statusCheck.h"
#include "RealTimeClock.h"
#include "sound_measurement.h"
#include "print_functions.h"
#include "sen5x.h"
// #include "sgp40.h"
// #include "wsenHIDS.h"

//Includes Teun
#include "setLED.h"
#include "sgp40.h"
#include "wsenHIDS.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    GADGET_BATTERY_CHECK,
    GADGET_START_MEASUREMENTS,
    GADGET_CHECK_MEASUREMENTS_DONE,
    GADGET_SEND_MEASUREMENTS,
    GADGET_GO_TO_SLEEP,
    GADGET_REINIT_UART,
}gadgetState;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEND_WAIT_TIME_SHORT 300
#define SEND_WAIT_TIME_LONG 600
#define SLEEP_TIME 10
#define LED_ON_SLP_TIME 1000
#define SAFE_DELAY_TIME 20

#define RESUME_ESP_INTERVAL 5*60*1000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
bool testDone = false;
bool ESP_Programming = false;
bool batteryEmpty = false;
static bool priorUSBpluggedIn = false;
// uint8_t SGPstate;
// uint8_t HIDSstate;
// uint8_t MICstate;
uint8_t ESPstate;
bool waitforSamples = false;
uint8_t hidscount = 0;
uint8_t u1_rx_buff[16];                       // rxbuffer for serial logger
uint8_t RxData[UART_CDC_DMABUFFERSIZE] = {0}; // rx buffer for USB
uint16_t IndexRxData = 0;
uint32_t LastRxTime = 0;
uint32_t batteryReadTimer = 0;
uint32_t timeReadTimer = 0;
uint32_t ESPSleepTime = 0;
uint16_t size = 0;

Battery_Status charge;
extern DMA_HandleTypeDef hdma_spi2_rx;

ESPHandler espHandle = {
    .done = false,
    .ready = false,
    .resume = false,
    .startSend = false,
    .connectionMade = false,
    .mode = ESP_PROGRAM_INIT
};

//
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


void petDog(){
  if (HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
    {
      Error_Handler();
    }
}

void ESP_Programming_Read_Remaining_DMA()
{
    // ESP programmer section

    if (LastRxTime != 0 && ESP_Programming)
    {
        if ((LastRxTime + 100) < HAL_GetTick()) // 120
        {
            HAL_UART_DMAPause(&hlpuart1);
            size = __HAL_DMA_GET_COUNTER(hlpuart1.hdmarx);
            if (size > (UART_CDC_DMABUFFERSIZE / 2))
            {
                size = UART_CDC_DMABUFFERSIZE - size;
            }
            else
            {
                size = (UART_CDC_DMABUFFERSIZE / 2) - size;
            }
            if (size > 0)
            {
                CDC_Transmit_FS(&RxData[IndexRxData], size);
                LastRxTime = 0;
                IndexRxData += size;
            }
            HAL_UART_DMAResume(&hlpuart1);
        }
    }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2S2_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART4_UART_Init();
  MX_ADC_Init();
  MX_USB_DEVICE_Init();
  MX_RTC_Init();
  MX_LPUART1_UART_Init();
  MX_TIM6_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
    // General TODO 's
    /*
     * : Put SSID in EEPROM
     * : Turn on heater if humidity is too high
     * : LEDs indicator for air quality
     * : Default network: Sensor community
     * : Different modes for outside and inside (check solar or check LED on/off mode?)
     * : Add CLI via usb-c
     * : Network not found? Sleep
     */
    GPIO_InitPWMLEDs(&htim2, &htim3);
    if (UserButton_Pressed())
    {
        EnableESPProg();
        ESP_Programming = true;
    }
    SetVerboseLevel(VERBOSE_ALL);
    BinaryReleaseInfo();
    HAL_UART_Receive_IT(&huart1, u1_rx_buff, 1);
    InitClock(&hrtc);

    if (!soundInit(&hdma_spi2_rx, &hi2s2, &htim6, DMA1_Channel4_5_6_7_IRQn))
    {
        errorHandler(__func__, __LINE__, __FILE__);
    }
    Device_Init(&hi2c1, &hi2s2, &hadc);
    priorUSBpluggedIn = !Check_USB_PowerOn(); // force the status of the SGP40
    ESPSleepTime = HAL_GetTick() + RESUME_ESP_INTERVAL;
    initESPHandler(&espHandle);
    initUart(&huart4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        static Battery_Status batteryCheck;
        static gadgetState state = GADGET_BATTERY_CHECK;
        static uint16_t sleepTime = SLEEP_TIME;
        processButtonPressed();
        petDog();
        switch(state){
            case GADGET_BATTERY_CHECK:
                batteryCheck = Battery_Upkeep();
                if(batteryCheck == BATTERY_GOOD || batteryCheck == USB_PLUGGED_IN){
                    state = GADGET_START_MEASUREMENTS;
                    sleepTime = SEND_WAIT_TIME_SHORT;
                }
                
                if(batteryCheck == BATTERY_LOW){
                  state = GADGET_START_MEASUREMENTS;
                  sleepTime = SEND_WAIT_TIME_LONG;
                }
                
                if(batteryCheck == BATTERY_CRITICAL){
                    state = GADGET_GO_TO_SLEEP;
                    sleepTime = SEND_WAIT_TIME_LONG;
                }
            break;

            case GADGET_START_MEASUREMENTS:
                measurementReset();
                measurementUpkeep();
                state = GADGET_CHECK_MEASUREMENTS_DONE;
            break;

            case GADGET_CHECK_MEASUREMENTS_DONE:
                bool measurementDone = measurementUpkeep();
                if(measurementDone){ 
                    state = GADGET_SEND_MEASUREMENTS;
                    espHandle.startSend = true;
                    espHandle.timeOutStamp = 60000 + HAL_GetTick();
                }
            break;

            case GADGET_SEND_MEASUREMENTS:
                ESP_Upkeep();
                HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, false);
                if(espHandle.done){
                  state = GADGET_GO_TO_SLEEP;
                  //espHandle.mode = ESP_PROGRAM_INIT;
                  espHandle.startSend = false;
                }
                if(TimestampIsReached(espHandle.timeOutStamp)){
                  HAL_GPIO_WritePin(MCU_LED_C_B_GPIO_Port, MCU_LED_C_B_Pin, true);
                  HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, false);
                  HAL_Delay(1000);
                  HAL_GPIO_WritePin(MCU_LED_C_R_GPIO_Port, MCU_LED_C_R_Pin, true);
                  espHandle.state = ESP_STATE_INIT;
                  //espHandle.mode = ESP_PROGRAM_INIT;
                  espHandle.startSend = false;
                  state = GADGET_GO_TO_SLEEP;
              }
                  
            break;

            case GADGET_GO_TO_SLEEP:
                DisableESP();
                HAL_UART_DeInit(&huart4);
                Debug("UART DeInited");
                espHandle.done = false;
                LEDSOff();
                watchdogStopMode(sleepTime);
                //VOCReset();
                state = GADGET_REINIT_UART;
            break;
                
            case GADGET_REINIT_UART:
              MX_USART4_UART_Init();
              initUart(&huart4);
              measurementReset();
              Debug("Uart reInited");
              state = GADGET_BATTERY_CHECK;
            break;
        }

       

        //Check watchdog


        // ESPstate = ESP_Upkeep();
		// UpdateLEDs();

        // if (ESPstate == ESP_STATE_WAIT_RESET)
        // {
        //     if (CurrentState.led_off)
        //     {
        //         switch (CurrentState.mode)
        //         {
        //             case (Mode_t)USB_POWERED_MODE:
        //                 EnterStop(&hrtc, 5*60);
        //                 setResumeESP(true);
        //                 break;
                    
        //             case (Mode_t)BATTERY_POWERED_MODE:
        //                 EnterStop(&hrtc, 15*60);
        //                 setResumeESP(true);
        //                 break;
        //         }
        //     }
        //     else
        //     {
        //         if (TimestampIsReached(ESPSleepTime))
        //         {
        //             setResumeESP(true);
        //             ESPSleepTime = HAL_GetTick() + RESUME_ESP_INTERVAL;
        //         }
        //     }
        // }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_LPUART1
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_RTC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// Provide a print interface for print_functions.
void printString(const char *str, uint16_t length)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)str, length, 0xFFFF);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
        NVIC_SystemReset();
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
