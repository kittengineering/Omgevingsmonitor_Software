################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Testing/Source/Tests/mfccdata.c \
../Drivers/DSP/Testing/Source/Tests/mfccdata_f16.c 

OBJS += \
./Drivers/DSP/Testing/Source/Tests/mfccdata.o \
./Drivers/DSP/Testing/Source/Tests/mfccdata_f16.o 

C_DEPS += \
./Drivers/DSP/Testing/Source/Tests/mfccdata.d \
./Drivers/DSP/Testing/Source/Tests/mfccdata_f16.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Testing/Source/Tests/%.o Drivers/DSP/Testing/Source/Tests/%.su Drivers/DSP/Testing/Source/Tests/%.cyclo: ../Drivers/DSP/Testing/Source/Tests/%.c Drivers/DSP/Testing/Source/Tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Testing-2f-Source-2f-Tests

clean-Drivers-2f-DSP-2f-Testing-2f-Source-2f-Tests:
	-$(RM) ./Drivers/DSP/Testing/Source/Tests/mfccdata.cyclo ./Drivers/DSP/Testing/Source/Tests/mfccdata.d ./Drivers/DSP/Testing/Source/Tests/mfccdata.o ./Drivers/DSP/Testing/Source/Tests/mfccdata.su ./Drivers/DSP/Testing/Source/Tests/mfccdata_f16.cyclo ./Drivers/DSP/Testing/Source/Tests/mfccdata_f16.d ./Drivers/DSP/Testing/Source/Tests/mfccdata_f16.o ./Drivers/DSP/Testing/Source/Tests/mfccdata_f16.su

.PHONY: clean-Drivers-2f-DSP-2f-Testing-2f-Source-2f-Tests

