################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.c \
../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.c 

OBJS += \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.o \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.o 

C_DEPS += \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.d \
./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/%.o Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/%.su Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/%.cyclo: ../Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/%.c Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-PythonWrapper-2f-cmsisdsp_pkg-2f-src

clean-Drivers-2f-DSP-2f-PythonWrapper-2f-cmsisdsp_pkg-2f-src:
	-$(RM) ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_basic.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_bayes.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_complexf.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_controller.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_distance.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_fastmath.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_filtering.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_interpolation.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_matrix.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_quaternion.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_statistics.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_support.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_svm.su ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.cyclo ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.d ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.o ./Drivers/DSP/PythonWrapper/cmsisdsp_pkg/src/cmsisdsp_transform.su

.PHONY: clean-Drivers-2f-DSP-2f-PythonWrapper-2f-cmsisdsp_pkg-2f-src

