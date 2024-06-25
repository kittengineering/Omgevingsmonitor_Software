################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/hx8347d/hx8347d.c 

OBJS += \
./Drivers/BSP/Components/hx8347d/hx8347d.o 

C_DEPS += \
./Drivers/BSP/Components/hx8347d/hx8347d.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/hx8347d/%.o Drivers/BSP/Components/hx8347d/%.su Drivers/BSP/Components/hx8347d/%.cyclo: ../Drivers/BSP/Components/hx8347d/%.c Drivers/BSP/Components/hx8347d/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-hx8347d

clean-Drivers-2f-BSP-2f-Components-2f-hx8347d:
	-$(RM) ./Drivers/BSP/Components/hx8347d/hx8347d.cyclo ./Drivers/BSP/Components/hx8347d/hx8347d.d ./Drivers/BSP/Components/hx8347d/hx8347d.o ./Drivers/BSP/Components/hx8347d/hx8347d.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-hx8347d

