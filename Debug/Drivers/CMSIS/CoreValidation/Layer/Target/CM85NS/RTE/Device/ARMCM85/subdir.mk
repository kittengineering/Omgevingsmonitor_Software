################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.c \
../Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.c 

OBJS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.o \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.o 

C_DEPS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.d \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/%.o Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/%.su Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/%.cyclo: ../Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/%.c Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CM85NS-2f-RTE-2f-Device-2f-ARMCM85

clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CM85NS-2f-RTE-2f-Device-2f-ARMCM85:
	-$(RM) ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/startup_ARMCM85.su ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CM85NS/RTE/Device/ARMCM85/system_ARMCM85.su

.PHONY: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CM85NS-2f-RTE-2f-Device-2f-ARMCM85

