################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.c \
../Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.o \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.d \
./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/FastMathFunctions/%.o Drivers/CMSIS/DSP/Source/FastMathFunctions/%.su Drivers/CMSIS/DSP/Source/FastMathFunctions/%.cyclo: ../Drivers/CMSIS/DSP/Source/FastMathFunctions/%.c Drivers/CMSIS/DSP/Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-FastMathFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-FastMathFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q31.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q31.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.su ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.cyclo ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.d ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.o ./Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q31.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-FastMathFunctions

