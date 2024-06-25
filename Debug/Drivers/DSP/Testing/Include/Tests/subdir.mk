################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Testing/Include/Tests/mfccdata.c 

OBJS += \
./Drivers/DSP/Testing/Include/Tests/mfccdata.o 

C_DEPS += \
./Drivers/DSP/Testing/Include/Tests/mfccdata.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Testing/Include/Tests/%.o Drivers/DSP/Testing/Include/Tests/%.su Drivers/DSP/Testing/Include/Tests/%.cyclo: ../Drivers/DSP/Testing/Include/Tests/%.c Drivers/DSP/Testing/Include/Tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Testing-2f-Include-2f-Tests

clean-Drivers-2f-DSP-2f-Testing-2f-Include-2f-Tests:
	-$(RM) ./Drivers/DSP/Testing/Include/Tests/mfccdata.cyclo ./Drivers/DSP/Testing/Include/Tests/mfccdata.d ./Drivers/DSP/Testing/Include/Tests/mfccdata.o ./Drivers/DSP/Testing/Include/Tests/mfccdata.su

.PHONY: clean-Drivers-2f-DSP-2f-Testing-2f-Include-2f-Tests

