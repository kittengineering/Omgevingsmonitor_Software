################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/st7735/st7735.c 

OBJS += \
./Drivers/BSP/Components/st7735/st7735.o 

C_DEPS += \
./Drivers/BSP/Components/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/st7735/%.o Drivers/BSP/Components/st7735/%.su Drivers/BSP/Components/st7735/%.cyclo: ../Drivers/BSP/Components/st7735/%.c Drivers/BSP/Components/st7735/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-st7735

clean-Drivers-2f-BSP-2f-Components-2f-st7735:
	-$(RM) ./Drivers/BSP/Components/st7735/st7735.cyclo ./Drivers/BSP/Components/st7735/st7735.d ./Drivers/BSP/Components/st7735/st7735.o ./Drivers/BSP/Components/st7735/st7735.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-st7735

