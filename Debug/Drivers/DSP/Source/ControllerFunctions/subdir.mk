################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.c \
../Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.c \
../Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.c \
../Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.c \
../Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.c \
../Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.c \
../Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.c \
../Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.c \
../Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.o \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.o \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.o \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.o \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.o \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.o \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.o \
./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.o \
./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.d \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.d \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.d \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.d \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.d \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.d \
./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.d \
./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.d \
./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/ControllerFunctions/%.o Drivers/DSP/Source/ControllerFunctions/%.su Drivers/DSP/Source/ControllerFunctions/%.cyclo: ../Drivers/DSP/Source/ControllerFunctions/%.c Drivers/DSP/Source/ControllerFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Source-2f-ControllerFunctions

clean-Drivers-2f-DSP-2f-Source-2f-ControllerFunctions:
	-$(RM) ./Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.cyclo ./Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.d ./Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.o ./Drivers/DSP/Source/ControllerFunctions/ControllerFunctions.su ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.d ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.o ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_f32.su ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.d ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.o ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q15.su ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.d ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.o ./Drivers/DSP/Source/ControllerFunctions/arm_pid_init_q31.su ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.d ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.o ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_f32.su ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.d ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.o ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q15.su ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.d ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.o ./Drivers/DSP/Source/ControllerFunctions/arm_pid_reset_q31.su ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.d ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.o ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_f32.su ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.cyclo ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.d ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.o ./Drivers/DSP/Source/ControllerFunctions/arm_sin_cos_q31.su

.PHONY: clean-Drivers-2f-DSP-2f-Source-2f-ControllerFunctions

