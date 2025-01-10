// Constants used for calculating sound pressure levels (SPL), including A-weighting.

#ifndef SOUND_LUTS_H
#define SOUND_LUTS_H

#include <stdint.h>

/* The constants defined in this file are:
 - sound_band_edges_Hz, sound_band_mids_Hz = Define the frequency bands for sound
   level measurement.
 - sqWsc_FsX_Y[] = scaled, squared A-weightings (scaled to fit in uint16s).
   To reverse the scaling, multiply by the scaling factor "SF", which is provided
   in the form 10*log10(SF).
 - tenlog10SF_FsX_Y = the scaling factor for the above, supplied as a float and in
   integer, fractional form.
 - bandIDs_FsX_Y[] = gives the octave band index number from 0 to (SOUND_FREQ_BANDS-1)
   or a value of SOUND_FREQ_BANDS to indicate not in any band. Length = Y/2.
   Where X = actual audio sample frequency in Hz and Y = FFT length.
   The constants are supplied for 9 combinations of X and Y.
*/

#define SOUND_FREQ_BANDS 6

extern const uint16_t sound_band_mids_Hz[];
extern const uint16_t sound_band_edges_Hz[];

extern const float tenlog10SF_Fs31250_1024;
extern const int32_t tenlog10SF_int_Fs31250_1024;
extern const int32_t tenlog10SF_frac_Fs31250_1024;
extern const uint16_t sqWsc_Fs31250_1024[];
extern const uint8_t bandIDs_Fs31250_1024[];

extern const float tenlog10SF_Fs31250_512;
extern const int32_t tenlog10SF_int_Fs31250_512;
extern const int32_t tenlog10SF_frac_Fs31250_512;
extern const uint16_t sqWsc_Fs31250_512[];
extern const uint8_t bandIDs_Fs31250_512[];

extern const float tenlog10SF_Fs31250_256;
extern const int32_t tenlog10SF_int_Fs31250_256;
extern const int32_t tenlog10SF_frac_Fs31250_256;
extern const uint16_t sqWsc_Fs31250_256[];
extern const uint8_t bandIDs_Fs31250_256[];

extern const float tenlog10SF_Fs31250_128;
extern const int32_t tenlog10SF_int_Fs31250_128;
extern const int32_t tenlog10SF_frac_Fs31250_128;
extern const uint16_t sqWsc_Fs31250_128[];
extern const uint8_t bandIDs_Fs31250_128[];

extern const float tenlog10SF_Fs15625_128;
extern const int32_t tenlog10SF_int_Fs15625_128;
extern const int32_t tenlog10SF_frac_Fs15625_128;
extern const uint16_t sqWsc_Fs15625_128[];
extern const uint8_t bandIDs_Fs15625_128[];

extern const float tenlog10SF_Fs15625_256;
extern const int32_t tenlog10SF_int_Fs15625_256;
extern const int32_t tenlog10SF_frac_Fs15625_256;
extern const uint16_t sqWsc_Fs15625_256[];
extern const uint8_t bandIDs_Fs15625_256[];

extern const float tenlog10SF_Fs15625_512;
extern const int32_t tenlog10SF_int_Fs15625_512;
extern const int32_t tenlog10SF_frac_Fs15625_512;
extern const uint16_t sqWsc_Fs15625_512[];
extern const uint8_t bandIDs_Fs15625_512[];

extern const float tenlog10SF_Fs50000_256;
extern const int32_t tenlog10SF_int_Fs50000_256;
extern const int32_t tenlog10SF_frac_Fs50000_256;
extern const uint16_t sqWsc_Fs50000_256[];
extern const uint8_t bandIDs_Fs50000_256[];

extern const float tenlog10SF_Fs50000_512;
extern const int32_t tenlog10SF_int_Fs50000_512;
extern const int32_t tenlog10SF_frac_Fs50000_512;
extern const uint16_t sqWsc_Fs50000_512[];
extern const uint8_t bandIDs_Fs50000_512[];

#endif
