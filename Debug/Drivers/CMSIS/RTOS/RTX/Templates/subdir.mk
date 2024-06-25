################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.c 

OBJS += \
./Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.o 

C_DEPS += \
./Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS/RTX/Templates/%.o Drivers/CMSIS/RTOS/RTX/Templates/%.su Drivers/CMSIS/RTOS/RTX/Templates/%.cyclo: ../Drivers/CMSIS/RTOS/RTX/Templates/%.c Drivers/CMSIS/RTOS/RTX/Templates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-Templates

clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-Templates:
	-$(RM) ./Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.cyclo ./Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.d ./Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.o ./Drivers/CMSIS/RTOS/RTX/Templates/RTX_Conf_CM.su

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-Templates

