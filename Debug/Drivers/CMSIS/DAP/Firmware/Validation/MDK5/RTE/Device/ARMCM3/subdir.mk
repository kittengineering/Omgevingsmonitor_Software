################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/startup_ARMCM3.s 

C_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.c 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/startup_ARMCM3.o \
./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.o 

S_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/startup_ARMCM3.d 

C_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/%.o: ../Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/%.s Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/%.o Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/%.su Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/%.cyclo: ../Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/%.c Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Validation-2f-MDK5-2f-RTE-2f-Device-2f-ARMCM3

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Validation-2f-MDK5-2f-RTE-2f-Device-2f-ARMCM3:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/startup_ARMCM3.d ./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/startup_ARMCM3.o ./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.cyclo ./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.d ./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.o ./Drivers/CMSIS/DAP/Firmware/Validation/MDK5/RTE/Device/ARMCM3/system_ARMCM3.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Validation-2f-MDK5-2f-RTE-2f-Device-2f-ARMCM3

