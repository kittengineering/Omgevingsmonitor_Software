################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.c \
../Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.c 

OBJS += \
./Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.o \
./Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.o 

C_DEPS += \
./Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.d \
./Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Platforms/IPSS/ARMCR5/%.o Drivers/DSP/Platforms/IPSS/ARMCR5/%.su Drivers/DSP/Platforms/IPSS/ARMCR5/%.cyclo: ../Drivers/DSP/Platforms/IPSS/ARMCR5/%.c Drivers/DSP/Platforms/IPSS/ARMCR5/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Platforms-2f-IPSS-2f-ARMCR5

clean-Drivers-2f-DSP-2f-Platforms-2f-IPSS-2f-ARMCR5:
	-$(RM) ./Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.cyclo ./Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.d ./Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.o ./Drivers/DSP/Platforms/IPSS/ARMCR5/mmu_ARMCR5.su ./Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.cyclo ./Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.d ./Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.o ./Drivers/DSP/Platforms/IPSS/ARMCR5/system_ARMCR5.su

.PHONY: clean-Drivers-2f-DSP-2f-Platforms-2f-IPSS-2f-ARMCR5

