################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := I2C_Part_6_MasterReadsData
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
I2C_Part_6_MasterReadsData.elf \

MAP_FILES += \
I2C_Part_6_MasterReadsData.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
I2C_Part_6_MasterReadsData.list \

OBJCOPY_HEX += \
I2C_Part_6_MasterReadsData.hex \

OBJCOPY_BIN += \
I2C_Part_6_MasterReadsData.bin \


# All Target
all: main-build

# Main-build Target
main-build: I2C_Part_6_MasterReadsData.elf secondary-outputs

# Tool invocations
I2C_Part_6_MasterReadsData.elf I2C_Part_6_MasterReadsData.map: $(OBJS) $(USER_OBJS) D:\STM32_My_Projects\I2C_Part_6_MasterReadsData\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "I2C_Part_6_MasterReadsData.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\STM32_My_Projects\I2C_Part_6_MasterReadsData\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="I2C_Part_6_MasterReadsData.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

I2C_Part_6_MasterReadsData.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "I2C_Part_6_MasterReadsData.list"
	@echo 'Finished building: $@'
	@echo ' '

I2C_Part_6_MasterReadsData.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "I2C_Part_6_MasterReadsData.hex"
	@echo 'Finished building: $@'
	@echo ' '

I2C_Part_6_MasterReadsData.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "I2C_Part_6_MasterReadsData.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) I2C_Part_6_MasterReadsData.bin I2C_Part_6_MasterReadsData.elf I2C_Part_6_MasterReadsData.hex I2C_Part_6_MasterReadsData.list I2C_Part_6_MasterReadsData.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
