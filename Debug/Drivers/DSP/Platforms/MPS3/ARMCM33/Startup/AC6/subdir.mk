################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.s 

OBJS += \
./Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.o 

S_DEPS += \
./Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/%.o: ../Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/%.s Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-DSP-2f-Platforms-2f-MPS3-2f-ARMCM33-2f-Startup-2f-AC6

clean-Drivers-2f-DSP-2f-Platforms-2f-MPS3-2f-ARMCM33-2f-Startup-2f-AC6:
	-$(RM) ./Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.d ./Drivers/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.o

.PHONY: clean-Drivers-2f-DSP-2f-Platforms-2f-MPS3-2f-ARMCM33-2f-Startup-2f-AC6

