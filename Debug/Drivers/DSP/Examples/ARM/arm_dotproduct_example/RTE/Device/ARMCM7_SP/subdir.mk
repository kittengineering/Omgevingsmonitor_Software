################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.c \
../Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.c 

OBJS += \
./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.o \
./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.o 

C_DEPS += \
./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.d \
./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/%.o Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/%.su Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/%.cyclo: ../Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/%.c Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_dotproduct_example-2f-RTE-2f-Device-2f-ARMCM7_SP

clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_dotproduct_example-2f-RTE-2f-Device-2f-ARMCM7_SP:
	-$(RM) ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.cyclo ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.d ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.o ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/startup_ARMCM7.su ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.cyclo ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.d ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.o ./Drivers/DSP/Examples/ARM/arm_dotproduct_example/RTE/Device/ARMCM7_SP/system_ARMCM7.su

.PHONY: clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_dotproduct_example-2f-RTE-2f-Device-2f-ARMCM7_SP

