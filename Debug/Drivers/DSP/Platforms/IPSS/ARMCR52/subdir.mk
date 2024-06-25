################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.c \
../Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.c 

OBJS += \
./Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.o \
./Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.o 

C_DEPS += \
./Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.d \
./Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Platforms/IPSS/ARMCR52/%.o Drivers/DSP/Platforms/IPSS/ARMCR52/%.su Drivers/DSP/Platforms/IPSS/ARMCR52/%.cyclo: ../Drivers/DSP/Platforms/IPSS/ARMCR52/%.c Drivers/DSP/Platforms/IPSS/ARMCR52/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Platforms-2f-IPSS-2f-ARMCR52

clean-Drivers-2f-DSP-2f-Platforms-2f-IPSS-2f-ARMCR52:
	-$(RM) ./Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.cyclo ./Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.d ./Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.o ./Drivers/DSP/Platforms/IPSS/ARMCR52/mmu_ARMCR52.su ./Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.cyclo ./Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.d ./Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.o ./Drivers/DSP/Platforms/IPSS/ARMCR52/system_ARMCR52.su

.PHONY: clean-Drivers-2f-DSP-2f-Platforms-2f-IPSS-2f-ARMCR52

