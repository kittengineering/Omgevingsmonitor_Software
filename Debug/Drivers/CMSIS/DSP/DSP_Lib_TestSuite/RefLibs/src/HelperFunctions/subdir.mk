################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.c 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.o 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I"../Drivers/CMSIS/Device/ST/STM32L0xx" -I../Drivers/CMSIS/DSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-HelperFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-HelperFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/mat_helper.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/HelperFunctions/ref_helper.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-HelperFunctions

