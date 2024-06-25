################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_List.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_System.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.c \
../Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.c 

OBJS += \
./Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_List.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_System.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.o \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.o 

C_DEPS += \
./Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_List.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_System.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.d \
./Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS/RTX/SRC/%.o Drivers/CMSIS/RTOS/RTX/SRC/%.su Drivers/CMSIS/RTOS/RTX/SRC/%.cyclo: ../Drivers/CMSIS/RTOS/RTX/SRC/%.c Drivers/CMSIS/RTOS/RTX/SRC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC

clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC:
	-$(RM) ./Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.d ./Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.o ./Drivers/CMSIS/RTOS/RTX/SRC/HAL_CM.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_CMSIS.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Event.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_List.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_List.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_List.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_List.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mailbox.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_MemBox.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Memory.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Mutex.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Robin.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Semaphore.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_System.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_System.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_System.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_System.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Task.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Time.su ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.cyclo ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.d ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.o ./Drivers/CMSIS/RTOS/RTX/SRC/rt_Timer.su

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-SRC

