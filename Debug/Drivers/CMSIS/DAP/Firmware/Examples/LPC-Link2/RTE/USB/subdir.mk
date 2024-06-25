################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.o 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/%.o Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/%.su Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/%.c Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2-2f-RTE-2f-USB

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2-2f-RTE-2f-USB:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/RTE/USB/USBD_Config_0.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2-2f-RTE-2f-USB

