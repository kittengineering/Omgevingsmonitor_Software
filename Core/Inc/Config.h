#ifndef CONFIG_H
#define CONFIG_H

#define EEPromStartAddr 0x08080000

#define SSIDStartAddr 0x08080200
#define SSIDAddrMaxSize 32

#define PasswordStartAddr 0x08080220
#define PasswordAddrMaxSize 64

#define IdCount 13

#define IdSize 12

#define ConfigSize (IdCount*IdSize) + CustomNameMaxLength

#define BoxConfigAddr EEPromStartAddr + (IdSize * 0)
#define TempConfigAddr EEPromStartAddr + (IdSize * 1)
#define HumidConfigAddr EEPromStartAddr + (IdSize * 2)
#define NOxIndexConfigAddr EEPromStartAddr + (IdSize * 3)
#define VocIndexConfigAddr EEPromStartAddr + (IdSize * 4)
#define dBaConfigAddr EEPromStartAddr + (IdSize * 5)
#define dBAConfigAddr EEPromStartAddr + (IdSize * 6)
#define PM2ConfigAddr EEPromStartAddr + (IdSize * 7)
#define PM10ConfigAddr EEPromStartAddr + (IdSize * 8)
#define BatVoltConfigAddr EEPromStartAddr + (IdSize * 9)
#define SolVoltConfigAddr EEPromStartAddr + (IdSize * 10)
#define ChargerStatConfigAddr EEPromStartAddr + (IdSize * 11)
#define CustomNameConfigAddr EEPromStartAddr + (IdSize * 12)

#define CustomNameMaxLength 30

#endif
