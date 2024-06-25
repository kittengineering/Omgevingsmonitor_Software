################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.c \
../Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.c 

OBJS += \
./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.o \
./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.o 

C_DEPS += \
./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.d \
./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/%.o Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/%.su Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/%.cyclo: ../Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/%.c Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_fir_example-2f-RTE-2f-Device-2f-ARMCM0

clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_fir_example-2f-RTE-2f-Device-2f-ARMCM0:
	-$(RM) ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.cyclo ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.d ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.o ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/startup_ARMCM0.su ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.cyclo ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.d ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.o ./Drivers/DSP/Examples/ARM/arm_fir_example/RTE/Device/ARMCM0/system_ARMCM0.su

.PHONY: clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_fir_example-2f-RTE-2f-Device-2f-ARMCM0

