################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.c \
../Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.c \
../Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.c \
../Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.c \
../Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.c \
../Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.c \
../Drivers/CMSIS/CoreValidation/Source/CV_Framework.c \
../Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.c \
../Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.c \
../Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.c \
../Drivers/CMSIS/CoreValidation/Source/CV_Report.c \
../Drivers/CMSIS/CoreValidation/Source/cmsis_cv.c 

OBJS += \
./Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.o \
./Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.o \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.o \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.o \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.o \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.o \
./Drivers/CMSIS/CoreValidation/Source/CV_Framework.o \
./Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.o \
./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.o \
./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.o \
./Drivers/CMSIS/CoreValidation/Source/CV_Report.o \
./Drivers/CMSIS/CoreValidation/Source/cmsis_cv.o 

C_DEPS += \
./Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.d \
./Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.d \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.d \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.d \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.d \
./Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.d \
./Drivers/CMSIS/CoreValidation/Source/CV_Framework.d \
./Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.d \
./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.d \
./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.d \
./Drivers/CMSIS/CoreValidation/Source/CV_Report.d \
./Drivers/CMSIS/CoreValidation/Source/cmsis_cv.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/CoreValidation/Source/%.o Drivers/CMSIS/CoreValidation/Source/%.su Drivers/CMSIS/CoreValidation/Source/%.cyclo: ../Drivers/CMSIS/CoreValidation/Source/%.c Drivers/CMSIS/CoreValidation/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Source

clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Source:
	-$(RM) ./Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.d ./Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.o ./Drivers/CMSIS/CoreValidation/Source/CV_CAL1Cache.su ./Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.d ./Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.o ./Drivers/CMSIS/CoreValidation/Source/CV_CML1Cache.su ./Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.d ./Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.o ./Drivers/CMSIS/CoreValidation/Source/CV_CoreAFunc.su ./Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.d ./Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.o ./Drivers/CMSIS/CoreValidation/Source/CV_CoreFunc.su ./Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.d ./Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.o ./Drivers/CMSIS/CoreValidation/Source/CV_CoreInstr.su ./Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.d ./Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.o ./Drivers/CMSIS/CoreValidation/Source/CV_CoreSimd.su ./Drivers/CMSIS/CoreValidation/Source/CV_Framework.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_Framework.d ./Drivers/CMSIS/CoreValidation/Source/CV_Framework.o ./Drivers/CMSIS/CoreValidation/Source/CV_Framework.su ./Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.d ./Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.o ./Drivers/CMSIS/CoreValidation/Source/CV_GenTimer.su ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.d ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.o ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.su ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.d ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.o ./Drivers/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.su ./Drivers/CMSIS/CoreValidation/Source/CV_Report.cyclo ./Drivers/CMSIS/CoreValidation/Source/CV_Report.d ./Drivers/CMSIS/CoreValidation/Source/CV_Report.o ./Drivers/CMSIS/CoreValidation/Source/CV_Report.su ./Drivers/CMSIS/CoreValidation/Source/cmsis_cv.cyclo ./Drivers/CMSIS/CoreValidation/Source/cmsis_cv.d ./Drivers/CMSIS/CoreValidation/Source/cmsis_cv.o ./Drivers/CMSIS/CoreValidation/Source/cmsis_cv.su

.PHONY: clean-Drivers-2f-CMSIS-2f-CoreValidation-2f-Source

