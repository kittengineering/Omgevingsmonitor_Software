################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.c \
../Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.c \
../Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.c \
../Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.o \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.o \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.o \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.o 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.d \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.d \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.d \
./Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Template/MDK5/%.o Drivers/CMSIS/DAP/Firmware/Template/MDK5/%.su Drivers/CMSIS/DAP/Firmware/Template/MDK5/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Template/MDK5/%.c Drivers/CMSIS/DAP/Firmware/Template/MDK5/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Template-2f-MDK5

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Template-2f-MDK5:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.d ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.o ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CDC_ACM_UART_0.su ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.d ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.o ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_CustomClass_0.su ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.d ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.o ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/USBD_User_HID_0.su ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.cyclo ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.d ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.o ./Drivers/CMSIS/DAP/Firmware/Template/MDK5/main.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Template-2f-MDK5

