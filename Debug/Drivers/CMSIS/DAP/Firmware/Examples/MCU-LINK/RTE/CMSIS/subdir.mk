################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.o 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/%.o Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/%.su Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/%.c Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-RTE-2f-CMSIS

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-RTE-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/CMSIS/RTX_Config.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-RTE-2f-CMSIS

