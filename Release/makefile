################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include HAL-Target/subdir.mk
-include Application/modes/subdir.mk
-include Application/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
led-globe.lss \

FLASH_IMAGE += \
led-globe.hex \

EEPROM_IMAGE += \
led-globe.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: led-globe.elf secondary-outputs

# Tool invocations
led-globe.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,led-globe.map -mmcu=atmega328p -o "led-globe.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

led-globe.lss: led-globe.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S led-globe.elf  >"led-globe.lss"
	@echo 'Finished building: $@'
	@echo ' '

led-globe.hex: led-globe.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex led-globe.elf  "led-globe.hex"
	@echo 'Finished building: $@'
	@echo ' '

led-globe.eep: led-globe.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex led-globe.elf  "led-globe.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: led-globe.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p led-globe.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) led-globe.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
