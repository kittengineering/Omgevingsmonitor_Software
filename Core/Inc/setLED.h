#ifndef SET_LED_TEUN_H_
#define SET_LED_TEUN_H_

#include <stdint.h>
#include <stdbool.h>

#define LED_MAX_VALUE 4000
#define LED_FULL_ON 3000
#define LED_HALF_ON 3500
#define LED_OFF     4000

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
}LED;

void SetStatusLED_T(uint16_t red, uint16_t green, uint16_t blue);
void SetDBLED_T(bool red, bool green, bool blue);
void SetVocLED_T(uint16_t red, uint16_t green, uint16_t blue);
void ErrorBlinkWiFi();
void UpdateLEDs();

#endif