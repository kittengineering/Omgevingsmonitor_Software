/*
 * sgp41.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "sensirion_gas_index_algorithm.h"
#include "wsenHIDS.h"
#include "main.h"
#include <sgp40.h>


static bool CheckCRC(uint8_t *data, uint8_t dataLength, uint8_t segmentSize);
static uint8_t CalculateCRC(uint8_t *data, uint8_t length);
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;

static uint8_t ExecuteSelfTestBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x28, 0x0E};
static uint8_t TurnHeaterOffBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x15};
static uint8_t GetSerialNumberBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x82};

//static uint8_t MeasureRawSignalBufferCompensated[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x26, 0x0f};
static uint8_t MeasureRawSignalBuffer[SGP_LONG_COMMAND_BUFFER_LENGTH] = {0x26, 0x0F, 0x80, 0x00, 0xA2, 0x66, 0x66, 0x93};
static uint8_t MeasureRawWithCompBuffer[SGP_LONG_COMMAND_BUFFER_LENGTH] = {0x26, 0x0F};
static uint8_t SoftResetBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x00, 0x06};
static uint8_t SGP_ReadBuffer[SGP_SERIAL_NUMBER_RESPONSE_LENGTH] = {0};
// static uint8_t SGP_WriteBuffer[SGP_SERIAL_NUMBER_BUFFER_LENGTH] = {0};

static uint8_t SGP_AmountOfSamplesDone = 0;
static uint8_t SGP_TotalSamples = 1;
static uint32_t SGP_HeatUpTime = SGP_SENSOR_HEATUP_TIME;
static uint32_t SGP_MeasurementDutyCycle = SGP_SENSOR_DUTYCYCLE;
static uint32_t SGP_IdleTime = SGP_SENSOR_IDLE_TIME;
static uint32_t SGP_SelfTestRunTime = SGP_SELF_TEST_WAIT_TIME;
static bool SGP_SelfTestStarted = false;
static bool HeatUpIsDone = false;
static bool MeasurementIsReady = false;
static GasIndexAlgorithmParams params;

static uint16_t SGP_Hum;
static uint16_t SGP_Temp;
static bool HT_MeasurementReceived = false;
static bool SGP_MsgSent = false;

static uint16_t Red;
static uint16_t Blue;
static uint16_t Green;
static uint16_t TimeValue = 4000;

//#define SGP_TEST_BUFFER_SIZE 6
//#define SGP_TEST_SEGMENT_SIZE 3
// static uint8_t SGP_TestBuffer[SGP_TEST_BUFFER_SIZE] = {0xBE, 0xEF, 0x92,
// 0xBE, 0xEF, 0x92};

static void ReadRegister(uint8_t address, uint8_t *buffer, uint8_t nrBytes) {
  if (ReadFunction != NULL) {
    ReadFunction(address, buffer, nrBytes);
  }
}

static void WriteRegister(uint8_t address, uint8_t *buffer, uint8_t nrBytes) {
  if (WriteFunction != NULL) {
    WriteFunction(address, buffer, nrBytes);
  }
}

void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
  ReadFunction = readFunction;
  WriteFunction = writeFunction;
  GasIndexAlgorithm_init(&params, GasIndexAlgorithm_ALGORITHM_TYPE_VOC);
}

void SGP_StartMeasurement(void) {
  if(HT_MeasurementReceived){
    WriteRegister(SGP_I2C_ADDRESS, MeasureRawWithCompBuffer, SGP_LONG_COMMAND_BUFFER_LENGTH);
    SGP_IdleTime = GetCurrentHalTicks() + SGP_SENSOR_IDLE_TIME;
  }
  else{
    WriteRegister(SGP_I2C_ADDRESS, MeasureRawSignalBuffer, SGP_LONG_COMMAND_BUFFER_LENGTH);
    SGP_HeatUpTime = GetCurrentHalTicks() + SGP_SENSOR_HEATUP_TIME;
  }
  HeatUpIsDone = false;
  MeasurementIsReady = false;
}

static bool SGP_HeatedUp(void) { return TimestampIsReached(SGP_HeatUpTime); }

static bool SGP_MeasurementReady(void) {
  return TimestampIsReached(SGP_IdleTime);
}

static bool SGP_MeasurementDone(void) {
  return TimestampIsReached(SGP_MeasurementDutyCycle);
}

void SGP_TurnHeaterOff(void) {
  // This command could take from 0.1 to 1ms.
  WriteRegister(SGP_I2C_ADDRESS, TurnHeaterOffBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
}

bool SGP_GetMeasurementValues(int32_t *vocIndex) {
  if (SGP_HeatedUp() && !HeatUpIsDone && !SGP_MsgSent) {
    Debug("SGP is heated up, starting the measurement.");
    HeatUpIsDone = true;
    // SGP is heated up, we ignore the output and start another measurement.
    if(HT_MeasurementReceived){
      WriteRegister(SGP_I2C_ADDRESS, MeasureRawWithCompBuffer, SGP_LONG_COMMAND_BUFFER_LENGTH);
      SGP_IdleTime = GetCurrentHalTicks() + SGP_SENSOR_IDLE_TIME;
    }
    else{
      WriteRegister(SGP_I2C_ADDRESS, MeasureRawSignalBuffer, SGP_LONG_COMMAND_BUFFER_LENGTH);
      SGP_IdleTime = GetCurrentHalTicks() + SGP_SENSOR_IDLE_TIME;
    }
    SGP_MsgSent = true;
  }
  if (HeatUpIsDone && SGP_MeasurementReady() && !MeasurementIsReady) {
    Debug("SGP_Measurement[%i] is ready, reading buffer.", SGP_AmountOfSamplesDone + 1);
    MeasurementIsReady = true;
    // Measurement is ready to be read, also turning the heater off.
    ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_MEASURE_BUFFER_RESPONSE_LENGTH);
    if (!CheckCRC(SGP_ReadBuffer, SGP_MEASURE_BUFFER_RESPONSE_LENGTH, SGP_MEASURE_BUFFER_RESPONSE_LENGTH)) {
      Error("SGP measurements CRC check failed.");
      Info("SGP_Measure buffer structure:");
      for (uint8_t i = 0; i < SGP_MEASURE_BUFFER_RESPONSE_LENGTH; i++) {
        Debug("SGP_Measurement buffer[%d]: %d", i, SGP_ReadBuffer[i]);
      }
      return false;
    }
    SGP_MeasurementDutyCycle = GetCurrentHalTicks() + SGP_SENSOR_DUTYCYCLE;
    SGP_TurnHeaterOff();
    SGP_AmountOfSamplesDone += 1;
    if (SGP_AmountOfSamplesDone >= SGP_TotalSamples) {
      uint16_t rawSignal = ((SGP_ReadBuffer[1] << 8) | (SGP_ReadBuffer[0]));
      Debug("rawSignal value: %d", rawSignal);
      int32_t tempVocIndex = 0;
      GasIndexAlgorithm_process(&params, rawSignal, &tempVocIndex);
      Debug("vocIndex value: %d", tempVocIndex);
//      *vocIndex = 1337;
      *vocIndex = tempVocIndex;
      if(*vocIndex > 0){
        // TODO add status LED logic.
//        HAL_GPIO_TogglePin(STATUS2_LED_GPIO_Port, STATUS2_LED_Pin);
      }
      if(*vocIndex > 0 && *vocIndex <= 100){
      Green = (1.0-(*vocIndex/100.0))*TimeValue;
      Blue = (*vocIndex/100.0)*TimeValue;
      Red = TimeValue;
      SetVocLED(Red, Green, Blue);
      }
      if(*vocIndex > 100){
        Green = (((*vocIndex-100.0)/400.0))*TimeValue;
        Red = (1.0-((*vocIndex-100.0)/400.0))*TimeValue;
        Blue = TimeValue;
        SetVocLED(Red, Green, Blue);
      }
      SGP_AmountOfSamplesDone = 0;
      Debug("SGP_Measurement completely done.");
      HT_MeasurementReceived = false;
      SGP_MsgSent = false;
//      for (uint8_t i = 0; i < SGP_MEASURE_BUFFER_RESPONSE_LENGTH; i++) {
//        Debug("SGP_Measurement buffer[%d]: %d", i, SGP_ReadBuffer[i]);
//      }
      return true;
    }
  }
  if (SGP_MeasurementDone() && HeatUpIsDone && MeasurementIsReady) {
    // Starting next measurement
    Debug("Starting next SGP_measurement.");
    SGP_StartMeasurement();
    SGP_MsgSent = false;
  }
  return false;
}

bool SGP_DeviceConnected(void) {
  WriteRegister(SGP_I2C_ADDRESS, GetSerialNumberBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
  HAL_Delay(1); // 1ms delay for the sensor to respond (according to datasheet)
  ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_SERIAL_NUMBER_RESPONSE_LENGTH);
  for (uint8_t i = 0; i < SGP_SERIAL_NUMBER_RESPONSE_LENGTH; i++) {
    Info("SGP_Device serial ID[%d]: 0x%X", i, SGP_ReadBuffer[i]);
  }
  return CheckCRC(SGP_ReadBuffer, SGP_SERIAL_NUMBER_RESPONSE_LENGTH, SGP_SERIAL_NUMBER_SEGMENT_SIZE);
}

static bool CheckCRC(uint8_t *data, uint8_t dataLength, uint8_t segmentSize) {
  for (uint8_t i = 0; i < dataLength; i += segmentSize) {
    uint8_t crcData[segmentSize];

    for (uint8_t j = 0; j < segmentSize; j++) {
      crcData[j] = data[i + j];
    }
    uint8_t crc = data[i + segmentSize - 1];

    if (CalculateCRC(crcData, segmentSize - 1) != crc) {
      Error("CRC check failed for segment: %d.", i + 1);
      return false;
    }
  }
  return true;
}

static uint8_t CalculateCRC(uint8_t *data, uint8_t length) {
  uint8_t crc = SGP_CRC_INIT_VALUE;

  for (uint8_t i = 0; i < length; i++) {
    // XOR byte into least significant byte of crc
    crc ^= data[i];

    for (uint8_t j = 0; j < 8; j++) {
      // If the leftmost (most significant) bit is set
      if (crc & SGP_CRC_MSB_MASK) {
        // Shift left and XOR with polynomial
        crc = (crc << 1) ^ SGP_CRC_POLYNOMIAL;
      } else {
        crc <<= 1;
      }
    }
  }
  //  Info("SGP_CRC calculated value: 0x%X", crc);
  return crc;
}

void SGP_GetHT(float* temperature, float* humidity){
  uint8_t humBuf[2];
  uint8_t tempBuf[2];
  SGP_Temp = (uint16_t)(((*temperature+45.0f)/175.0f)*(float)0xFFFF);
  SGP_Hum = ((*humidity/100.0f)*(float)0xFFFF);
  humBuf[0] = MeasureRawWithCompBuffer[2] = SGP_Hum >> 8;
  humBuf[1] = MeasureRawWithCompBuffer[3] = SGP_Hum;
  MeasureRawWithCompBuffer[4] = CalculateCRC(humBuf, 2);
  tempBuf[0] = MeasureRawWithCompBuffer[5] = SGP_Temp >> 8;
  tempBuf[1] = MeasureRawWithCompBuffer[6] = SGP_Temp;
  MeasureRawWithCompBuffer[7] = CalculateCRC(tempBuf, 2);
  HT_MeasurementReceived = true;
}

void SGP_StartSelfTest(void) {
  if (SGP_SelfTestStarted)
    return;
  // TODO: Implement the self test so it runs for the first time (above the
  // while loop)
  WriteRegister(SGP_I2C_ADDRESS, ExecuteSelfTestBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
  SGP_SelfTestRunTime = GetCurrentHalTicks() + SGP_SELF_TEST_WAIT_TIME;
  SGP_SelfTestStarted = true;
  // After 320 ms, the master can read a fixed data pattern (1 word + CRC byte)
  // to check if the test was successful or not. Exit measurement mode by
  // turning heater off.
  //  If this command is called when the sensor is in idle mode, the sensor
  //  returns to idle mode after the test
}

bool SGP_SelfTestDone(void) {
  if (TimestampIsReached(SGP_SelfTestRunTime)) {
    SGP_SelfTestStarted = false;
    SGP_TurnHeaterOff();
    return true;
  }
  return false;
}

bool SGP_SelfTestSuccessful(void) {
  if (!SGP_SelfTestStarted) {
    Debug("Self test was not started. Starting self test.");
    SGP_StartSelfTest();
    return false;
  }
  if (!SGP_SelfTestDone())
    return false;
  ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_SELF_TEST_RESPONSE_LENGTH);
  if (CheckCRC(SGP_ReadBuffer, SGP_SELF_TEST_RESPONSE_LENGTH,
               SGP_SELF_TEST_SEGMENT_LENGTH)) {
    if (SGP_ReadBuffer[1] == SGP_SELF_TEST_SUCCESS) {
      Debug("All self tests have [PASSED] successfully.");
      return true;
    } else {
      Debug("One or more self tests have [FAILED].");
      return false;
    }
  }
  return false;
}

void SGP_SoftReset(void) {
  /* Joris: Datasheet mentioned this was a general reset command, which is odd.
  // But if something happens to the i2c bus, this might be the issue.
  Worth mentioning. */
  // Danny: Its not odd, its a general reset command which is a standard syntaxis. So do not use blind.
  // This command could take from 0.1 to 1ms.
  WriteRegister(SGP_I2C_ADDRESS, SoftResetBuffer,
                SGP_SHORT_COMMAND_BUFFER_LENGTH);
}
