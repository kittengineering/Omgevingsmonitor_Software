################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.c 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.o 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I"../Drivers/CMSIS/Device/ST/STM32L0xx" -I../Drivers/CMSIS/DSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-StatisticsFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-StatisticsFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/max.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/mean.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/min.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/power.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/rms.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/std.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/StatisticsFunctions/var.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-StatisticsFunctions

