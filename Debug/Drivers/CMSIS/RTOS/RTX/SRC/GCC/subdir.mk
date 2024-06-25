################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.S \
../Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.S \
../Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.S \
../Drivers/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.S 

OBJS += \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.o \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.o \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.o \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.o 

S_UPPER_DEPS += \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.d \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.d \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.d \
./Drivers/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS/RTX/SRC/GCC/%.o: ../Drivers/CMSIS/RTOS/RTX/SRC/GCC/%.S Drivers/CMSIS/RTOS/RTX/SRC/GCC/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC-2f-GCC

clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC-2f-GCC:
	-$(RM) ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.d ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.o ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.d ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.o ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.d ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.o ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.d ./Drivers/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.o

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC-2f-GCC

