#ifndef PC_CONFIG_H
#define PC_CONFIG_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_uart.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#define MAX_PAYLOAD_SIZE 256
#define HEADER_SIZE 3
#define CRC_SIZE 2
#define TOTAL_BUFFER_SIZE (MAX_PAYLOAD_SIZE + HEADER_SIZE + CRC_SIZE)

#define ERROR_CMD 255

#define PREABMLE "#"

#define BoxConfigCmd 0
#define TempConfigCmd 1
#define HumidConfigCmd 2
#define VocRawConfigCmd 3
#define VocIndexConfigCmd 4
#define dBaConfigCmd 5
#define dBcConfigCmd 6
#define PM2ConfigCmd 7
#define PM10ConfigCmd 8
#define BatVoltConfigCmd 9
#define SolVoltConfigCmd 10
#define ChargerStatConfigCmd 11
#define CustomNameConfigCmd 12
#define ClearConfigCmd 253
#define ClearEepromCmd 254
#define ErrorCmd 255

typedef struct
{
    uint8_t     Command;
    uint8_t     PayloadLength;
    uint8_t     Payload[MAX_PAYLOAD_SIZE];
    uint16_t    Crc;
} Receive_MSG;

void Process_PC_Config(uint8_t* data);//, uint16_t length);
void Create_Message(uint8_t command, uint8_t payload[], uint8_t payloadLength);
void printf_USB(const char* message, ...);

#endif