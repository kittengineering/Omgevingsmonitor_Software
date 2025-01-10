// Constants for a specific microphone, which define its response to sound.
// This assumes that it is a perfect microphone with constant
// and frequency-independent sensitivity.

#ifndef MICROPHONE_CONSTANTS_H
#define MICROPHONE_CONSTANTS_H

// Initial period of time after power-on, during which the
// microphone output should be considered inaccurate.
#define MIC_SETTLING_PERIOD_MS 1500

/* Conversion of microphone digital output to sound pressure.
   This depends on the microphone sensitivity (S) and the
   output data bitdepth (N).
      pressure/mPa = (digital amplitude)*ik_mPa;
      ik_mPa = sqrt(2)/((10^((S/dB)/20))*((2^(N-1))-1))
   e.g. If S = -26 dB and N = 24, then: ik_mPa = 3.3638e-3
*/
static const float ik_mPa = 3.3638e-3f;

/* Decibel scale factor 'dBscale' is constant for a given microphone:
      dBscale = 20*log10((ik_mPa/1000)/(20e-6))
   e.g. if S = -26dB and N = 24; dBscale = -15.5 (to 1.d.p.)
*/
static const int32_t dBscale_int = -15;
static const int32_t dBscale_frac = -5;

#endif
