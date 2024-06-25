################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.c \
../Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.c \
../Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.c \
../Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.c \
../Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.c \
../Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.c \
../Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.c \
../Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.c 

OBJS += \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.o \
./Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.o \
./Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.o \
./Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.o \
./Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.o \
./Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.o \
./Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.o \
./Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.o 

C_DEPS += \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.d \
./Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.d \
./Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.d \
./Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.d \
./Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.d \
./Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.d \
./Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.d \
./Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DoxyGen/Driver/src/%.o Drivers/CMSIS/DoxyGen/Driver/src/%.su Drivers/CMSIS/DoxyGen/Driver/src/%.cyclo: ../Drivers/CMSIS/DoxyGen/Driver/src/%.c Drivers/CMSIS/DoxyGen/Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DoxyGen-2f-Driver-2f-src

clean-Drivers-2f-CMSIS-2f-DoxyGen-2f-Driver-2f-src:
	-$(RM) ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_CAN.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Common.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_MAC.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_ETH_PHY.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Flash.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_I2C.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_MCI.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_NAND.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SAI.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_SPI.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_Storage.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USART.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USB.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBD.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_USBH.su ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.d ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.o ./Drivers/CMSIS/DoxyGen/Driver/src/Driver_WiFi.su ./Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.d ./Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.o ./Drivers/CMSIS/DoxyGen/Driver/src/Flash_Demo.su ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.d ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.o ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_Demo.su ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.d ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.o ./Drivers/CMSIS/DoxyGen/Driver/src/I2C_SlaveDemo.su ./Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.d ./Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.o ./Drivers/CMSIS/DoxyGen/Driver/src/MCI_Demo.su ./Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.d ./Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.o ./Drivers/CMSIS/DoxyGen/Driver/src/NAND_Demo.su ./Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.d ./Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.o ./Drivers/CMSIS/DoxyGen/Driver/src/SPI_Demo.su ./Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.cyclo ./Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.d ./Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.o ./Drivers/CMSIS/DoxyGen/Driver/src/USART_Demo.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DoxyGen-2f-Driver-2f-src

