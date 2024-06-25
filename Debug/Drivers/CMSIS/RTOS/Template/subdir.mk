################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/RTOS/Template/startup_LPC177x_8x.s 

C_SRCS += \
../Drivers/CMSIS/RTOS/Template/os_sample.c \
../Drivers/CMSIS/RTOS/Template/os_sample1.c \
../Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.c 

OBJS += \
./Drivers/CMSIS/RTOS/Template/os_sample.o \
./Drivers/CMSIS/RTOS/Template/os_sample1.o \
./Drivers/CMSIS/RTOS/Template/startup_LPC177x_8x.o \
./Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.o 

S_DEPS += \
./Drivers/CMSIS/RTOS/Template/startup_LPC177x_8x.d 

C_DEPS += \
./Drivers/CMSIS/RTOS/Template/os_sample.d \
./Drivers/CMSIS/RTOS/Template/os_sample1.d \
./Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS/Template/%.o Drivers/CMSIS/RTOS/Template/%.su Drivers/CMSIS/RTOS/Template/%.cyclo: ../Drivers/CMSIS/RTOS/Template/%.c Drivers/CMSIS/RTOS/Template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/CMSIS/RTOS/Template/%.o: ../Drivers/CMSIS/RTOS/Template/%.s Drivers/CMSIS/RTOS/Template/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-CMSIS-2f-RTOS-2f-Template

clean-Drivers-2f-CMSIS-2f-RTOS-2f-Template:
	-$(RM) ./Drivers/CMSIS/RTOS/Template/os_sample.cyclo ./Drivers/CMSIS/RTOS/Template/os_sample.d ./Drivers/CMSIS/RTOS/Template/os_sample.o ./Drivers/CMSIS/RTOS/Template/os_sample.su ./Drivers/CMSIS/RTOS/Template/os_sample1.cyclo ./Drivers/CMSIS/RTOS/Template/os_sample1.d ./Drivers/CMSIS/RTOS/Template/os_sample1.o ./Drivers/CMSIS/RTOS/Template/os_sample1.su ./Drivers/CMSIS/RTOS/Template/startup_LPC177x_8x.d ./Drivers/CMSIS/RTOS/Template/startup_LPC177x_8x.o ./Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.cyclo ./Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.d ./Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.o ./Drivers/CMSIS/RTOS/Template/system_LPC177x_8x.su

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS-2f-Template

