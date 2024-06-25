################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.c 

OBJS += \
./Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.o 

C_DEPS += \
./Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/%.o Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/%.su Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/%.cyclo: ../Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/%.c Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-App-2f-Validation_Cortex-2d-A

clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-App-2f-Validation_Cortex-2d-A:
	-$(RM) ./Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.cyclo ./Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.d ./Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.o ./Drivers/CMSIS/CoreValidation/Layer/App/Validation_Cortex-A/main.su

.PHONY: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-App-2f-Validation_Cortex-2d-A

