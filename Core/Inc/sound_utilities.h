// Calculation functions used for sound measurements.
// These are not specific to the microphone hardware or the CPU architecture.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>

void floatToIntAndFrac2dp(float positiveValue, uint32_t *intpart,
                          uint8_t *fracpart2dp);
void floatToIntAndFrac1dp(float positiveValue, uint32_t *intpart,
                          uint8_t *fracpart1dp);
void sumToIntAverage(uint8_t * intpart, uint8_t * fracpart1dp, const int32_t intSum,
                     const int32_t frac1dpSum, const uint32_t sumCount);
void findMinMax(int32_t * min, int32_t * max, const int32_t * array,
                const uint32_t length);
uint32_t getPo2factor(uint32_t bigVal, uint32_t smallVal);
void amplitudeDN_to_mPa(uint32_t ampDN, const float ik_mPa, uint16_t * intAmp_mPa,
                        uint8_t * frac2dpAmp_mPa);
void scaleSPL(uint64_t sumSq, const int32_t dBscale_int, const int32_t dBscale_frac,
              const int32_t weightingInt, const int32_t weightingFrac,
              int32_t * SPLintegerPart, int32_t * SPLfractionalPart);
void decodeI2SdataLch(const uint16_t * inBuf, const uint32_t inBufLength,
                      int32_t * outBuf);

#endif
