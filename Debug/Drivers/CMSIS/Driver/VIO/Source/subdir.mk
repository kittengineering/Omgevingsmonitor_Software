################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Driver/VIO/Source/vio.c \
../Drivers/CMSIS/Driver/VIO/Source/vio_memory.c 

OBJS += \
./Drivers/CMSIS/Driver/VIO/Source/vio.o \
./Drivers/CMSIS/Driver/VIO/Source/vio_memory.o 

C_DEPS += \
./Drivers/CMSIS/Driver/VIO/Source/vio.d \
./Drivers/CMSIS/Driver/VIO/Source/vio_memory.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Driver/VIO/Source/%.o Drivers/CMSIS/Driver/VIO/Source/%.su Drivers/CMSIS/Driver/VIO/Source/%.cyclo: ../Drivers/CMSIS/Driver/VIO/Source/%.c Drivers/CMSIS/Driver/VIO/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Driver-2f-VIO-2f-Source

clean-Drivers-2f-CMSIS-2f-Driver-2f-VIO-2f-Source:
	-$(RM) ./Drivers/CMSIS/Driver/VIO/Source/vio.cyclo ./Drivers/CMSIS/Driver/VIO/Source/vio.d ./Drivers/CMSIS/Driver/VIO/Source/vio.o ./Drivers/CMSIS/Driver/VIO/Source/vio.su ./Drivers/CMSIS/Driver/VIO/Source/vio_memory.cyclo ./Drivers/CMSIS/Driver/VIO/Source/vio_memory.d ./Drivers/CMSIS/Driver/VIO/Source/vio_memory.o ./Drivers/CMSIS/Driver/VIO/Source/vio_memory.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Driver-2f-VIO-2f-Source

