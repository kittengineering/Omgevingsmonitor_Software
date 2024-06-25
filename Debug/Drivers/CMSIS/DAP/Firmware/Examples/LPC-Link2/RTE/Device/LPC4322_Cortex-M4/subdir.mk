################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/startup_LPC43xx.s 

C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/startup_LPC43xx.o \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.o 

S_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/startup_LPC43xx.d 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/%.o: ../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/%.s Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/%.o Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/%.su Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/%.c Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2-2f-RTE-2f-Device-2f-LPC4322_Cortex-2d-M4

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2-2f-RTE-2f-Device-2f-LPC4322_Cortex-2d-M4:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/startup_LPC43xx.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/startup_LPC43xx.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/Device/LPC4322_Cortex-M4/system_LPC43xx.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2-2f-RTE-2f-Device-2f-LPC4322_Cortex-2d-M4

