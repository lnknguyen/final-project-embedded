################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Sensor/subdir.mk
-include src/LCD/subdir.mk
-include src/InterruptHandler/subdir.mk
-include src/GUI/subdir.mk
-include src/Controller/subdir.mk
-include src/Buttons/subdir.mk
-include src/ABBDrive/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: final-project-embedded.axf

# Tool invocations
final-project-embedded.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_board_nxp_lpcxpresso_1549/Debug" -L"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_chip_15xx/Debug" -Xlinker -Map="final-project-embedded.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "project1_Debug.ld" -o "final-project-embedded.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) final-project-embedded.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "final-project-embedded.axf"; # arm-none-eabi-objcopy -v -O binary "final-project-embedded.axf" "final-project-embedded.bin" ; # checksum -p LPC1549 -d "final-project-embedded.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
