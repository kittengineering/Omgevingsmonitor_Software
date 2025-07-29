/*
 * sgp41.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 */
#include "stm32l0xx_hal.h"
#include "utils.h"
#include "sensirion_gas_index_algorithm.h"
// #include "wsenHIDS.h"
#include "main.h"
#include "rtc.h"
#include "statusCheck.h"
#include "RealTimeClock.h"

#include "sgp40.h"
#include "measurement.h"
#include "setLED.h"
#include "wsenHIDS.h"
#include "I2CSensors.h"

static bool CheckCRC(uint8_t *data, uint8_t dataLength, uint8_t segmentSize);
static uint8_t CalculateCRC(uint8_t *data, uint8_t length);
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;
static I2CTransmissionDoneCB StatusFunction = NULL;

static uint8_t ExecuteSelfTestBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x28, 0x0E};
static uint8_t TurnHeaterOffBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x15};
static uint8_t GetSerialNumberBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x36, 0x82};

static uint8_t SoftResetBuffer[SGP_SHORT_COMMAND_BUFFER_LENGTH] = {0x00, 0x06};
static uint8_t SGP_ReadBuffer[SGP_SERIAL_NUMBER_RESPONSE_LENGTH] = {0};

static uint32_t SGP_SelfTestRunTime = SGP_SELF_TEST_WAIT_TIME;
static uint32_t SGP40TimeStamp;
static uint32_t SGP40NextMeasurement;
static bool SGP_SelfTestStarted = false;
static bool SGP40Resume = false;
static GasIndexAlgorithmParams params;
SensorType1* VOCout = NULL;

static int32_t VocIndex;
static uint32_t SGP40Interval;


void initVOC(SensorType1* vocout){
    VOCout = vocout;
}

static void ReadRegister(uint8_t address, uint8_t *buffer, uint8_t nrBytes)
{
    if (ReadFunction != NULL)
    {
        ReadFunction(address, buffer, nrBytes);
    }
}

static void WriteRegister(uint8_t address, uint8_t *buffer, uint8_t nrBytes)
{
    if (WriteFunction != NULL)
    {
        WriteFunction(address, buffer, nrBytes);
    }
}

static bool TransmissionDone()
{
    if (StatusFunction != NULL)
    {
        return StatusFunction();
    }
    return false;
}


void SGP40_Resume(bool value)
{
	SGP40Resume = value;
}

void SGP_Init(I2CReadCb readFunction, I2CWriteCB writeFunction, I2CTransmissionDoneCB statusFunction)
{
    ReadFunction = readFunction;
    WriteFunction = writeFunction;
    StatusFunction = statusFunction;
    GasIndexAlgorithm_init(&params, GasIndexAlgorithm_ALGORITHM_TYPE_VOC);
}

void SGP_TurnHeaterOff(void)
{
    // This command could take from 0.1 to 1ms.
    WriteRegister(SGP_I2C_ADDRESS, TurnHeaterOffBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
}

bool SGP_DeviceConnected(void)
{
    WriteRegister(SGP_I2C_ADDRESS, GetSerialNumberBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
    HAL_Delay(1); // 1ms delay for the sensor to respond (according to datasheet)
    ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_SERIAL_NUMBER_RESPONSE_LENGTH);
    for (uint8_t i = 0; i < SGP_SERIAL_NUMBER_RESPONSE_LENGTH; i++)
    {
        Info("SGP_Device serial ID[%d]: 0x%X", i, SGP_ReadBuffer[i]);
    }
    return CheckCRC(SGP_ReadBuffer, SGP_SERIAL_NUMBER_RESPONSE_LENGTH, SGP_SERIAL_NUMBER_SEGMENT_SIZE);
}

static bool CheckCRC(uint8_t *data, uint8_t dataLength, uint8_t segmentSize)
{
    for (uint8_t i = 0; i < dataLength; i += segmentSize)
    {
        uint8_t crcData[segmentSize];

        for (uint8_t j = 0; j < segmentSize; j++)
        {
            crcData[j] = data[i + j];
        }
        uint8_t crc = data[i + segmentSize - 1];

        if (CalculateCRC(crcData, segmentSize - 1) != crc)
        {
            Error("CRC check failed for segment: %d.", i + 1);
            return false;
        }
    }
    return true;
}

uint8_t CalculateCRC(uint8_t *data, uint8_t length)
{
    static uint8_t crc; 
    crc = SGP_CRC_INIT_VALUE;

    for (uint8_t i = 0; i < length; i++)
    {
        // XOR byte into least significant byte of crc
        crc ^= data[i];

        for (uint8_t j = 0; j < 8; j++)
        {
            // If the leftmost (most significant) bit is set
            if (crc & SGP_CRC_MSB_MASK)
            {
                // Shift left and XOR with polynomial
                crc = (crc << 1) ^ SGP_CRC_POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    //  Info("SGP_CRC calculated value: 0x%X", crc);
    return crc;
}

void SGP_StartSelfTest(void)
{
    if (SGP_SelfTestStarted)
        return;
    // TODO: Implement the self test so it runs for the first time (above the
    // while loop)
    WriteRegister(SGP_I2C_ADDRESS, ExecuteSelfTestBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
    SGP_SelfTestRunTime = HAL_GetTick() + SGP_SELF_TEST_WAIT_TIME;
    SGP_SelfTestStarted = true;
    // After 320 ms, the master can read a fixed data pattern (1 word + CRC byte)
    // to check if the test was successful or not. Exit measurement mode by
    // turning heater off.
    //  If this command is called when the sensor is in idle mode, the sensor
    //  returns to idle mode after the test
}

bool SGP_SelfTestDone(void)
{
    if (TimestampIsReached(SGP_SelfTestRunTime))
    {
        SGP_SelfTestStarted = false;
        SGP_TurnHeaterOff();
        return true;
    }
    return false;
}

bool SGP_SelfTestSuccessful(void)
{
    if (!SGP_SelfTestStarted)
    {
        Debug("Self test was not started. Starting self test.");
        SGP_StartSelfTest();
        return false;
    }
    if (!SGP_SelfTestDone())
        return false;
    ReadRegister(SGP_I2C_ADDRESS, SGP_ReadBuffer, SGP_SELF_TEST_RESPONSE_LENGTH);
    if (CheckCRC(SGP_ReadBuffer, SGP_SELF_TEST_RESPONSE_LENGTH,
                 SGP_SELF_TEST_SEGMENT_LENGTH))
    {
        if (SGP_ReadBuffer[1] == SGP_SELF_TEST_SUCCESS)
        {
            Debug("All self tests have [PASSED] successfully.");
            return true;
        }
        else
        {
            Debug("One or more self tests have [FAILED].");
            return false;
        }
    }
    return false;
}

//Teun zijn code

// #define UINT16_MAX 65535

Compensation_t Compensation = {0};

uint16_t VocRaw = 0;

void ResetVOCresult(void)
{
    VocIndex = 0;
}

void SGP_SoftReset(void)
{
    Debug("SGP40 brought to idle");
    SGP_TurnHeaterOff();
    HAL_Delay(10);
    WriteRegister(SGP_I2C_ADDRESS, SoftResetBuffer, SGP_SHORT_COMMAND_BUFFER_LENGTH);
}

void SGP_SetCompensation(float temperature, float humidity)
{
    Compensation.temperatureComp = (temperature + 45) * (float)(__UINT16_MAX__ / 175);
    Compensation.humidityComp = humidity * (float)(__UINT16_MAX__ / 100);
    Compensation.lastUpdate = HAL_GetTick();
}

bool RecentCompensation()
{
    if (!TimestampIsReached(Compensation.lastUpdate + SGP_OLD_COMPENSATION))
    {
        return true;
    }
    return false;
}

void SGP_StartRawMeasurement()
{
    static uint8_t buffer[SGP_LONG_COMMAND_BUFFER_LENGTH] = {0};
    buffer[0] = 0x26;
    buffer[1] = 0x0F;
    buffer[2] = (Compensation.humidityComp >> 8);
    buffer[3] = (uint8_t) (Compensation.humidityComp & 0x00FF);
    buffer[4] = CalculateCRC(&buffer[2], 2);
    buffer[5] = (Compensation.humidityComp >> 8);
    buffer[6] = (uint8_t) (Compensation.humidityComp & 0x00FF);
    buffer[7] = CalculateCRC(&buffer[5], 2);
    WriteRegister(SGP_I2C_ADDRESS, buffer, SGP_LONG_COMMAND_BUFFER_LENGTH);
}

bool SGP_GetRawMeasurement(uint16_t *rawValue)
{
    uint8_t buffer[3] = {0};
    ReadRegister(SGP_I2C_ADDRESS, buffer, 3);
    HAL_Delay(1);
    uint8_t crc = CalculateCRC(&buffer[0], 2);
    if (buffer[2] == crc)
    {
        *rawValue = ((uint16_t)buffer[0] << 8) | buffer[1];
        return true;
    }
    return false;
}

SGP40State SGP_Upkeep()//State gadgetState)
{
    static SGP40State SGPState = SGP_STATE_INIT;
    switch (SGPState)
    {
    case SGP_STATE_OFF:
        Debug("Measurements are turned off for SGP40.");
        break;

    case SGP_STATE_INIT:
        ResetVOCresult();                           //Set VOCindex to zero
        SGP40NextMeasurement = HAL_GetTick() + SGP40Interval;
        SGPState = SGP_STATE_START_FIRST_MEASUREMENT;
        break;

    case SGP_STATE_START_FIRST_MEASUREMENT:
        if (RecentCompensation())
        {
            if (TransmissionDone())                                                                 //Only transmit if possible otherwise wait
            {
                SGP_StartRawMeasurement(Compensation.temperatureComp, Compensation.humidityComp);   //Start the first measurement
                SGP40TimeStamp = HAL_GetTick() + SGP_SENSOR_IDLE_TIME;
                SGPState = SGP_STATE_WAIT_FOR_HEAT_UP;
            }
        }
        break;
        
    case SGP_STATE_WAIT_FOR_HEAT_UP:
        if (TimestampIsReached(SGP40TimeStamp))                                                     //It takes 30mS to get any measurement
        {      
            if (TransmissionDone())                                                                 //Only transmit if possible otherwise wait
            {                 
                if (SGP_GetRawMeasurement(&VocRaw))                                                 //Check if measurement finished and discard the first measurement
                {                       
                    SGP40TimeStamp = HAL_GetTick() + SGP_SENSOR_HEATUP_TIME;                        //It takes 170mS to heat up the sensor to get a good reading
                    SGPState = SGP_STATE_START_MEASUREMENTS;                        
                }                       
                else                        
                {                       
                    SGPState = SGP_STATE_START_FIRST_MEASUREMENT;                                   //Retry if CRC errro
                }
            }
        }
        break;

    case SGP_STATE_START_MEASUREMENTS:
        if (TimestampIsReached(SGP40TimeStamp))                                                     //Wait for the heat up time
        {               
            if(RecentCompensation() && TransmissionDone())                                          //Only run with updated compensation levels and if transmit is possible
            {
                SGP_StartRawMeasurement(Compensation.temperatureComp, Compensation.humidityComp);   //Start the real measurement
                SGPState = SGP_STATE_WAIT_FOR_COMPLETION;
            }
        }
        break;

    case SGP_STATE_WAIT_FOR_COMPLETION:
        if (TransmissionDone())                                                                     //Minimum tijd wachten?
        {
            if (SGP_GetRawMeasurement(&VocRaw))
            {
                SGPState = SGP_STATE_PROCESS_RESULTS;
            }
        }
        break;

    case SGP_STATE_PROCESS_RESULTS:
        if (TransmissionDone())
        {
            GasIndexAlgorithm_process(&params, VocRaw, &VocIndex);
            VOCout->measurementValue = (float)VocIndex;
            VOCout->measurementDone = true;
            SGP_SoftReset();
            SGPState = SGP_STATE_DONE;
            SGP40Resume = false;
        }
        break;

    case SGP_STATE_DONE:
        if (VOCout->resume)
		{
            SGPState = SGP_STATE_INIT;
            VOCout->resume = false;
        }
        break;

    default:
        // Handle unexpected state
        SGPState = SGP_STATE_INIT;
        break;
    }
    return SGPState;
}

void UpdateAlgorithmInterval(uint32_t interval)
{
    params.mSamplingInterval = (float)interval/1000;
    SGP40Interval = interval;
}
