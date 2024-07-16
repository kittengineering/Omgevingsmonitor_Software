################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.c 

OBJS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/%.o Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/%.su Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/%.cyclo: ../Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/%.c Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I"../Drivers/CMSIS/Device/ST/STM32L0xx" -I../Drivers/CMSIS/DSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_dotproduct_example

clean-Drivers-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_dotproduct_example:
	-$(RM) ./Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.cyclo ./Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.d ./Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.o ./Drivers/CMSIS/DSP/Examples/ARM/arm_dotproduct_example/arm_dotproduct_example_f32.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Examples-2f-ARM-2f-arm_dotproduct_example

