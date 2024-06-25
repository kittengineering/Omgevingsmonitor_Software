################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.c \
../Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.c 

OBJS += \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.o \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.o 

C_DEPS += \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.d \
./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32L073Z_EVAL/%.o Drivers/BSP/STM32L073Z_EVAL/%.su Drivers/BSP/STM32L073Z_EVAL/%.cyclo: ../Drivers/BSP/STM32L073Z_EVAL/%.c Drivers/BSP/STM32L073Z_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32L073Z_EVAL

clean-Drivers-2f-BSP-2f-STM32L073Z_EVAL:
	-$(RM) ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_eeprom.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_glass_lcd.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_idd.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_io.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_lcd.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_sd.su ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.cyclo ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.d ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.o ./Drivers/BSP/STM32L073Z_EVAL/stm32l073z_eval_tsensor.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32L073Z_EVAL

