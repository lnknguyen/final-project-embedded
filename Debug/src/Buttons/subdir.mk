################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Buttons/Buttons.cpp \
../src/Buttons/DebouncedInput.cpp \
../src/Buttons/DigitalIoPin.cpp \
../src/Buttons/PinEvent.cpp 

OBJS += \
./src/Buttons/Buttons.o \
./src/Buttons/DebouncedInput.o \
./src/Buttons/DigitalIoPin.o \
./src/Buttons/PinEvent.o 

CPP_DEPS += \
./src/Buttons/Buttons.d \
./src/Buttons/DebouncedInput.d \
./src/Buttons/DigitalIoPin.d \
./src/Buttons/PinEvent.d 


# Each subdirectory must supply rules for building sources it contributes
src/Buttons/%.o: ../src/Buttons/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_chip_15xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


