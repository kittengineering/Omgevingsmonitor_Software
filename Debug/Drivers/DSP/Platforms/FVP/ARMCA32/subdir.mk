################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.c \
../Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.c \
../Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.c 

OBJS += \
./Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.o \
./Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.o \
./Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.o 

C_DEPS += \
./Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.d \
./Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.d \
./Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Platforms/FVP/ARMCA32/%.o Drivers/DSP/Platforms/FVP/ARMCA32/%.su Drivers/DSP/Platforms/FVP/ARMCA32/%.cyclo: ../Drivers/DSP/Platforms/FVP/ARMCA32/%.c Drivers/DSP/Platforms/FVP/ARMCA32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCA32

clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCA32:
	-$(RM) ./Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.cyclo ./Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.d ./Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.o ./Drivers/DSP/Platforms/FVP/ARMCA32/irq_ctrl_gic.su ./Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.cyclo ./Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.d ./Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.o ./Drivers/DSP/Platforms/FVP/ARMCA32/mmu_ARMCA32.su ./Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.cyclo ./Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.d ./Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.o ./Drivers/DSP/Platforms/FVP/ARMCA32/system_ARMCA32.su

.PHONY: clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCA32

