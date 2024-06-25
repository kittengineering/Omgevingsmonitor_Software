################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.c \
../Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.c 

OBJS += \
./Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o 

C_DEPS += \
./Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d \
./Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/QuaternionMathFunctions/%.o Drivers/DSP/Source/QuaternionMathFunctions/%.su Drivers/DSP/Source/QuaternionMathFunctions/%.cyclo: ../Drivers/DSP/Source/QuaternionMathFunctions/%.c Drivers/DSP/Source/QuaternionMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-QuaternionMathFunctions

clean-Drivers-2f-DSP-2f-Source-2f-QuaternionMathFunctions:
	-$(RM) ./Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.d ./Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.o ./Drivers/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.su ./Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.cyclo ./Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d ./Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o ./Drivers/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-QuaternionMathFunctions

