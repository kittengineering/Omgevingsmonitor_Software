################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.c \
../Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.c 

OBJS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.o \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.o 

C_DEPS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.d \
./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/%.o Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/%.su Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/%.cyclo: ../Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/%.c Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CM33S_BL-2f-RTE-2f-Device-2f-ARMCM33_DSP_FP_TZ

clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CM33S_BL-2f-RTE-2f-Device-2f-ARMCM33_DSP_FP_TZ:
	-$(RM) ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/startup_ARMCM33.su ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CM33S_BL/RTE/Device/ARMCM33_DSP_FP_TZ/system_ARMCM33.su

.PHONY: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CM33S_BL-2f-RTE-2f-Device-2f-ARMCM33_DSP_FP_TZ

