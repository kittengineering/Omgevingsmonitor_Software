################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32L0538-Discovery/font12epd.c \
../Drivers/BSP/STM32L0538-Discovery/font16epd.c \
../Drivers/BSP/STM32L0538-Discovery/font20epd.c \
../Drivers/BSP/STM32L0538-Discovery/font8epd.c \
../Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.c \
../Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.c 

OBJS += \
./Drivers/BSP/STM32L0538-Discovery/font12epd.o \
./Drivers/BSP/STM32L0538-Discovery/font16epd.o \
./Drivers/BSP/STM32L0538-Discovery/font20epd.o \
./Drivers/BSP/STM32L0538-Discovery/font8epd.o \
./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.o \
./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.o 

C_DEPS += \
./Drivers/BSP/STM32L0538-Discovery/font12epd.d \
./Drivers/BSP/STM32L0538-Discovery/font16epd.d \
./Drivers/BSP/STM32L0538-Discovery/font20epd.d \
./Drivers/BSP/STM32L0538-Discovery/font8epd.d \
./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.d \
./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32L0538-Discovery/%.o Drivers/BSP/STM32L0538-Discovery/%.su Drivers/BSP/STM32L0538-Discovery/%.cyclo: ../Drivers/BSP/STM32L0538-Discovery/%.c Drivers/BSP/STM32L0538-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/MJSGadget/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32L0538-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32L0538-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32L0538-Discovery/font12epd.cyclo ./Drivers/BSP/STM32L0538-Discovery/font12epd.d ./Drivers/BSP/STM32L0538-Discovery/font12epd.o ./Drivers/BSP/STM32L0538-Discovery/font12epd.su ./Drivers/BSP/STM32L0538-Discovery/font16epd.cyclo ./Drivers/BSP/STM32L0538-Discovery/font16epd.d ./Drivers/BSP/STM32L0538-Discovery/font16epd.o ./Drivers/BSP/STM32L0538-Discovery/font16epd.su ./Drivers/BSP/STM32L0538-Discovery/font20epd.cyclo ./Drivers/BSP/STM32L0538-Discovery/font20epd.d ./Drivers/BSP/STM32L0538-Discovery/font20epd.o ./Drivers/BSP/STM32L0538-Discovery/font20epd.su ./Drivers/BSP/STM32L0538-Discovery/font8epd.cyclo ./Drivers/BSP/STM32L0538-Discovery/font8epd.d ./Drivers/BSP/STM32L0538-Discovery/font8epd.o ./Drivers/BSP/STM32L0538-Discovery/font8epd.su ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.cyclo ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.d ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.o ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery.su ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.cyclo ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.d ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.o ./Drivers/BSP/STM32L0538-Discovery/stm32l0538_discovery_epd.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32L0538-2d-Discovery

