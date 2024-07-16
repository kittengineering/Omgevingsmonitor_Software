/*
 * sgp41.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */
#include <sgp40.h>
#include "utils.h"
#include "stm32l0xx_hal.h"

static bool CheckCRC(uint8_t* data, uint8_t dataLength, uint8_t segmentSize);
static uint8_t CalculateCRC(uint8_t* data, uint8_t length);
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;

static uint8_t ExecuteSelfTestBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x28, 0x0E};
static uint8_t TurnHeaterOffBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x15};
static uint8_t GetSerialNumberBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x82};

static uint8_t MeasureRawSignalBufferCompensated[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x26, 0x0f};
static uint8_t MeasureRawSignalBuffer[SGP_LONG_COMMAND_BUFFER_LENGTH] = {0x26, 0x0f, 0x80, 0x00, 0xA2, 0x66, 0x66, 0x93};
static uint8_t SoftResetBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x00, 0x06};

static uint8_t SGP_ReadBuffer[SGP_SERIAL_NUMBER_RESPONSE_LENGTH] = {0};
//static uint8_t SGP_WriteBuffer[SGP_SERIAL_NUMBER_BUFFER_LENGTH] = {0};

static uint8_t SGP_AmountOfSamplesDone = 0;
static uint8_t SGP_AmountOfSamples = 10;
static uint32_t SGP_HeatUpTime = SGP_SENSOR_HEATUP_TIME;
static uint32_t SGP_MeasurementDutyCycle = SGP_SENSOR_DUTYCYCLE;
static uint32_t SGP_IdleTime = SGP_SENSOR_IDLE_TIME;
static uint32_t SGP_SelfTestRunTime = SGP_SELF_TEST_WAIT_TIME;
static bool SGP_SelfTestStarted = false;

//#define SGP_TEST_BUFFER_SIZE 6
//#define SGP_TEST_SEGMENT_SIZE 3
//static uint8_t SGP_TestBuffer[SGP_TEST_BUFFER_SIZE] = {0xBE, 0xEF, 0x92, 0xBE, 0xEF, 0x92};

static void ReadRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (ReadFunction != NULL) {
    ReadFunction(address, buffer, nrBytes);
  }
}

static void WriteRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (WriteFunction != NULL) {
      WriteFunction(address, buffer, nrBytes);
  }
}

void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
  ReadFunction = readFunction;
  WriteFunction = writeFunction;
}

void SGP_StartMeasurement(void) {
  WriteRegister(SGP_I2C_ADDRESS, MeasureRawSignalBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
  SGP_HeatUpTime = GetCurrentHalTicks() + SGP_SENSOR_HEATUP_TIME;
}

static bool SGP_HeatedUp(void) {
  if(!TimestampIsReached(SGP_HeatUpTime)) return false;
  SGP_IdleTime = GetCurrentHalTicks() + SGP_SENSOR_IDLE_TIME;
  return true;
}

static bool SGP_MeasurementReady(void) {
  if(!TimestampIsReached(SGP_IdleTime))return false;
  Debug("SGP measurement is ready to be read.");
  SGP_MeasurementDutyCycle = GetCurrentHalTicks() + SGP_SENSOR_DUTYCYCLE;
  return true;
}

static bool SGP_MeasurementDone(void) {
  if(!TimestampIsReached(SGP_MeasurementDutyCycle)) return false;
  Debug("SGP_Measurement idle time has passed.");
  return true;
}


void SGP_TurnHeaterOff(void) {
  // This command could take from 0.1 to 1ms.
  WriteRegister(SGP_I2C_ADDRESS, TurnHeaterOffBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
}

bool SGP_GetMeasurementValues(float* vocIndex) {
  if(!SGP_HeatedUp()) {
    // SGP is heated up, we ignore the output and start another measurement.
    WriteRegister(SGP_I2C_ADDRESS, MeasureRawSignalBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
  }
  if(SGP_MeasurementReady()) {
    // Measurement is ready to be read, also turning the heater off.
    ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_MEASURE_BUFFER_RESPONSE_LENGTH);
    if(!CheckCRC(SGP_ReadBuffer, SGP_MEASURE_BUFFER_RESPONSE_LENGTH, SGP_MEASURE_BUFFER_RESPONSE_LENGTH)) {
      Error("SGP measurements CRC check failed.");
      Info("SGP_Measure buffer structure:");
      for(uint8_t i = 0; i < SGP_MEASURE_BUFFER_RESPONSE_LENGTH; i++) {
        Debug("SGP_Measurement buffer[%d]: %d", i, SGP_ReadBuffer[i]);
      }
      return false;
    }
    SGP_TurnHeaterOff();
    SGP_AmountOfSamplesDone += 1;
    if(SGP_AmountOfSamplesDone >= SGP_AmountOfSamples) {
      SGP_AmountOfSamplesDone = 0;
      return true;
    }
    if(SGP_MeasurementDone()) {
      // Starting next measurement
      SGP_StartMeasurement();
    }
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

static bool CheckCRC(uint8_t* data, uint8_t dataLength, uint8_t segmentSize) {
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

static uint8_t CalculateCRC(uint8_t* data, uint8_t length) {
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

void SGP_StartSelfTest(void) {
  if(SGP_SelfTestStarted) return;
  // TODO: Implement the self test so it runs for the first time (above the while loop)
  WriteRegister(SGP_I2C_ADDRESS, ExecuteSelfTestBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
  SGP_SelfTestRunTime = GetCurrentHalTicks() + SGP_SELF_TEST_WAIT_TIME;
  SGP_SelfTestStarted = true;
  // After 320 ms, the master can read a fixed data pattern (1 word + CRC byte) to check if
  // the test was successful or not.
  // Exit measurement mode by turning heater off.
  //  If this command is called when the sensor is in idle mode, the sensor returns to idle mode after the test
}

bool SGP_SelfTestDone(void) {
  if(TimestampIsReached(SGP_SelfTestRunTime)) {
    SGP_SelfTestStarted = false;
    SGP_TurnHeaterOff();
    return true;
  }
  return false;
}

bool SGP_SelfTestSuccessful(void) {
  if(!SGP_SelfTestStarted) {
    Debug("Self test was not started. Starting self test.");
    SGP_StartSelfTest();
    return false;
  }
  if(!SGP_SelfTestDone()) return false;
  ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_SELF_TEST_RESPONSE_LENGTH);
  if(CheckCRC(SGP_ReadBuffer, SGP_SELF_TEST_RESPONSE_LENGTH, SGP_SELF_TEST_SEGMENT_LENGTH)) {
    if(SGP_ReadBuffer[1] == SGP_SELF_TEST_SUCCESS) {
      Debug("All self tests have [PASSED] successfully.");
      return true;
    }else {
      Debug("One or more self tests have [FAILED].");
      return false;
    }
  }
  return false;
}

void SGP_SoftReset(void) {
  // Datasheet mentioned this was a general reset command, which is odd.
  // But if something happens to the i2c bus, this might be the issue.
  // Worth mentioning.
  // This command could take from 0.1 to 1ms.
  WriteRegister(SGP_I2C_ADDRESS, SoftResetBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
}
