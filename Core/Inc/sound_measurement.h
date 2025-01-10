// Convert I2S data from a microphone into A-weighted Sound Pressure Level (SPL) measurements.
// This code is ARM/STM32-specific but is not limited to a particular device.
//
// Brief explanation of use:
// 1) Create external functions which initialise I2S, DMA and timer peripherals,
//    then pass function pointers to soundInit().
// 2) Call enableMicrophone() to start the collection of I2S data in the circular
//    DMA buffer.
// 3) Call startSPLcalculation() when ready to acquire data and calculate output.
// 4) Use getSoundData() to check for completion of calculation and obtain result.
// 5) Use clearMaximumAmplitude() at any time to reset the peak amplitude (which
//    is output in addition to SPL).

#ifndef SOUND_MEASUREMENT_H
#define SOUND_MEASUREMENT_H

#include <stdbool.h>
#include "stm32l0xx_hal.h"
#include "sound_LUTs.h"

// Sound settings
#define FFT_N 128   // FFT points; can be 128 - 1024
#define I2S_AUDIOFREQ I2S_AUDIOFREQ_16K  // Can be 16, 32, 48
#define FILTER_SPL_N 16 // the number of consecutive SPL calculations to average over

extern volatile bool micEnabled;
extern volatile bool DataReady;
////////////////////////////////////////////////////////

typedef struct __attribute__((packed)) {
    uint8_t  SPL_dBA_int;
    uint8_t  SPL_dBA_fr_1dp;
    uint8_t  SPL_bands_dB_int[SOUND_FREQ_BANDS];
    uint8_t  SPL_bands_dB_fr_1dp[SOUND_FREQ_BANDS];
    uint16_t peak_amp_mPa_int;
    uint8_t  peak_amp_mPa_fr_2dp;
    uint8_t  stable;
} SoundData_t;

////////////////////////////////////////////////////////
// User interface functions:

//bool soundInit(void (*DMAInit)(DMA_HandleTypeDef **),
//               bool (*I2SInit)(I2S_HandleTypeDef **),
//               bool (*tmrInit)(TIM_HandleTypeDef **), IRQn_Type DMAChIRQn);
bool soundInit(DMA_HandleTypeDef* hdma_spi2_r,
               I2S_HandleTypeDef* hi2s2,
               TIM_HandleTypeDef* htim6,
               IRQn_Type DMAChIRQn);
bool enableMicrophone(bool bEnable);
void clearMaximumAmplitude(void);
bool startSPLcalculation(void);
bool getSoundData(SoundData_t * data, bool getSPLdata, bool getMaxAmpData);
bool micSettlingComplete(void);

#ifdef TESTS
void test_soundSystem(void);
#endif

#endif
