/*
 * wsenHIDS.c
 *
 *  Created on: Jun 11, 2024
 *      Author: Joris Blankestijn
 */

#include "measurement.h"
#include "wsenHIDS.h"
#include "ESP.h"
#include "sgp40.h"

static float Humidity = 0.0;
static float Temperature = 0.0;

static HIDSHeaterModes HeaterMode = HHM_HIGH_PRECISION_1S_110MW; //HHM_HIGH_PRECISION_1S_200MW;
static HIDSMeasureModes MeasureMode = HMM_HIGH_PRECISION;
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;
static I2CTransmissionDoneCB StatusFunction = NULL;

static uint8_t SerialBuffer[HIDS_SERIAL_BUFFER_LENGTH] = {0};
static uint8_t MeasureBuffer[HIDS_MEASURE_BUFFER_LENGTH] = {0};

static uint32_t HIDS_NextRunTime = HIDS_SENSOR_INITIAL_INTERVAL;
static uint32_t HIDS_Interval_ms = HIDS_SENSOR_INITIAL_INTERVAL;
static bool HIDSResume = false;
static uint32_t HIDSTimeStamp;
SensorType2 *temp = NULL;

static bool ReadRegister(uint8_t address, uint8_t *buffer, uint8_t nrBytes)
{
	if (ReadFunction != NULL)
	{
		return ReadFunction(address, buffer, nrBytes);
	}
	return false;
}

static bool WriteRegister(uint8_t address, uint8_t *buffer, uint8_t nrBytes)
{
	if (WriteFunction != NULL)
	{
		return WriteFunction(address, buffer, nrBytes);
	}
	return false;
}

void hydroTempInit(SensorType2* HT){
	temp = HT;
}

static bool TransmissionDone()
{
	if (StatusFunction != NULL)
	{
		return StatusFunction();
	}
	return false;
}

static uint8_t CalculateCRC(uint8_t *data, uint8_t length)
{
	uint8_t crc = HIDS_CRC_INIT_VALUE;

	for (uint8_t i = 0; i < length; i++)
	{
		// XOR byte into least significant byte of crc
		crc ^= data[i];

		for (uint8_t j = 0; j < 8; j++)
		{
			// If the leftmost (most significant) bit is set
			if (crc & HIDS_CRC_MSB_MASK)
			{
				// Shift left and XOR with polynomial
				crc = (crc << 1) ^ HIDS_CRC_POLYNOMIAL;
			}
			else
			{
				crc <<= 1;
			}
		}
	}
	return crc;
}

void HIDS_EnableHeater(HIDSHeaterModes heaterMode)
{
	WriteRegister(HIDS_I2C_ADDRESS, (uint8_t*) &heaterMode, 1);
	Info("Started the heater in mode: %d", heaterMode);
}

void HIDS_Init(I2CReadCb readFunction, I2CWriteCB writeFunction, I2CTransmissionDoneCB statusFunction)
{
	ReadFunction = readFunction;
	WriteFunction = writeFunction;
	StatusFunction = statusFunction;
}

void HIDS_StartMeasurement(void)
{
	WriteRegister(HIDS_I2C_ADDRESS, &MeasureMode, 1);
	HAL_Delay(10);
}

void HIDS_Resume(bool value)
{
	HIDSResume = value;
}

void setHIDSTimeStamp(uint32_t ticks)
{
	HIDSTimeStamp = HAL_GetTick() + ticks;
}

static bool CheckCRC(uint8_t *data)
{
	uint8_t crcData1[2] = {data[0], data[1]};
	uint8_t crc1 = data[2];
	if (CalculateCRC(crcData1, 2) != crc1)
	{
		Error("CRC check failed for the first segment.");
		return false;
	}

	// Check CRC for the second segment
	uint8_t crcData2[2] = {data[3], data[4]};
	uint8_t crc2 = data[5];
	if (CalculateCRC(crcData2, 2) != crc2)
	{
		Error("CRC check failed for the second segment.");
		errorHandler(__func__, __LINE__, __FILE__);
		return false;
	}
	return true;
}

bool HIDS_DeviceConnected(void)
{
	uint8_t serialReg = HIDS_SERIAL_NUMBER_REG;
	WriteRegister(HIDS_I2C_ADDRESS, &serialReg, 1);
	HAL_Delay(30);
	ReadRegister(HIDS_I2C_ADDRESS, SerialBuffer, HIDS_SERIAL_BUFFER_LENGTH);

	for (uint8_t i = 0; i < HIDS_SERIAL_BUFFER_LENGTH; i++)
	{
		Info("HIDS_Device serial ID[%d]: 0x%X", i, SerialBuffer[i]);
	}
	return CheckCRC(SerialBuffer);
}

bool HIDS_MeasurementReady(void)
{
	return TimestampIsReached(HIDS_NextRunTime);
}

void HIDS_SoftReset(void)
{
	uint8_t resetReg = HIDS_SOFT_RESET_REG;
	WriteRegister(HIDS_I2C_ADDRESS, &resetReg, 1);
	HAL_Delay(10);
}

float Calculate_DewPoint(float humidity, float temperature)
{
	float dewPoint = temperature - ((100 - humidity)/5);	//Not very precise for value's 
	return dewPoint;
}

bool HIDS_GetMeasurementValues(float *humidity, float *temperature)
{
	float currentTemperature;
	float currentHumidity;
	static uint8_t measureBuffer[6] = {0};
	memset(measureBuffer, 0, sizeof(measureBuffer));
	if (!ReadRegister(HIDS_I2C_ADDRESS, measureBuffer, HIDS_MEASURE_BUFFER_LENGTH))
	{
		Error("Error during reading the wsenHIDS result register");
	}
	HAL_Delay(100);
	if (!CheckCRC(measureBuffer))
	{
		for (uint8_t i = 0; i < HIDS_MEASURE_BUFFER_LENGTH; i++)
		{
			Debug("HIDS_Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
		}
		return false;
	}
	currentTemperature = ((175.0f * ((measureBuffer[0] << 8) | measureBuffer[1])) / (float)__UINT16_MAX__);
	currentTemperature -= 45.0f;
	currentHumidity = ((125.0f * ((measureBuffer[3] << 8) | measureBuffer[4]) / (float)__UINT16_MAX__));
	currentHumidity -= 6.0f;

	*temperature = currentTemperature;
	*humidity = currentHumidity;
	return true;
}

void HIDS_Interval(uint32_t interval)
{
	HIDS_Interval_ms = interval;
}

void ResetHIDSresults()
{
	Humidity = 0.0;
	Temperature = 0.0;
}

wsenHIDSState HIDS_Upkeep()
{
	static wsenHIDSState HIDSState = HIDS_STATE_INIT;
	switch (HIDSState)
	{
	case HIDS_STATE_OFF:
		Debug("Measurements are turned off for wsenHIDS sensor.");
		break;

	case HIDS_STATE_INIT:
		if (TransmissionDone())
		{
			ResetHIDSresults();
			HIDSState = HIDS_STATE_START_MEASUREMENTS;
		}
		break;

	case HIDS_STATE_START_MEASUREMENTS:
		if (TransmissionDone())
		{
			HIDS_StartMeasurement();
			HIDSState = HIDS_STATE_WAIT_FOR_COMPLETION;
		}
		break;

	case HIDS_STATE_WAIT_FOR_COMPLETION:
		if (TransmissionDone())
		{
			if (HIDS_GetMeasurementValues(&Humidity, &Temperature))
			{
				if (Calculate_DewPoint(Humidity, Temperature) > (Temperature + 1)) 
				{
					HIDSState = HIDS_STATE_WAIT_FOR_HEATER;
					HIDS_EnableHeater(HeaterMode);
				}
				else
				{
					HIDSState = HIDS_STATE_PROCESS_RESULTS;
				}
			}
		}
		break;

	case HIDS_STATE_WAIT_FOR_HEATER:
		if (TransmissionDone())				
		{
			HIDS_StartMeasurement();
			HIDSTimeStamp = HAL_GetTick() + HIDS_MEASUREMENT_TIME;
			HIDSState = HIDS_STATE_WAIT_FOR_COMPLETION_RH;
		}
		break;

	case HIDS_STATE_WAIT_FOR_COMPLETION_RH:
		if (TimestampIsReached(HIDSTimeStamp))
		{
			if (TransmissionDone())
			{
				HIDS_GetMeasurementValues(&Humidity, &Temperature);
				HIDSState = HIDS_STATE_PROCESS_RESULTS;
			}
		}
		break;

	case HIDS_STATE_PROCESS_RESULTS:
		Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", Humidity, Temperature);
		SGP_SetCompensation(Temperature, Humidity);
		temp->measurementValue2 = Humidity;
		temp->measurementValue1 = Temperature;
		temp->measurementDone = true;
		HIDSState = HIDS_STATE_DONE;
		HIDSResume = false;
		break;

	case HIDS_STATE_DONE:
		if (temp->resume)
		{
			HIDSState = HIDS_STATE_INIT;
			temp->resume = false;
		}
		break;

	case HIDS_STATE_WAIT:
		if (temp->resume){
			HIDSState = HIDS_STATE_INIT;
			temp->resume = false;
		}
		break;

	default:
		// Handle unexpected state
		HIDSState = HIDS_STATE_INIT;
		break;
	}

	return HIDSState;
}