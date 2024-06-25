################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.c \
../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.c 

OBJS += \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.o \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.o 

C_DEPS += \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.d \
./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/%.o Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/%.su Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/%.cyclo: ../Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/%.c Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-UserCodeTemplates

clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-UserCodeTemplates:
	-$(RM) ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.su ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.cyclo ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.d ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.o ./Drivers/CMSIS/RTOS/RTX/UserCodeTemplates/main.su

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS-2f-RTX-2f-UserCodeTemplates

