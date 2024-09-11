################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Battery_utils.c \
../Core/Src/EEProm.c \
../Core/Src/ESP.c \
../Core/Src/I2CSensors.c \
../Core/Src/PC_Config.c \
../Core/Src/adc.c \
../Core/Src/dma.c \
../Core/Src/gadget.c \
../Core/Src/gasSensor.c \
../Core/Src/gpio.c \
../Core/Src/humidTemp.c \
../Core/Src/i2c.c \
../Core/Src/i2s.c \
../Core/Src/main.c \
../Core/Src/measurement.c \
../Core/Src/microphone.c \
../Core/Src/sensirion_gas_index_algorithm.c \
../Core/Src/sgp40.c \
../Core/Src/stm32l0xx_hal_msp.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l0xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c \
../Core/Src/utils.c \
../Core/Src/wsenHIDS.c 

OBJS += \
./Core/Src/Battery_utils.o \
./Core/Src/EEProm.o \
./Core/Src/ESP.o \
./Core/Src/I2CSensors.o \
./Core/Src/PC_Config.o \
./Core/Src/adc.o \
./Core/Src/dma.o \
./Core/Src/gadget.o \
./Core/Src/gasSensor.o \
./Core/Src/gpio.o \
./Core/Src/humidTemp.o \
./Core/Src/i2c.o \
./Core/Src/i2s.o \
./Core/Src/main.o \
./Core/Src/measurement.o \
./Core/Src/microphone.o \
./Core/Src/sensirion_gas_index_algorithm.o \
./Core/Src/sgp40.o \
./Core/Src/stm32l0xx_hal_msp.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l0xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o \
./Core/Src/utils.o \
./Core/Src/wsenHIDS.o 

C_DEPS += \
./Core/Src/Battery_utils.d \
./Core/Src/EEProm.d \
./Core/Src/ESP.d \
./Core/Src/I2CSensors.d \
./Core/Src/PC_Config.d \
./Core/Src/adc.d \
./Core/Src/dma.d \
./Core/Src/gadget.d \
./Core/Src/gasSensor.d \
./Core/Src/gpio.d \
./Core/Src/humidTemp.d \
./Core/Src/i2c.d \
./Core/Src/i2s.d \
./Core/Src/main.d \
./Core/Src/measurement.d \
./Core/Src/microphone.d \
./Core/Src/sensirion_gas_index_algorithm.d \
./Core/Src/sgp40.d \
./Core/Src/stm32l0xx_hal_msp.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l0xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/utils.d \
./Core/Src/wsenHIDS.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -DARM_MATH_CM0 -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -I"C:/Users/Danny/Documents/GitHub/MJSGadget/Drivers/CMSIS/DSP/Include" -I"C:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Lib" -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/Danny/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Battery_utils.cyclo ./Core/Src/Battery_utils.d ./Core/Src/Battery_utils.o ./Core/Src/Battery_utils.su ./Core/Src/EEProm.cyclo ./Core/Src/EEProm.d ./Core/Src/EEProm.o ./Core/Src/EEProm.su ./Core/Src/ESP.cyclo ./Core/Src/ESP.d ./Core/Src/ESP.o ./Core/Src/ESP.su ./Core/Src/I2CSensors.cyclo ./Core/Src/I2CSensors.d ./Core/Src/I2CSensors.o ./Core/Src/I2CSensors.su ./Core/Src/PC_Config.cyclo ./Core/Src/PC_Config.d ./Core/Src/PC_Config.o ./Core/Src/PC_Config.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gadget.cyclo ./Core/Src/gadget.d ./Core/Src/gadget.o ./Core/Src/gadget.su ./Core/Src/gasSensor.cyclo ./Core/Src/gasSensor.d ./Core/Src/gasSensor.o ./Core/Src/gasSensor.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/humidTemp.cyclo ./Core/Src/humidTemp.d ./Core/Src/humidTemp.o ./Core/Src/humidTemp.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/i2s.cyclo ./Core/Src/i2s.d ./Core/Src/i2s.o ./Core/Src/i2s.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/measurement.cyclo ./Core/Src/measurement.d ./Core/Src/measurement.o ./Core/Src/measurement.su ./Core/Src/microphone.cyclo ./Core/Src/microphone.d ./Core/Src/microphone.o ./Core/Src/microphone.su ./Core/Src/sensirion_gas_index_algorithm.cyclo ./Core/Src/sensirion_gas_index_algorithm.d ./Core/Src/sensirion_gas_index_algorithm.o ./Core/Src/sensirion_gas_index_algorithm.su ./Core/Src/sgp40.cyclo ./Core/Src/sgp40.d ./Core/Src/sgp40.o ./Core/Src/sgp40.su ./Core/Src/stm32l0xx_hal_msp.cyclo ./Core/Src/stm32l0xx_hal_msp.d ./Core/Src/stm32l0xx_hal_msp.o ./Core/Src/stm32l0xx_hal_msp.su ./Core/Src/stm32l0xx_it.cyclo ./Core/Src/stm32l0xx_it.d ./Core/Src/stm32l0xx_it.o ./Core/Src/stm32l0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l0xx.cyclo ./Core/Src/system_stm32l0xx.d ./Core/Src/system_stm32l0xx.o ./Core/Src/system_stm32l0xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/utils.cyclo ./Core/Src/utils.d ./Core/Src/utils.o ./Core/Src/utils.su ./Core/Src/wsenHIDS.cyclo ./Core/Src/wsenHIDS.d ./Core/Src/wsenHIDS.o ./Core/Src/wsenHIDS.su

.PHONY: clean-Core-2f-Src

