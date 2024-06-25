################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/startup_LPC55S69_cm33_core0.S 

OBJS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/startup_LPC55S69_cm33_core0.o 

S_UPPER_DEPS += \
./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/startup_LPC55S69_cm33_core0.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/%.o: ../Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/%.S Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-RTE-2f-Device-2f-LPC55S69JBD64_cm33_core0

clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-RTE-2f-Device-2f-LPC55S69JBD64_cm33_core0:
	-$(RM) ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/startup_LPC55S69_cm33_core0.d ./Drivers/CMSIS/DAP/Firmware/Examples/MCU-LINK/RTE/Device/LPC55S69JBD64_cm33_core0/startup_LPC55S69_cm33_core0.o

.PHONY: clean-Drivers-2f-CMSIS-2f-DAP-2f-Firmware-2f-Examples-2f-MCU-2d-LINK-2f-RTE-2f-Device-2f-LPC55S69JBD64_cm33_core0

