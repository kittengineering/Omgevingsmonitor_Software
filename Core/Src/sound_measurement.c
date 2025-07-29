// Convert I2S data from a microphone into A-weighted Sound Pressure Level (SPL).
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

#include <sound_utilities.h>
#include <stdint.h>
#include <stdlib.h>
#include "arm_math.h"
#include "sound_measurement.h"
#include "arm_const_structs.h"
#include <stdbool.h>
#include "stm32l0xx_hal.h"
#include "sound_LUTs.h"
#include "sound_LUT_select.h"
#include "math.h"
#include "microphone_constants.h" // Supply this to define the microphone response
#include "stm32l0xx_it.h"
#include "print_functions.h"
//#include "microphone.h"

// This function must be supplied externally:
extern void errorHandler(const char * func, const uint32_t line, const char * file);
volatile bool DataReady = false;

////////////////////////////////////////////////

// Constants
#define EIGHTH_BUFLEN FFT_N
#define HALF_BUFLEN (EIGHTH_BUFLEN*4)
#define FULL_BUFLEN (HALF_BUFLEN*2)
#define BIT_ROUNDING_MARGIN 4
#define FFT_SCALE_BITSHIFT 3
#define Q31_BITSHIFT 31

// State variables:
volatile bool micEnabled = false;
static volatile bool SPLcalcEnabled = false;
static volatile bool DMAinterruptEnabled = false;
static volatile bool SPLcalcComplete = false;
static volatile uint32_t amplitudeSettlingPeriods = 0;

// Derived data
static volatile uint32_t maximumAmplitude = 0;
static volatile int32_t SPL_int = 0, SPL_frac_1dp = 0;
static volatile int32_t bandSPL_int[SOUND_FREQ_BANDS] = {0};
static volatile int32_t bandSPL_frac_1dp[SOUND_FREQ_BANDS] = {0};

// Memory buffers
static volatile uint16_t dmaBuffer[FULL_BUFLEN] = {0};
static volatile int32_t dataBuffer[EIGHTH_BUFLEN] = {0};

// Handles for peripherals
static TIM_HandleTypeDef * htim6;
static I2S_HandleTypeDef * hi2s2;
static DMA_HandleTypeDef * hdma_spi2_rx;
static IRQn_Type DMA_Channel_IRQn;

// SPL state variables
static volatile int32_t spl_int_sum = 0;
static volatile int32_t spl_frac1dp_sum = 0;
static volatile int32_t band_spl_int_sum[SOUND_FREQ_BANDS] = {0};
static volatile int32_t band_spl_frac1dp_sum[SOUND_FREQ_BANDS] = {0};
static volatile uint32_t spl_sum_count = 0;

//////////////////////////////////////////////////////////////////////////////

static bool startMicSettlingPeriod(void);
static void processHalfDMAbuffer(uint32_t halfBufferStart);
static void calculateSPLQ31(void);
bool micSettlingComplete(void);
static void resetSPLstate(void);
static uint32_t getFilteredMaxAmplitudeQ31(const int32_t * data,
                                           const uint32_t length,
                                           bool reset, bool updateMaxAmpFollower);

//////////////////////////////////////////////////////////////////////////////

// Obtain the output SoundData, during a brief period of disabled DMA interrupt.
// Note that disabling the interrupt prevents the possibility of corrupted data
// but does not (under non-error conditions) cause loss of sound data because the
// DMA buffer is still being filled with I2S data.
// Return false if no data available.
bool getSoundData(SoundData_t * data, bool getSPLdata, bool getMaxAmpData)
{
//	print("micEnabled:  %d, SPLcalcComplete: %d\r\n", micEnabled, SPLcalcComplete);
  if ((!micEnabled) || (!SPLcalcComplete))
    {
        return false;
    }
//	Info("getSoundData: DMAinterruptEnabled: %d\r\n", DMAinterruptEnabled);
    if (DMAinterruptEnabled)
    {
        NVIC_DisableIRQ(DMA_Channel_IRQn);
    }
    // Use memory barrier instructions here, in case DMA interrupt had already
    // been triggered and would execute in the next few cycles.
    // Note: __DMB is not needed.
    __DSB();
    __ISB();
    // At this point, we know that no DMA ISR is in progress and that it will
    // not trigger until re-enabled.

    if (getSPLdata)
    {
        if (spl_sum_count == 0)
        {
            // No data: prevent divide by zero
            data->SPL_dBA_int = 0;
            data->SPL_dBA_fr_1dp = 0;
            for (uint32_t i = 0; i < SOUND_FREQ_BANDS; i++)
            {
                data->SPL_bands_dB_int[i] = 0;
                data->SPL_bands_dB_fr_1dp[i] = 0;
            }
        }
        else
        {
            sumToIntAverage(&(data->SPL_dBA_int), &(data->SPL_dBA_fr_1dp),
                            spl_int_sum, spl_frac1dp_sum, spl_sum_count);

            for (uint32_t i = 0; i < SOUND_FREQ_BANDS; i++)
            {
                sumToIntAverage(&(data->SPL_bands_dB_int[i]),
                                &(data->SPL_bands_dB_fr_1dp[i]), band_spl_int_sum[i],
                                band_spl_frac1dp_sum[i], spl_sum_count);
            }
        }
    }

    if (getMaxAmpData)
    {
        uint16_t intPart = 0;
        uint8_t fracPart = 0;
        amplitudeDN_to_mPa(maximumAmplitude, ik_mPa, &intPart, &fracPart);
        data->peak_amp_mPa_int = intPart;
        data->peak_amp_mPa_fr_2dp = fracPart;
    }

    data->stable = micSettlingComplete();

    if (DMAinterruptEnabled)
    {
        NVIC_EnableIRQ(DMA_Channel_IRQn);
    }
    // NOTE that any pending DMA interrupt will now fire, but will
    // take ~2 cycles to start
    return true;
}

// Initialize hardware for reading out the microphone: DMA, Timer, I2S.
// Obtain the handles to the peripherals and return bool success.
//bool soundInit(void (*DMAInit)(DMA_HandleTypeDef **),
//               bool (*I2SInit)(I2S_HandleTypeDef **),
//               bool (*tmrInit)(TIM_HandleTypeDef **), IRQn_Type DMAChIRQn)
bool soundInit(DMA_HandleTypeDef* h_hdma_spi2_rx,
               I2S_HandleTypeDef* h_hi2s2,
               TIM_HandleTypeDef* h_htim6,
               IRQn_Type DMAChIRQn)
{
    hi2s2 = h_hi2s2;
    htim6 = h_htim6;
    hdma_spi2_rx = h_hdma_spi2_rx;
    DMA_Channel_IRQn = DMA_Channel_IRQn;

    return true;
}

// Call this from external code to clear the maximum amplitude value.
void clearMaximumAmplitude(void)
{
    maximumAmplitude = 0;
}

// Prepare a one-shot timer to indicate the short time period during which the
// microphone output is inaccurate after power-on (warmup/settling time).
// This is output with the data for advice only: all functions still operate as
// normal during this period.
static bool startMicSettlingPeriod(void)
{
//  Debug("TMR6 started\r\n");
//  if (htim6 == NULL) {
//    print("htim6 == NULL");
//  }
  __HAL_TIM_SetCounter(htim6, 0);
    if (HAL_TIM_Base_Start(htim6) != HAL_OK)
    {
        return false;
    }
    return true;
}

// See whether the warmup/settling time has finished
bool micSettlingComplete(void)
{
//   print("Checking micSettlingComplete\r\n");
    bool complete = __HAL_TIM_GET_FLAG(htim6, TIM_SR_UIF);
    if (complete)
    {
//      Debug("TMR6 expired\r\n");
      HAL_TIM_Base_Stop(htim6);
      DataReady = true;
//      Info("micSettlingComplete set DataReady to true");
    }
    return complete;
}

// Enable: starts the I2S clock, warmup timer, and DMA interrupts
// Disable: stops the DMA interrupts and stops I2S clock.
// Return false on failure.
bool enableMicrophone(bool bEnable)
{
    if (bEnable == micEnabled)
    {
        return true;
    }
    if (bEnable)
    {
        startMicSettlingPeriod();
        if (HAL_I2S_Receive_DMA(hi2s2, (uint16_t *) dmaBuffer, HALF_BUFLEN) != HAL_OK)
        {
            return false;
        }
        clearMaximumAmplitude();
        amplitudeSettlingPeriods = 0;
        NVIC_EnableIRQ(DMA_Channel_IRQn);
        DMAinterruptEnabled = true;
        micEnabled = true;
        SPLcalcEnabled = false;
        SPLcalcComplete = false;
    }
    else
    {
        NVIC_DisableIRQ(DMA_Channel_IRQn);
        DMAinterruptEnabled = false;
        SPLcalcEnabled = false;
        SPLcalcComplete = false;
        if (HAL_I2S_DMAStop(hi2s2) != HAL_OK)
        {
            return false;
        }
        micEnabled = false;
    }
    return true;
}

// The microphone/I2S/DMA is already running: start the
// conversion of I2S data to SPL.
// Return false if microphone is not enabled (fail).
bool startSPLcalculation(void)
{
    if (!micEnabled)
    {
        return false;
    }
    if (SPLcalcEnabled)
    {
        return true;
    }
    resetSPLstate();
    SPLcalcEnabled = true;
    return true;
}

// Called from the DMA ISR when the first half of the DMA buffer is full,
// i.e. "HALF_BUFLEN" uint16s are in the first half of dmaBuffer
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s2loc)
{
  if (hi2s2loc == hi2s2) {
    UNUSED(hi2s2);
    processHalfDMAbuffer(0);
  }
}

// Called from the DMA ISR when the second half of the DMA buffer is full,
// i.e. "HALF_BUFLEN" uint16s are in the second half of dmaBuffer
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s2loc)
{
  if (hi2s2loc == hi2s2) {
    UNUSED(hi2s2);
    processHalfDMAbuffer(HALF_BUFLEN);
  }
}

static void processHalfDMAbuffer(uint32_t halfBufferStart)
{
    // Decode the raw I2S data and copy it out of the DMA buffer and into dataBuffer
    decodeI2SdataLch((uint16_t *) &(dmaBuffer[halfBufferStart]), HALF_BUFLEN,
                     (int32_t *) dataBuffer);
    // Filter the amplitude, find the maximum, and update maximumAmplitude:
    getFilteredMaxAmplitudeQ31((int32_t *) dataBuffer, (uint32_t) EIGHTH_BUFLEN,
                               amplitudeSettlingPeriods == 0,
                               amplitudeSettlingPeriods >= N_AMP_SETTLE_HALF_PERIODS);
    if (amplitudeSettlingPeriods < N_AMP_SETTLE_HALF_PERIODS)
    {
        // Need to allow the IIR filter to settle
        amplitudeSettlingPeriods++;
    }
    if (SPLcalcEnabled)
    {
        // Calculate the A-weighted SPL and octave bands SPL
        calculateSPLQ31();
    }
}

void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s2loc)
{
  if (hi2s2loc == hi2s2) {
    UNUSED(hi2s2);
    errorHandler(__func__, __LINE__, __FILE__);
  }
}

// Calculate A-weighted SPL and frequency-band SPL from input data.
// dataBuffer must contain (at least) FFT_N values and is reused for
// storage throughout this function. Since dataBuffer is shared by
// both halves of the DMA buffer, this function must complete before
// the next DMA interrupt.
static void calculateSPLQ31(void)
{
    // Interleaved complex, so need 2x number of elements:
    static q31_t FFTdata[2*FFT_N] = {0};

    // Find max, min values of the input data
    int32_t max, min;
    findMinMax(&min, &max, (int32_t *) dataBuffer, FFT_N);

    // Calculate the centre of the signal range, and the largest bitshift needed
    // to fill the available range without saturating
    int32_t centre = (min/2) + (max/2);
    uint32_t amplitude = (uint32_t) (max - centre + BIT_ROUNDING_MARGIN);
    uint32_t bitShift = getPo2factor(INT32_MAX, amplitude);

    // Apply offset and bitshift and put data into FFT input array
    uint32_t count = 0;
    for (uint32_t i = 0; i < FFT_N; i++)
    {
        FFTdata[count] = (q31_t) ((dataBuffer[i] - centre) << bitShift);
        FFTdata[count + 1] = 0;
        count += 2;
    }

    // Do the FFT; the output is internally divided by FFT_N (number of points)
    arm_cfft_q31(fftInstance, FFTdata, 0, 1);

    // Find FFT output max, min values (in 1st half of output),
    // ignoring the two dc bin values:
    findMinMax(&min, &max, &(FFTdata[2]), ((uint32_t) FFT_N) - 2);

    // find the largest absolute real/imag component (store in "max")
    if (min == INT32_MIN)
    {
        min = INT32_MAX;
    }
    if (max == INT32_MIN)
    {
        max = INT32_MAX;
    }
    min = abs(min);
    max = abs(max);
    if (min > max)
    {
        max = min;
    }
    // Calculate the largest bitshift needed to fill the available range
    // without saturating
    uint32_t amplitude2 = ((uint32_t) max) + BIT_ROUNDING_MARGIN;
    uint32_t bitShift2 = getPo2factor((uint32_t) INT32_MAX, amplitude2);

    // Apply the bitshift (not to the dc bins, and to 1st half of data only),
    // then get the absolute square magnitude of each bin
    for (uint32_t i = 2; i<FFT_N; i++)
    {
        FFTdata[i] = (q31_t) (FFTdata[i] << bitShift2);
    }
    // Re-use dataBuffer as working memory:
    q31_t * sqmag = (q31_t *) dataBuffer;
    arm_cmplx_mag_squared_q31(FFTdata, sqmag, FFT_N/2);

    // Apply the A-weighting and sum, excluding the dc bin.
    // Also sum for the unweighted frequency-band SPL:
    uint64_t bandSum[SOUND_FREQ_BANDS] = {0};
    uint64_t sumSq = 0; // sum of squared weighted magnitudes (scaled)
    for (uint32_t i = 1; i < (FFT_N/2); i++)
    {
        sumSq += ((uint64_t) sqmag[i])*((uint64_t) sqWsc[i]);
        if (bandIDs[i] != SOUND_FREQ_BANDS)
        {
            // This bin belongs in one of the frequency-bands:
            bandSum[bandIDs[i]] += (uint64_t) sqmag[i];
        }
    }

    // Reverse the (explicit and implicit) scalings using a bitshift.
    // Shifts applied before squaring are doubled when reversed.
    int32_t bs_right = ((int32_t) (2*bitShift)) + ((int32_t) (2*bitShift2))
                       - FFT_SCALE_BITSHIFT - Q31_BITSHIFT;
    uint32_t absShift = (uint32_t) abs(bs_right);
    if (bs_right < 0)
    {
        // Left shift
        sumSq = sumSq << absShift;
        for (uint32_t i = 0; i < SOUND_FREQ_BANDS; i++)
        {
            bandSum[i] = bandSum[i] << absShift;
        }
    }
    else
    {
        // Right shift
        sumSq = sumSq >> absShift;
        for (uint32_t i = 0; i < SOUND_FREQ_BANDS; i++)
        {
            bandSum[i] = bandSum[i] >> absShift;
        }
    }

    // Add on the dB terms accounting for the microphone parameters
    // and (only for the A-weighted SPL) the weighting scale factor
    scaleSPL(sumSq, dBscale_int, dBscale_frac, *tenlog10SF_int, *tenlog10SF_frac,
             (int32_t *) &SPL_int, (int32_t *) &SPL_frac_1dp);
    for (uint32_t i=0; i<SOUND_FREQ_BANDS; i++)
    {
        scaleSPL(bandSum[i], dBscale_int, dBscale_frac, 0, 0,
                 (int32_t *) &(bandSPL_int[i]), (int32_t *) &(bandSPL_frac_1dp[i]));
    }

    spl_int_sum += SPL_int;
    spl_frac1dp_sum += SPL_frac_1dp;

    for (uint32_t i = 0; i < SOUND_FREQ_BANDS; i++)
    {
        band_spl_int_sum[i] += bandSPL_int[i];
        band_spl_frac1dp_sum[i] += bandSPL_frac_1dp[i];
    }

    spl_sum_count++;
    if (spl_sum_count >= FILTER_SPL_N)
    {
        SPLcalcComplete = true;
        SPLcalcEnabled = false;
    }
}

static void resetSPLstate(void)
{
    spl_int_sum = 0;
    spl_frac1dp_sum = 0;
    spl_sum_count = 0;
    for (uint32_t i=0; i<SOUND_FREQ_BANDS; i++)
    {
        band_spl_int_sum[i] = 0;
        band_spl_frac1dp_sum[i] = 0;
    }
    SPLcalcComplete = false;
}

// Find and return the largest absolute amplitude in the input data buffer.
// Optionally also update the global maximum amplitude value.
// Uses a simple single-pole hi-pass IIR filter to remove the input dc offset.
// Uses Q31 operations.
static uint32_t getFilteredMaxAmplitudeQ31(const int32_t * data,
                                           const uint32_t length, bool reset,
                                           bool updateMaxAmpFollower)
{
    static q31_t filtered = 0;
    static q31_t lastData = 0;

    if (reset)
    {
        // Reset the state of the digital filter,
        // e.g. if the mic has been disabled then re-enabled.
        filtered = 0;
        lastData = 0;
    }
    q31_t maxAmp = 0;
    q31_t minAmp = 0;

    // Apply a bitshift to the incoming data, before filtering, to maximise the
    // dynamic range but while also ensuring the intermediate value cannot
    // overflow (three Q31 values are added together).
    const uint32_t scalingBitShift = 5;
    for (uint32_t i = 0; i < length; i++)
    {
        q31_t fx = (q31_t) (data[i] << scalingBitShift);

        // Arm saturating operations:
        // D = A*B is: arm_mult_q31(&A, &B, &D, 1);
        // D = A+B is: arm_add_q31(&A, &B, &D, 1);

        // Now do the filter calculation:
        q31_t r1, r2, r3;
        lastData = -lastData;
        arm_add_q31(&fx, &lastData, &r1, 1); // r1 = fx - lastData
        arm_mult_q31((q31_t *) &a0, &r1, &r2, 1);      // r2 = a0*r1
        arm_mult_q31((q31_t *) &b, &filtered, &r3, 1); // r3 = b*filtered
        arm_add_q31(&r2, &r3, &filtered, 1); // filtered = r2 + r3

        lastData = fx;
        if (filtered > maxAmp)
        {
            maxAmp = filtered;
        }
        else if (filtered < minAmp)
        {
            minAmp = filtered;
        }
    }
    // Find the maximum absolute amplitude from the signed values:
    uint32_t absMin = abs(minAmp);
    uint32_t absMax = (uint32_t) maxAmp;
    uint32_t absMaxAmp = (absMin > absMax) ? absMin : absMax;

    // Reverse the scaling bitshift
    uint32_t absMaxAmp32 = (uint32_t) (absMaxAmp >> scalingBitShift);

    if (updateMaxAmpFollower && (absMaxAmp32 > maximumAmplitude))
    {
        maximumAmplitude = absMaxAmp32;
    }
    return absMaxAmp32;
}
