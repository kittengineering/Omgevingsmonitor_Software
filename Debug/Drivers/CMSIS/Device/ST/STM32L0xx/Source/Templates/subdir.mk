################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/%.o Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/%.su Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/%.cyclo: ../Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/%.c Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32L0xx-2f-Source-2f-Templates

clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32L0xx-2f-Source-2f-Templates:
	-$(RM) ./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.cyclo ./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.d ./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.o ./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32L0xx-2f-Source-2f-Templates

