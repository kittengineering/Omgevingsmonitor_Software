################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.o 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/%.o Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/%.su Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/%.c Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD1_LPC55xxx.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CDC_ACM_UART_0.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/USBD_User_CustomClass_0.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/fsl_usart.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/main.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/ser_num.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK

