################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.c \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.o \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.o 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.d \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/%.o Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/%.su Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/%.c Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-board

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-board:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/clock_config.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/peripherals.su ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.cyclo ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.o ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/board/pin_mux.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-board

