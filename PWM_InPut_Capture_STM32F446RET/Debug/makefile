################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := PWM_InPut_Capture_STM32F446RET
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
PWM_InPut_Capture_STM32F446RET.elf \

MAP_FILES += \
PWM_InPut_Capture_STM32F446RET.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PWM_InPut_Capture_STM32F446RET.list \

OBJCOPY_HEX += \
PWM_InPut_Capture_STM32F446RET.hex \

OBJCOPY_BIN += \
PWM_InPut_Capture_STM32F446RET.bin \


# All Target
all: main-build

# Main-build Target
main-build: PWM_InPut_Capture_STM32F446RET.elf secondary-outputs

# Tool invocations
PWM_InPut_Capture_STM32F446RET.elf PWM_InPut_Capture_STM32F446RET.map: $(OBJS) $(USER_OBJS) D:\STM32_My_Projects\PWM_InPut_Capture_STM32F446RET\STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "PWM_InPut_Capture_STM32F446RET.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\STM32_My_Projects\PWM_InPut_Capture_STM32F446RET\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="PWM_InPut_Capture_STM32F446RET.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PWM_InPut_Capture_STM32F446RET.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PWM_InPut_Capture_STM32F446RET.list"
	@echo 'Finished building: $@'
	@echo ' '

PWM_InPut_Capture_STM32F446RET.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "PWM_InPut_Capture_STM32F446RET.hex"
	@echo 'Finished building: $@'
	@echo ' '

PWM_InPut_Capture_STM32F446RET.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "PWM_InPut_Capture_STM32F446RET.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) PWM_InPut_Capture_STM32F446RET.bin PWM_InPut_Capture_STM32F446RET.elf PWM_InPut_Capture_STM32F446RET.hex PWM_InPut_Capture_STM32F446RET.list PWM_InPut_Capture_STM32F446RET.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
