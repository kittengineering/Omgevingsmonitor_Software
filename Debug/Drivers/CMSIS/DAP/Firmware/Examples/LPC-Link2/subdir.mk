################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.c \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.c \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.c \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.c \
../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.o \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.o \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.o \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.o \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.o 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.d \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.d \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.d \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.d \
./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/%.o Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/%.su Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/%.c Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CDC_ACM_UART_0.su ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/USBD_User_CustomClass_0.su ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/main.su ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/ser_num.su ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.d ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.o ./Drivers/CMSIS/DAP/Firmware/Examples/LPC-Link2/target.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-LPC-2d-Link2

