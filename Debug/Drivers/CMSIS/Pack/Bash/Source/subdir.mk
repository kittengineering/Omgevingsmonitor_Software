################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Pack/Bash/Source/component.c 

OBJS += \
./Drivers/CMSIS/Pack/Bash/Source/component.o 

C_DEPS += \
./Drivers/CMSIS/Pack/Bash/Source/component.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Pack/Bash/Source/%.o Drivers/CMSIS/Pack/Bash/Source/%.su Drivers/CMSIS/Pack/Bash/Source/%.cyclo: ../Drivers/CMSIS/Pack/Bash/Source/%.c Drivers/CMSIS/Pack/Bash/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Pack-2f-Bash-2f-Source

clean-Drivers-2f-CMSIS-2f-Pack-2f-Bash-2f-Source:
	-$(RM) ./Drivers/CMSIS/Pack/Bash/Source/component.cyclo ./Drivers/CMSIS/Pack/Bash/Source/component.d ./Drivers/CMSIS/Pack/Bash/Source/component.o ./Drivers/CMSIS/Pack/Bash/Source/component.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Pack-2f-Bash-2f-Source

