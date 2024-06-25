################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/gde021a1/gde021a1.c 

OBJS += \
./Drivers/BSP/Components/gde021a1/gde021a1.o 

C_DEPS += \
./Drivers/BSP/Components/gde021a1/gde021a1.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/gde021a1/%.o Drivers/BSP/Components/gde021a1/%.su Drivers/BSP/Components/gde021a1/%.cyclo: ../Drivers/BSP/Components/gde021a1/%.c Drivers/BSP/Components/gde021a1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-gde021a1

clean-Drivers-2f-BSP-2f-Components-2f-gde021a1:
	-$(RM) ./Drivers/BSP/Components/gde021a1/gde021a1.cyclo ./Drivers/BSP/Components/gde021a1/gde021a1.d ./Drivers/BSP/Components/gde021a1/gde021a1.o ./Drivers/BSP/Components/gde021a1/gde021a1.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-gde021a1

