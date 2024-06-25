################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.c \
../Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.c \
../Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.c 

OBJS += \
./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.o \
./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.o \
./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.o 

C_DEPS += \
./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.d \
./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.d \
./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/InterpolationFunctions/%.o Drivers/DSP/Source/InterpolationFunctions/%.su Drivers/DSP/Source/InterpolationFunctions/%.cyclo: ../Drivers/DSP/Source/InterpolationFunctions/%.c Drivers/DSP/Source/InterpolationFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-InterpolationFunctions

clean-Drivers-2f-DSP-2f-Source-2f-InterpolationFunctions:
	-$(RM) ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.cyclo ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.d ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.o ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctions.su ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.cyclo ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.d ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.o ./Drivers/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.su ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.d ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.o ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.su ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.d ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.o ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.su ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.d ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.o ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.su ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.d ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.o ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.su ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.d ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.o ./Drivers/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.su ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.d ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.o ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.su ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.d ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.o ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.su ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.d ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.o ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.su ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.d ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.o ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.su ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.d ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.o ./Drivers/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.su ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.d ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.o ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.su ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.cyclo ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.d ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.o ./Drivers/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-InterpolationFunctions

