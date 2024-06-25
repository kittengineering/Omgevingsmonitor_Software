################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Scripts/mfcctemplates/mfccdata.c 

OBJS += \
./Drivers/DSP/Scripts/mfcctemplates/mfccdata.o 

C_DEPS += \
./Drivers/DSP/Scripts/mfcctemplates/mfccdata.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Scripts/mfcctemplates/%.o Drivers/DSP/Scripts/mfcctemplates/%.su Drivers/DSP/Scripts/mfcctemplates/%.cyclo: ../Drivers/DSP/Scripts/mfcctemplates/%.c Drivers/DSP/Scripts/mfcctemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Scripts-2f-mfcctemplates

clean-Drivers-2f-DSP-2f-Scripts-2f-mfcctemplates:
	-$(RM) ./Drivers/DSP/Scripts/mfcctemplates/mfccdata.cyclo ./Drivers/DSP/Scripts/mfcctemplates/mfccdata.d ./Drivers/DSP/Scripts/mfcctemplates/mfccdata.o ./Drivers/DSP/Scripts/mfcctemplates/mfccdata.su

.PHONY: clean-Drivers-2f-DSP-2f-Scripts-2f-mfcctemplates

