#include "../Inc/EEProm.h"

uint32_t WriteUint8ArrayEeprom(uint32_t startAddr, uint8_t data[], uint16_t size)
{
    static uint32_t addr;
    addr = startAddr;
    HAL_FLASHEx_DATAEEPROM_Unlock();
    for (uint16_t i = 0; i < size; i++)
    {
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, addr, data[i]);
        addr++;
    }
    HAL_FLASHEx_DATAEEPROM_Lock();
    return addr;
}

void WriteUint8ArrayEepromSafe(uint32_t startAddr, uint8_t data[], uint16_t size, uint16_t maxSize)
{
    if (size <= maxSize)
    {
        WriteUint8ArrayEeprom(startAddr, data, size);
    }
}

void ReadUint8ArrayEEprom(uint32_t startAddr, uint8_t data[], uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        data[i] = *(uint8_t*)(startAddr + i);
    }
}

void ClearEEprom(uint32_t startAddr, uint16_t size)
{
    HAL_FLASHEx_DATAEEPROM_Unlock();
    for (uint16_t i = 0; i < size; i+=4)
    {
        HAL_FLASHEx_DATAEEPROM_Erase(startAddr+i);
    }
    HAL_FLASHEx_DATAEEPROM_Lock();
}
