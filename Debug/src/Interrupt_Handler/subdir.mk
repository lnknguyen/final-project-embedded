################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Interrupt_Handler/systick.cpp 

OBJS += \
./src/Interrupt_Handler/systick.o 

CPP_DEPS += \
./src/Interrupt_Handler/systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/Interrupt_Handler/%.o: ../src/Interrupt_Handler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/vinhxu/Desktop/Workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/vinhxu/Desktop/Workspace/lpc_chip_15xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


