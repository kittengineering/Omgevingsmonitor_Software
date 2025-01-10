// Functions and constants for calculating 10*log10(P) via an
// efficient algorithm using integers.

#ifndef EFFICIENT_10LOG10_H
#define EFFICIENT_10LOG10_H

#include <stdint.h>

void efficient10log10(uint64_t P, int32_t * integerPart, int32_t * fractionalPart);
void correctIntFracNumber(int32_t * intPart, int32_t * fracPart);

#endif
