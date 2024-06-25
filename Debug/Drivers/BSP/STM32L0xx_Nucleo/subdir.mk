################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.c 

OBJS += \
./Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.o 

C_DEPS += \
./Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32L0xx_Nucleo/%.o Drivers/BSP/STM32L0xx_Nucleo/%.su Drivers/BSP/STM32L0xx_Nucleo/%.cyclo: ../Drivers/BSP/STM32L0xx_Nucleo/%.c Drivers/BSP/STM32L0xx_Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32L0xx_Nucleo

clean-Drivers-2f-BSP-2f-STM32L0xx_Nucleo:
	-$(RM) ./Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.cyclo ./Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.d ./Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.o ./Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32L0xx_Nucleo

