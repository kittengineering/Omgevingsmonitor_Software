################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/USB_Device_Library/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MJSGadget - dB meter
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MJSGadget\ -\ dB\ meter.elf \

MAP_FILES += \
MJSGadget\ -\ dB\ meter.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MJSGadget\ -\ dB\ meter.list \


# All Target
all: main-build

# Main-build Target
main-build: MJSGadget\ -\ dB\ meter.elf secondary-outputs

# Tool invocations
MJSGadget\ -\ dB\ meter.elf MJSGadget\ -\ dB\ meter.map: $(OBJS) $(USER_OBJS) C:\Users\itsme\OneDrive\Documenten\GitHub\MJSGadget\ -\ dB\ meter\STM32L072RZTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "MJSGadget - dB meter.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\itsme\OneDrive\Documenten\GitHub\MJSGadget - dB meter\STM32L072RZTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MJSGadget - dB meter.map" -Wl,--gc-sections -static -L"C:\Users\itsme\OneDrive\Documenten\GitHub\MJSGadget - dB meter\Drivers\CMSIS\Lib\GCC" --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MJSGadget\ -\ dB\ meter.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MJSGadget - dB meter.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MJSGadget\ -\ dB\ meter.elf MJSGadget\ -\ dB\ meter.list MJSGadget\ -\ dB\ meter.map MJSGadget\\ -\\ dB\\ meter.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
