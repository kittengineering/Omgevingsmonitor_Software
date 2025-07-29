// Select which of the lookup tables (LUTs) is required, based
// on the choice of sample frequency and FFT size.

#include "stm32l0xx_hal.h"
#include "arm_math.h"
#include "microphone.h"
#include "sound_LUTs.h"

// Define the exact I2S frequency
#if (I2S_AUDIOFREQ == I2S_AUDIOFREQ_16K)
    #define I2S_FREQ 15625
#elif (I2S_AUDIOFREQ == I2S_AUDIOFREQ_32K)
    #define I2S_FREQ 31250
#elif (I2S_AUDIOFREQ == I2S_AUDIOFREQ_48K)
    #define I2S_FREQ 50000
#else
    #error "Unknown I2S AUDIO FREQ"
#endif

// Find the time period for the settling of the amplitude filter, as
// a multiple of the half-DMA buffer fill time.
#if (I2S_FREQ == 31250)
    #if (FFT_N == 256)
        #define N_AMP_SETTLE_HALF_PERIODS 10
    #elif (FFT_N == 512)
        #define N_AMP_SETTLE_HALF_PERIODS 5
    #elif (FFT_N == 1024)
        #define N_AMP_SETTLE_HALF_PERIODS 3
    #else
        #error("N-points and/or Fs not implemented yet")
    #endif
#elif (I2S_FREQ == 15625)
    #if (FFT_N == 128)
        #define N_AMP_SETTLE_HALF_PERIODS 10
    #elif (FFT_N == 256)
        #define N_AMP_SETTLE_HALF_PERIODS 5
    #elif (FFT_N == 512)
        #define N_AMP_SETTLE_HALF_PERIODS 3
    #else
        #error("N-points and/or Fs not implemented yet")
    #endif
#else
    #error("N-points and/or Fs not implemented yet")
#endif


#if (I2S_FREQ == 50000)
    #if (FFT_N == 256)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len256;
        const uint16_t * sqWsc = sqWsc_Fs50000_256;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs50000_256;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs50000_256;
        const uint8_t * bandIDs = bandIDs_Fs50000_256;
    #elif (FFT_N == 512)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len512;
        const uint16_t * sqWsc = sqWsc_Fs50000_512;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs50000_512;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs50000_512;
        const uint8_t * bandIDs = bandIDs_Fs50000_512;
    #else
        #error("N-points and/or Fs not implemented yet")
    #endif
#elif (I2S_FREQ == 31250)
    #if (FFT_N == 128)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len128;
        const uint16_t * sqWsc = sqWsc_Fs31250_128;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs31250_128;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs31250_128;
        const uint8_t * bandIDs = bandIDs_Fs31250_128;
    #elif (FFT_N == 256)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len256;
        const uint16_t * sqWsc = sqWsc_Fs31250_256;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs31250_256;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs31250_256;
        const uint8_t * bandIDs = bandIDs_Fs31250_256;
    #elif (FFT_N == 512)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len512;
        const uint16_t * sqWsc = sqWsc_Fs31250_512;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs31250_512;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs31250_512;
        const uint8_t * bandIDs = bandIDs_Fs31250_512;
    #elif (FFT_N == 1024)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len1024;
        const uint16_t * sqWsc = sqWsc_Fs31250_1024;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs31250_1024;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs31250_1024;
        const uint8_t * bandIDs = bandIDs_Fs31250_1024;
    #else
        #error("N-points and/or Fs not implemented yet")
    #endif
#elif (I2S_FREQ == 15625)
    #if (FFT_N == 128)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len128;
        const uint16_t * sqWsc = sqWsc_Fs15625_128;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs15625_128;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs15625_128;
        const uint8_t * bandIDs = bandIDs_Fs15625_128;
    #elif (FFT_N == 256)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len256;
        const uint16_t * sqWsc = sqWsc_Fs15625_256;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs15625_256;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs15625_256;
        const uint8_t * bandIDs = bandIDs_Fs15625_256;
    #elif (FFT_N == 512)
        const arm_cfft_instance_q31 * fftInstance = &arm_cfft_sR_q31_len512;
        const uint16_t * sqWsc = sqWsc_Fs15625_512;
        const int32_t * tenlog10SF_int = &tenlog10SF_int_Fs15625_512;
        const int32_t * tenlog10SF_frac = &tenlog10SF_frac_Fs15625_512;
        const uint8_t * bandIDs = bandIDs_Fs15625_512;
    #else
        #error("N-points and/or Fs not implemented yet")
    #endif
#else
    #error("N-points and/or Fs not implemented yet")
#endif

// Sound amplitude filter coefficients.
// Want a IIR filter with cutoff of fc = 10Hz.
// The coefficients depend on Fs according to:
//   b = exp(-2.pi.(1/Fs).fc)
//   a0 = (1+b)/2
//   a1 = -a0
// Then convert to Q31 by dividing by 2^-31 and then rounding.
// Also note that since a1 = -a0 the filter becomes:
//   F_new = (a0*(x_new - x_old)) + (b*F_old)
#if (I2S_AUDIOFREQ == I2S_AUDIOFREQ_16K)
    const q31_t a0 = 2143174546, b = 2138865443;
#elif (I2S_AUDIOFREQ == I2S_AUDIOFREQ_32K)
    const q31_t a0 = 2145326931, b = 2143170214;
#elif (I2S_AUDIOFREQ == I2S_AUDIOFREQ_48K)
    const q31_t a0 = 2146135192, b = 2144786735;
#else
    #error "Undefined I2S AUDIO FREQ"
#endif
