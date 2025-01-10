#ifndef EEPROM_H
#define EEPROM_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_uart.h"
#include "stm32l0xx_hal_flash_ex.h"

#define EEPROM_START 0x08080000
#define EEPROM_END 0x080817FF

#define EEPROM_SIZE (EEPROM_END - EEPROM_START) + 1

uint32_t WriteUint8ArrayEeprom(uint32_t startAddr, uint8_t data[], uint16_t size);
void WriteUint8ArrayEepromSafe(uint32_t startAddr, uint8_t data[], uint16_t size, uint16_t maxSize);
void ReadUint8ArrayEEprom(uint32_t startAddr, uint8_t data[], uint16_t size);
void ClearEEprom(uint32_t startAddr, uint16_t size);

#endif
