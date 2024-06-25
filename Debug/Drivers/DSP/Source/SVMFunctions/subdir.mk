################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/SVMFunctions/SVMFunctions.c \
../Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.c \
../Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.c 

OBJS += \
./Drivers/DSP/Source/SVMFunctions/SVMFunctions.o \
./Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.o \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.o 

C_DEPS += \
./Drivers/DSP/Source/SVMFunctions/SVMFunctions.d \
./Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.d \
./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/SVMFunctions/%.o Drivers/DSP/Source/SVMFunctions/%.su Drivers/DSP/Source/SVMFunctions/%.cyclo: ../Drivers/DSP/Source/SVMFunctions/%.c Drivers/DSP/Source/SVMFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-SVMFunctions

clean-Drivers-2f-DSP-2f-Source-2f-SVMFunctions:
	-$(RM) ./Drivers/DSP/Source/SVMFunctions/SVMFunctions.cyclo ./Drivers/DSP/Source/SVMFunctions/SVMFunctions.d ./Drivers/DSP/Source/SVMFunctions/SVMFunctions.o ./Drivers/DSP/Source/SVMFunctions/SVMFunctions.su ./Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.cyclo ./Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.d ./Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.o ./Drivers/DSP/Source/SVMFunctions/SVMFunctionsF16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_init_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_linear_predict_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_init_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_polynomial_predict_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_init_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_rbf_predict_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_init_f32.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f16.su ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.cyclo ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.d ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.o ./Drivers/DSP/Source/SVMFunctions/arm_svm_sigmoid_predict_f32.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-SVMFunctions

