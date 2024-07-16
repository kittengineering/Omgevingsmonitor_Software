################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv6-m.s \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv7-m.s 

C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.c 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv6-m.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv7-m.o 

S_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv6-m.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv7-m.d 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I"../Drivers/CMSIS/Device/ST/STM32L0xx" -I../Drivers/CMSIS/DSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/%.o: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/%.s Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-platform-2f-ARMCC

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-platform-2f-ARMCC:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/Retarget.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv6-m.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv6-m.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv7-m.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/platform/ARMCC/startup_armv7-m.o

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-platform-2f-ARMCC

