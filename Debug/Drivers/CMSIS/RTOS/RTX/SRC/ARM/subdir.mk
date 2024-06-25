################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/RTOS/RTX/SRC/ARM/SVC_Table.s 

C_SRCS += \
../Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.c \
../Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.c \
../Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.c 

OBJS += \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.o \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.o \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.o \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/SVC_Table.o 

S_DEPS += \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/SVC_Table.d 

C_DEPS += \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.d \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.d \
./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS/RTX/SRC/ARM/%.o Drivers/CMSIS/RTOS/RTX/SRC/ARM/%.su Drivers/CMSIS/RTOS/RTX/SRC/ARM/%.cyclo: ../Drivers/CMSIS/RTOS/RTX/SRC/ARM/%.c Drivers/CMSIS/RTOS/RTX/SRC/ARM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/CMSIS/RTOS/RTX/SRC/ARM/%.o: ../Drivers/CMSIS/RTOS/RTX/SRC/ARM/%.s Drivers/CMSIS/RTOS/RTX/SRC/ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC-2f-ARM

clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC-2f-ARM:
	-$(RM) ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.d ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.o ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM0.su ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.d ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.o ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM3.su ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.d ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.o ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/HAL_CM4.su ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/SVC_Table.d ./Drivers/CMSIS/RTOS/RTX/SRC/ARM/SVC_Table.o

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC-2f-ARM

