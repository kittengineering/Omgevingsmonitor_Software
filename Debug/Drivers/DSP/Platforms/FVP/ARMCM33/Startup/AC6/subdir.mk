################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.s 

C_SRCS += \
../Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.c 

OBJS += \
./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.o 

S_DEPS += \
./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.d 

C_DEPS += \
./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/%.o Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/%.su Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/%.cyclo: ../Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/%.c Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/%.o: ../Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/%.s Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCM33-2f-Startup-2f-AC6

clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCM33-2f-Startup-2f-AC6:
	-$(RM) ./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.cyclo ./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.d ./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.o ./Drivers/DSP/Platforms/FVP/ARMCM33/Startup/AC6/startup_ARMCM33.su

.PHONY: clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCM33-2f-Startup-2f-AC6

