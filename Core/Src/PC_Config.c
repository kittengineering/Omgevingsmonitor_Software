#include "../Inc/PC_Config.h"
#include "../Inc/EEProm.h"
#include "../Inc/Config.h"

Receive_MSG received;

static uint16_t CRC16_ARC(uint8_t data[], uint16_t size);
void ProcessCmd(Receive_MSG msg);

//*************************************Preview Uart Config message**********************************
// #, Command, Payload lengte, Payload, MSB CRC16_ARC, LSB CRC16_ARC
// Command value:   0 = ...
//                  1 = ...
//**************************************************************************************************

void Process_PC_Config(uint8_t* data) //, uint16_t length)
{
    uint32_t length = GetUsbRxDataSize();
    if (length > 5)
    {
        uint8_t* message = (unsigned char*)strstr((const char*)data, PREABMLE);
        if(message != NULL)// && strlen((const char*)message) > 5)
        {
            received.Command = message[1];
            received.PayloadLength = message[2];
            if (length >= (uint32_t)(received.PayloadLength + HEADER_SIZE + CRC_SIZE))
            {
                memcpy(received.Payload, &message[3], received.PayloadLength);
                received.Crc = message[3 + received.PayloadLength] << 8 | message[3 + received.PayloadLength + 1];

                if (received.Crc != CRC16_ARC(message, received.PayloadLength + 3))
                {
                    Create_Message(ERROR, received.Payload, received.PayloadLength);
                    //Handel het foutief ontvangen bericht af
                }
                else
                {
                    //Handel het correct ontvangen bericht af
                    ProcessCmd(received);
                    Create_Message(received.Command, received.Payload, received.PayloadLength);
                }
                ResetUsbRxDataSize();
                return;
            }
            GetUsbRxNextChunk(length);
        }
        else
        {
            ResetUsbRxDataSize();
        }
    }
}

void ProcessCmd(Receive_MSG msg)
{
    switch (msg.Command)
    {
        case BoxConfigCmd:
            WriteUint8ArrayEeprom(BoxConfigAddr, msg.Payload, msg.PayloadLength);
        break;
        case TempConfigCmd:
            WriteUint8ArrayEeprom(TempConfigAddr, msg.Payload, msg.PayloadLength);
        break;
        case HumidConfigCmd:
            WriteUint8ArrayEeprom(HumidConfigAddr, msg.Payload, msg.PayloadLength);
        break;
        case VocRawConfigCmd:
            WriteUint8ArrayEeprom(VocRawConfigAddr, msg.Payload, msg.PayloadLength);
        break;
        case VocIndexConfigCmd:
            WriteUint8ArrayEeprom(VocIndexConfigAddr, msg.Payload, msg.PayloadLength);
        break;
        case dBaConfigCmd:
            WriteUint8ArrayEeprom(dBaConfigAddr, msg.Payload, msg.PayloadLength);
        break;
        case dBcConfigCmd:
            WriteUint8ArrayEeprom(dBcConfigAddr, msg.Payload, msg.PayloadLength);
        break;
    }
}

void Create_Message(uint8_t command, uint8_t *payload, uint8_t payloadLength)
{
    static uint8_t message[TOTAL_BUFFER_SIZE];
    message[0] = (uint8_t)PREABMLE[0];
    message[1] = command;
    message[2] = payloadLength;
    memcpy(&message[3], payload, payloadLength);
    uint16_t crcIndex = (HEADER_SIZE + payloadLength);
    uint16_t calculatedCRC = CRC16_ARC(message, crcIndex);
    message[crcIndex] = calculatedCRC >> 8;
    message[crcIndex + 1] = calculatedCRC & 0xFF;
    CDC_Transmit_FS((uint8_t*)message, (crcIndex + 2));
}

static uint16_t CRC16_ARC(uint8_t data[], uint16_t size)
{
    uint16_t crc = 0;

    for (int i = 0; i < size; i++)
    {
        crc ^= data[i];

        for (int j = 0; j < 8; j++)
        {
            if ((crc & 0x0001) != 0)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc; 
}

void printf_USB(const char* message, ...)
{
  char string[150];
  va_list args;
  va_start(args, message);
  vsprintf(string, message, args);
  va_end(args);

  CDC_Transmit_FS((uint8_t*)string, strlen(string));
}