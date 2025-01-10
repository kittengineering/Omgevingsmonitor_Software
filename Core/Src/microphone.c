/*
 * microphone.c
 *
 *  Created on: Jun 10, 2024
 *      Author: Joris Blankestijn
 *      modified dec 2024 Bert Havinga
 */

#include "microphone.h"
//#include "main.h"
#include "GPIO.h"
#include "sound_measurement.h"
#include "print_functions.h"

static volatile uint32_t StartTime = 0;
static volatile uint32_t StartupDoneTime = 0;
static volatile bool StartUpDone = false;

char mPabuffer[12] = {0};
static float dBA = 0.0;
float dBASamples[NUMBER_OF_SAMPLES] = {0.0};
float dBAAverage = 0.0;
float dBAsum;
float dBValue = 0.0;
float dBAmax = 0.0;
uint8_t counter = 0;
uint8_t denominator = 1;
bool samplebufferfilled = false;
static uint32_t MICTimeStamp;

SoundData_t soundData = {0};

void ResetdBAmax() {
  dBAmax = 0.0;
}
void setMICTimeStamp(uint32_t ticks) {
  MICTimeStamp = HAL_GetTick() + ticks;
}

void ResetDBACalculator(void) {
  counter = 0;
  denominator = 1;
  samplebufferfilled = false;
}

void MIC_Print(void) {
  dBA = dBValue; // dBValue is the actual sample
  dBASamples[counter] = dBA;
  counter++;
  if (counter < NUMBER_OF_SAMPLES && !samplebufferfilled) {
    denominator = counter;
  }
  else {
    denominator = NUMBER_OF_SAMPLES;
    samplebufferfilled = true;
  }
//  dBAmax = 0.0;
  dBAsum = 0.0;
  for(uint8_t i=0; i < denominator; i++){
    dBAsum += dBASamples[i];
    if (dBASamples[i] > dBAmax) {
      dBAmax = dBASamples[i];
  }
  dBAAverage = dBAsum/(float)denominator;
//  setMic(dBAAverage);
  setMic(dBAmax);
  }
  print("SPL_dBA: %.1f, SPL_peak_mPa: %s, dBA peak: %.1f, dBA average: %.1f\r\n", dBA,mPabuffer, dBAmax, dBAAverage);

  if(counter > NUMBER_OF_SAMPLES){
    counter = 0;
  }
  if(dBA >= 90){//white
    SetDBLED(true, true, true);
  }
  if(dBA >= 80 && dBA < 90){ //red
    SetDBLED(true, false, false);
  }
  if(dBA >= 70 && dBA < 80){//yellow
    SetDBLED(true, true, false);
  }
  if(dBA >= 60 && dBA < 70){//Green
    SetDBLED(false, true, false);
  }
  if(dBA >= 50 && dBA < 60){//light blue
    SetDBLED(false, true, true);
  }
  if(dBA >= 40 && dBA < 50){//blue
    SetDBLED(false, false, true);
  }
  if(dBA >= 35 && dBA < 40){//purple
    SetDBLED(true, false, true);
  }
  if(dBA < 35){//off
    SetDBLED(false, false, false);
  }
}

bool MIC_MeasurementDone(void) {
  if(DataReady) {
    MIC_Print();
//    Debug("MIC measurement is done with %i samples.", Samples);
    ResetMICIndicator();
    return true;
  }
  return false;
}

bool MIC_TestMeasurementDone(void) {
  bool Check;
  Info("DataReady in MIC_TestMeasurementDone: %d", DataReady);
  if(DataReady) {
    Check = micEnabled;
    Info("status micEnabled: %d",micEnabled );
    ResetMICIndicator();
    return Check;
  }
  return false;
}

MicrophoneState Mic_Upkeep(){
  static MicrophoneState MicState = MIC_STATE_INIT;
  switch(MicState){

  case MIC_STATE_INIT:
    //reset if necesarry
    if (!enableMicrophone(true)) {
      errorHandler(__func__, __LINE__, __FILE__);
    }
    MicState = MIC_STATE_START_MEASUREMENT;
    break;

  case MIC_STATE_START_MEASUREMENT:
    if (micSettlingComplete() || DataReady) {
      if (!startSPLcalculation())
      {
        errorHandler(__func__, __LINE__, __FILE__);
      }
      MicState = MIC_STATE_WAIT_FOR_COMPLETION;
    }
    break;

  case MIC_STATE_WAIT_FOR_COMPLETION:
    if (getSoundData(&soundData, true, true)) {
      clearMaximumAmplitude();
      char dBbuffer[8];
      sprintf(dBbuffer, "%u.%1u", soundData.SPL_dBA_int, soundData.SPL_dBA_fr_1dp);
      sprintf(mPabuffer, "%u.%02u", soundData.peak_amp_mPa_int, soundData.peak_amp_mPa_fr_2dp);
      dBValue = atof(dBbuffer);
      dBValue = ((int)(dBValue * 100 + .5) / 100.0);
      MIC_Print();
      if (!startSPLcalculation()) {
        errorHandler(__func__, __LINE__, __FILE__);
      }
      if (!enableMicrophone(false)) {
        errorHandler(__func__, __LINE__, __FILE__);
      }
      MICTimeStamp = HAL_GetTick() + 755;  // about every second
      MicState = MIC_STATE_WAIT;
      ResetMICIndicator();
    }
    break;

  case MIC_STATE_WAIT:
    if(TimestampIsReached(MICTimeStamp)){
      if (!enableMicrophone(true)) {
        errorHandler(__func__, __LINE__, __FILE__);
      }
      MicState = MIC_STATE_START_MEASUREMENT;
      SetMICIndicator();
    }
    break;

  default:
    Debug("Unexpected occurrence happened");
    MicState = MIC_STATE_INIT;
    break;
  }

  return MicState;
}
