################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.c \
../Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.c 

OBJS += \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.o \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.o 

C_DEPS += \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.d \
./Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Driver/DriverTemplates/%.o Drivers/CMSIS/Driver/DriverTemplates/%.su Drivers/CMSIS/Driver/DriverTemplates/%.cyclo: ../Drivers/CMSIS/Driver/DriverTemplates/%.c Drivers/CMSIS/Driver/DriverTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Driver-2f-DriverTemplates

clean-Drivers-2f-CMSIS-2f-Driver-2f-DriverTemplates:
	-$(RM) ./Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_CAN.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Flash.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_I2C.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_MCI.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_NAND.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SAI.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_SPI.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_Storage.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USART.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBD.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_USBH.su ./Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.cyclo ./Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.d ./Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.o ./Drivers/CMSIS/Driver/DriverTemplates/Driver_WiFi.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Driver-2f-DriverTemplates

