################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.c 

OBJS += \
./Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.o 

C_DEPS += \
./Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/%.o Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/%.su Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/%.cyclo: ../Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/%.c Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/MJSGadget/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Gravitech_4DigitsDisplay_NanoShield

clean-Drivers-2f-BSP-2f-Gravitech_4DigitsDisplay_NanoShield:
	-$(RM) ./Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.cyclo ./Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.d ./Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.o ./Drivers/BSP/Gravitech_4DigitsDisplay_NanoShield/stm32_gravitech_4digits.su

.PHONY: clean-Drivers-2f-BSP-2f-Gravitech_4DigitsDisplay_NanoShield

