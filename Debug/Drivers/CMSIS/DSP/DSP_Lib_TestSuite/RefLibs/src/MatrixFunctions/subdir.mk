################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.c 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.o 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I"../Drivers/CMSIS/Device/ST/STM32L0xx" -I../Drivers/CMSIS/DSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-MatrixFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-MatrixFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-MatrixFunctions

