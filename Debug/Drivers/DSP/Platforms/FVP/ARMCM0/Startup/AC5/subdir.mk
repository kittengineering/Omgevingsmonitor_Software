################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/startup_ARMCM0.s 

OBJS += \
./Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/startup_ARMCM0.o 

S_DEPS += \
./Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/startup_ARMCM0.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/%.o: ../Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/%.s Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCM0-2f-Startup-2f-AC5

clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCM0-2f-Startup-2f-AC5:
	-$(RM) ./Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/startup_ARMCM0.d ./Drivers/DSP/Platforms/FVP/ARMCM0/Startup/AC5/startup_ARMCM0.o

.PHONY: clean-Drivers-2f-DSP-2f-Platforms-2f-FVP-2f-ARMCM0-2f-Startup-2f-AC5

