################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.c \
../Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.c \
../Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.c 

OBJS += \
./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.o \
./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.o \
./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.o 

C_DEPS += \
./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.d \
./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.d \
./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/%.o Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/%.su Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/%.cyclo: ../Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/%.c Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_graphic_equalizer_example

clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_graphic_equalizer_example:
	-$(RM) ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.cyclo ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.d ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.o ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_data.su ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.cyclo ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.d ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.o ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.su ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.cyclo ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.d ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.o ./Drivers/DSP/Examples/ARM/arm_graphic_equalizer_example/math_helper.su

.PHONY: clean-Drivers-2f-DSP-2f-Examples-2f-ARM-2f-arm_graphic_equalizer_example

