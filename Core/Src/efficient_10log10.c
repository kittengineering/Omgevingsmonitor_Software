// Functions and constants for calculating 10*log10(P) via an
// efficient algorithm using integers.

#include "efficient_10log10.h"

// Lookup table (LUT) and constant data
#define LUT_10LOG10_LENGTH 128
static const uint32_t mantissa_kBits = 8;
static const uint16_t TLT2_intPart = 3;
static const uint16_t TLT2_shiftedFracPart = 1;
static const uint32_t TLT2_bitshift = 3;
static const uint32_t intOffset10log10 = 21;
static const uint32_t fracPartLSBs = 6;
static const uint8_t LUT10log10[LUT_10LOG10_LENGTH] = {1, 1, 2, 2, 2, 3, 3, 3, 4,
4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 10, 64, 64, 65, 65,
65, 65, 66, 66, 66, 66, 67, 67, 67, 67, 68, 68, 68, 68, 69, 69, 69, 69, 70,
70, 70, 70, 71, 71, 71, 71, 72, 72, 72, 72, 72, 73, 73, 73, 73, 74, 74, 74,
128, 128, 129, 129, 129, 129, 129, 130, 130, 130, 130, 131, 131, 131, 131, 131,
132, 132, 132, 132, 132, 133, 133, 133, 133, 133, 134, 134, 134, 134, 134, 134,
135, 135, 135, 135, 135, 136, 136, 136, 136, 136, 136, 137, 137, 137, 137, 137,
138, 138, 138, 192, 192, 192, 193, 193};


// Obtain the value from the lookup table (LUT) and convert it to
// integer and fractional parts:
static void accessLUT10log10(uint32_t index, uint32_t * intPart, uint32_t * fracPart)
{
    if (index >= LUT_10LOG10_LENGTH)
    {
        index = LUT_10LOG10_LENGTH - 1;
    }
    uint8_t x = LUT10log10[index];
    intPart[0] = (uint32_t) (x >> fracPartLSBs);
    fracPart[0] = ((uint32_t) x) - (intPart[0] << fracPartLSBs);
}


// Calculate 10*log10(P), returning the result as an integer part
// and a 1-decimal-place fractional part.
// i.e. result = integerPart + (fractionalPart/10);
void efficient10log10(uint64_t P, int32_t * integerPart, int32_t * fractionalPart)
{
    // NOTE: the CLZ (count leading zeros) instruction is not available on M0/M0+
    // so use a simple shifting algorithm:
    uint64_t limit = (((uint64_t) 1) << mantissa_kBits) - 1; // limit = ((2^kBits)-1)
    // Bit-shift P downwards until the remaining mantissa is a
    // "mantissa_kBits" length value
    uint16_t bShift = 0;
    while (P > limit)
    {
        P = P >> 1;
        bShift++;
    }
    // Calculate the index to the LUT:
    uint32_t ind = ((uint32_t) P) - (((uint32_t) 1) << (mantissa_kBits-1));
    // Do the lookup:
    uint32_t lutIntPart = 0;
    uint32_t lutFracPart = 0;
    accessLUT10log10(ind, &lutIntPart, &lutFracPart);
    // Provide the result as an integer and fractional part
    // (with the fractional part x10)
    int32_t intPart = (int32_t) (intOffset10log10 + lutIntPart
                        + (bShift * TLT2_intPart));
    int32_t fracPart = (int32_t) (lutFracPart
                        + ((bShift * TLT2_shiftedFracPart) >> TLT2_bitshift));
    // Make a correction if fractional part is not in range 0->9:
    correctIntFracNumber(&intPart, &fracPart);
    integerPart[0] = intPart;
    fractionalPart[0] = fracPart;
}


// After doing a sum of (+ve or -ve) numbers represented as integer and
// 1-decimal-place fractional parts, correct the result if the fractional
// part has grown to be larger than 9.
// Valid numbers have same sign of both int and frac parts
// (or one/both parts zero) AND |fracPart| < 10
void correctIntFracNumber(int32_t * intPart, int32_t * fracPart)
{
    while (fracPart[0] >= 10)
    {
        intPart[0] = intPart[0] + 1;
        fracPart[0] = fracPart[0] - 10;
    }
    while (fracPart[0] <= -10)
    {
        intPart[0] = intPart[0] - 1;
        fracPart[0] = fracPart[0] + 10;
    }
    // now correct cases where signs are not consistent:
    if ((intPart[0] < 0) && (fracPart[0] > 0))
    {
        intPart[0] = intPart[0] + 1;
        fracPart[0] = fracPart[0] - 10;
    }
    else if ((intPart[0] > 0) && (fracPart[0] < 0))
    {
        intPart[0] = intPart[0] - 1;
        fracPart[0] = fracPart[0] + 10;
    }
}

