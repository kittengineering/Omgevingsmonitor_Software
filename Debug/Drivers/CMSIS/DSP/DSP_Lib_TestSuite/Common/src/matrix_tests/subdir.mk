################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.c 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.o 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/%.su Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/%.cyclo: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I"C:/Users/joris/Documents/1. Projects/Stage/4. STM32/MJSGadget/Lib" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc" -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I"../Drivers/CMSIS/Device/ST/STM32L0xx" -I../Drivers/CMSIS/DSP -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-src-2f-matrix_tests

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-src-2f-matrix_tests:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_add_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_cmplx_mult_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_init_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_inverse_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_fast_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_mult_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_scale_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_sub_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/mat_trans_tests.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_common_data.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.cyclo ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/src/matrix_tests/matrix_test_group.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-Common-2f-src-2f-matrix_tests

