################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.c 

OBJS += \
./Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.o 

C_DEPS += \
./Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/%.o Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/%.su Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/%.cyclo: ../Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/%.c Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L072xx -c -I../Core/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -IC:/Users/joris/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-SDFTools-2f-sdf-2f-nodes-2f-cpp-2f-StreamingNodes-2f-VHT-2f-video

clean-Drivers-2f-DSP-2f-SDFTools-2f-sdf-2f-nodes-2f-cpp-2f-StreamingNodes-2f-VHT-2f-video:
	-$(RM) ./Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.cyclo ./Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.d ./Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.o ./Drivers/DSP/SDFTools/sdf/nodes/cpp/StreamingNodes/VHT/video/video_drv.su

.PHONY: clean-Drivers-2f-DSP-2f-SDFTools-2f-sdf-2f-nodes-2f-cpp-2f-StreamingNodes-2f-VHT-2f-video

