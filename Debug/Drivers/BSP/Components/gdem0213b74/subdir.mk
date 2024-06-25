################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/gdem0213b74/gdem0213b74.c 

OBJS += \
./Drivers/BSP/Components/gdem0213b74/gdem0213b74.o 

C_DEPS += \
./Drivers/BSP/Components/gdem0213b74/gdem0213b74.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/gdem0213b74/%.o Drivers/BSP/Components/gdem0213b74/%.su Drivers/BSP/Components/gdem0213b74/%.cyclo: ../Drivers/BSP/Components/gdem0213b74/%.c Drivers/BSP/Components/gdem0213b74/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-gdem0213b74

clean-Drivers-2f-BSP-2f-Components-2f-gdem0213b74:
	-$(RM) ./Drivers/BSP/Components/gdem0213b74/gdem0213b74.cyclo ./Drivers/BSP/Components/gdem0213b74/gdem0213b74.d ./Drivers/BSP/Components/gdem0213b74/gdem0213b74.o ./Drivers/BSP/Components/gdem0213b74/gdem0213b74.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-gdem0213b74

