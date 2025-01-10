/*
 * wsenHIDS.c
 *
 *  Created on: Jun 11, 2024
 *      Author: Joris Blankestijn
 */

#include "wsenHIDS.h"
#include "sgp40.h"
#include "ESP.h"

static float humid = 0.0;
static float temp = 0.0;


static HIDSHeaterModes HeaterMode = HHM_HIGH_PRECISION_1S_200MW;
static HIDSMeasureModes MeasureMode = HMM_HIGH_PRECISION;
static I2CReadCb ReadFunction = NULL;
static I2CWriteCB WriteFunction = NULL;

static uint8_t SerialBuffer[HIDS_SERIAL_BUFFER_LENGTH] = {0};
static uint8_t MeasureBuffer[HIDS_MEASURE_BUFFER_LENGTH] = {0};

static uint32_t HIDS_NextRunTime = HIDS_SENSOR_INITIAL_INTERVAL;
static uint32_t HIDS_Interval_ms = HIDS_SENSOR_INITIAL_INTERVAL;
static uint32_t HIDS_MeasurementDuration = HIDS_SENSOR_INITIAL_INTERVAL;
static bool MeasurementDone = false;

static uint32_t HIDSTimeStamp;
//static uint32_t SensorNextRunTime = HIDS_SENSOR_WAIT_TIME_HIGH;
//static uint32_t SensorWaitTime_ms = HIDS_SENSOR_WAIT_TIME_HIGH;

static bool ReadRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
	if (ReadFunction != NULL) {
		return ReadFunction(address, buffer, nrBytes);
	}
	return false;
}

static bool WriteRegister(uint8_t address, uint8_t* buffer, uint8_t nrBytes) {
  if (WriteFunction != NULL) {
    return WriteFunction(address, buffer, nrBytes);
  }
  return false;
}

static uint8_t CalculateCRC(uint8_t* data, uint8_t length) {
  uint8_t crc = HIDS_CRC_INIT_VALUE;

  for (uint8_t i = 0; i < length; i++) {
    // XOR byte into least significant byte of crc
    crc ^= data[i];

    for (uint8_t j = 0; j < 8; j++) {
      // If the leftmost (most significant) bit is set
      if (crc & HIDS_CRC_MSB_MASK) {
        // Shift left and XOR with polynomial
        crc = (crc << 1) ^ HIDS_CRC_POLYNOMIAL;
      } else {
          crc <<= 1;
      }
    }
  }

//  Debug("CRC calculated value: 0x%X", crc);
  return crc;
}

void HIDS_EnableHeater(void) {
  // During heater operation, the sensor’s specifications are not valid.
  uint8_t heaterReg = HeaterMode;
  WriteRegister(HIDS_I2C_ADDRESS, &heaterReg, 1);
  Info("Started the heater in mode: %d", heaterReg);
}

void HIDS_Init(I2CReadCb readFunction, I2CWriteCB writeFunction) {
	ReadFunction = readFunction;
	WriteFunction = writeFunction;
	HIDS_SetMeasurementMode(MeasureMode);
	HIDS_SetHeaterMode(HeaterMode);
//	HIDS_EnableHeater();
	// TODO: Enable heater after measurement is done and humidity is above a certain percentage, use formula.
}

void HIDS_StartMeasurement(void) {
  HIDS_NextRunTime = HAL_GetTick() + HIDS_Interval_ms;
  WriteRegister(HIDS_I2C_ADDRESS, &MeasureMode, 1);
  MeasurementDone = false;
}

void HIDS_SetMeasurementDuration(uint32_t duration) {
  HIDS_MeasurementDuration = duration;
}

void HIDS_SetHeaterMode(HIDSHeaterModes modeHeater) {
  HeaterMode = modeHeater;
}

void HIDS_SetMeasurementMode(HIDSMeasureModes modeMeasure) {
  MeasureMode = modeMeasure;
}

void setHIDSTimeStamp(uint32_t ticks) {
  HIDSTimeStamp = HAL_GetTick() + ticks;
}

static bool CheckCRC(uint8_t* data) {
  // Data format: 2 bytes for data, followed by an 8-bit CRC

	// Check CRC for the first segment
	uint8_t crcData1[2] = {data[0], data[1]};
	uint8_t crc1 = data[2];
	if (CalculateCRC(crcData1, 2) != crc1) {
		Error("CRC check failed for the first segment.");
//		errorHandler(__func__, __LINE__, __FILE__);
		return false;
	}

	// Check CRC for the second segment
	uint8_t crcData2[2] = {data[3], data[4]};
	uint8_t crc2 = data[5];
	if (CalculateCRC(crcData2, 2) != crc2) {
		Error("CRC check failed for the second segment.");
		errorHandler(__func__, __LINE__, __FILE__);
		return false;
	}
	return true;
}

bool HIDS_DeviceConnected(void) {
	uint8_t serialReg = HIDS_SERIAL_NUMBER_REG;
	WriteRegister(HIDS_I2C_ADDRESS, &serialReg, 1);
	HAL_Delay(30);
	ReadRegister(HIDS_I2C_ADDRESS, SerialBuffer, HIDS_SERIAL_BUFFER_LENGTH);

	for (uint8_t i = 0; i < HIDS_SERIAL_BUFFER_LENGTH; i++) {
		Info("HIDS_Device serial ID[%d]: 0x%X", i, SerialBuffer[i]);
	}
	return CheckCRC(SerialBuffer);
}

bool HIDS_MeasurementReady(void) {
  return TimestampIsReached(HIDS_NextRunTime);
}

void HIDS_SoftReset(void){
  uint8_t resetReg = HIDS_SOFT_RESET_REG;
  WriteRegister(HIDS_I2C_ADDRESS, &resetReg, 1);
}

void ShowHumidity(){
//  humidity = ...
//  if(humidity >= 0 && humidity <= 20){ //From red to orange
//    red = 3000;
//    blue = full;
//    green = (1-(humidity /20))*half;
//  }
//  if(humidity > 20 && humidity <= 40){ orange to yellow
//    red = 3000;
//    green = (1-((humidity - 20)/40))*Full;
//    blue = Full;
//  }
//  if(humidity > 40 && humidity <= 60){
//    red = (1 - ((humidity - 40)/20)*full;
//    green = full;
//    blue = 0;
//  }
//  if(humidity > 60 && humidity <= 80){
//    red = 0;
//    green = Full;
//    blue = ((humidity - 60)/20))*Full;
//  }
//  if(humidity > 80){
//    red = 0;
//    green = (1- ((humidity - 80)/20))*Full;
//    blue = Full;
//  }
}

bool HIDS_GetMeasurementValues(float* humidity, float* temperature) {
  // TODO: Store last measurement humidity for sgp40 measurement.
  if(MeasurementDone) return true;
  if(!HIDS_MeasurementReady()) return false;
//  uint32_t amountOfMeasurements = HIDS_MeasurementDuration / HIDS_Interval_ms;
//  static uint32_t measurements = 0;
  float currentTemperature;
  float currentHumidity;
//  static float temperatures[HIDS_MAX_MEASUREMENTS];
//  static float humidities[HIDS_MAX_MEASUREMENTS];

  //Debug("HT measurements: %d out of %d completed.", measurements + 1, amountOfMeasurements);
  if (!ReadRegister(HIDS_I2C_ADDRESS, MeasureBuffer, HIDS_MEASURE_BUFFER_LENGTH)) {
    Error("Error during reading the wsenHIDS result register");
  }
	if(!CheckCRC(MeasureBuffer)) {
		//Error("HIDS measurements CRC check failed.");
		//Info("Measure buffer structure:");
		for(uint8_t i = 0; i < HIDS_MEASURE_BUFFER_LENGTH; i++) {
			//Debug("HIDS_Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
		}
		return false;
	}

//	for(uint8_t i = 0; i < HIDS_MEASURE_BUFFER_LENGTH; i++) {
//	  Debug("Measurement buffer[%d]: %d", i, MeasureBuffer[i]);
//  }

  // Humidity formula in percentage:
  //  RH = ((-6 + 125 * SRH) / (2^16 - 1))
  // Temperature formula in degrees Celsius:
  //  T = ((-45 + (175 * ST) / (2^16 - 1)))
	currentTemperature = (((175 * ((MeasureBuffer[0] << 8) | MeasureBuffer[1]))) / HIDS_POW_2_16_MINUS_1);
	currentTemperature -= 45;
	currentHumidity = ((125 * ((MeasureBuffer[3] << 8) | MeasureBuffer[4]) / HIDS_POW_2_16_MINUS_1));
	currentHumidity -= 6;

//	if(measurements < amountOfMeasurements) {
//	  temperatures[measurements] = currentTemperature;
//	  humidities[measurements] = currentHumidity;
//	  measurements++;
//	}

//	if (measurements >= amountOfMeasurements) {
//	  // Measurements done, calculating average and returning it.
//    float sumTemperature = 0.0;
//    float sumHumidity = 0.0;
//    for (uint8_t i = 0; i < measurements; i++) {
//        sumTemperature += temperatures[i];
//        sumHumidity += humidities[i];
//    }

   *temperature = currentTemperature;
   *humidity = currentHumidity;

   SGP_GetHT(temperature, humidity);
   ESP_GetHT(currentTemperature, currentHumidity);

//   measurements = 0;
   MeasurementDone = true;
   //HIDS_StartMeasurement();
    //Debug("HIDS measurement is done.");
   return true;
	// Starting another measurement, still not done with all measurements.

	//return false;
}
void ResetHIDSresults() {
  humid = 0.0;
  temp = 0.0;
}

wsenHIDSState HIDS_Upkeep(void) {
  static wsenHIDSState HIDSState = HIDS_STATE_INIT;
  switch(HIDSState) {
    case HIDS_STATE_OFF:
      Debug("Measurements are turned off for wsenHIDS sensor.");
      break;

    case HIDS_STATE_INIT:
//      Debug("entered HIDS_STATE_INIT");
      ResetHIDSresults();
      HIDSState = HIDS_STATE_START_MEASUREMENTS;
      break;

    case HIDS_STATE_START_MEASUREMENTS:
//      Debug("entered HIDS_STATE_START_MEASUREMENTS");
      SetMeasurementIndicator();
      HIDS_StartMeasurement();
      HIDSState = HIDS_STATE_WAIT_FOR_COMPLETION;
      break;

    case HIDS_STATE_WAIT_FOR_COMPLETION:
//      Debug("entered HIDS_STATE_WAIT_FOR_COMPLETION");
      if(HIDS_GetMeasurementValues(&humid, &temp)) {
        HIDSState = HIDS_STATE_PROCESS_RESULTS;
      }
      break;

    case HIDS_STATE_PROCESS_RESULTS:
//      Debug("entered HIDS_STATE_PROCESS_RESULTS");
//      Debug("Processing results.");
      Debug("Humidity value: %3.2f%%, Temperature value: %3.2fC", humid, temp);
      setHIDS(temp, humid);
      ResetMeasurementIndicator();
      HIDSTimeStamp = HAL_GetTick() + (powerCheck() == USB_PLUGGED_IN?10000:1000);  // about every ten seconds when power is plugged
      HIDSState = HIDS_STATE_WAIT;
      break;

    case HIDS_STATE_WAIT:
//      Debug("entered HIDS_STATE_WAIT");
      if(TimestampIsReached(HIDSTimeStamp)) {
        HIDSState = HIDS_STATE_INIT;
      }
      break;

    default:
    // Handle unexpected state
      HIDSState = HIDS_STATE_INIT;
      break;
  }

  return HIDSState;
}
