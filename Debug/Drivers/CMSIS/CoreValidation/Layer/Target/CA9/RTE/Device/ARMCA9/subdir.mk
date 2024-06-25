################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.s 

C_SRCS += \
../Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.c \
../Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.c \
../Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.c 

OBJS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.o \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.o \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.o 

S_DEPS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.d 

C_DEPS += \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.d \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.d \
./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/%.o Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/%.su Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/%.cyclo: ../Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/%.c Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/%.o: ../Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/%.s Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CA9-2f-RTE-2f-Device-2f-ARMCA9

clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CA9-2f-RTE-2f-Device-2f-ARMCA9:
	-$(RM) ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/mmu_ARMCA9.su ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/startup_ARMCA9.su ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.cyclo ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.d ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.o ./Drivers/CMSIS/CoreValidation/Layer/Target/CA9/RTE/Device/ARMCA9/system_ARMCA9.su

.PHONY: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Layer-2f-Target-2f-CA9-2f-RTE-2f-Device-2f-ARMCA9

