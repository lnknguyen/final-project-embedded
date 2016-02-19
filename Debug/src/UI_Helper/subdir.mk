################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UI_Helper/BarGraph.cpp \
../src/UI_Helper/IntegerEdit.cpp \
../src/UI_Helper/MenuItem.cpp \
../src/UI_Helper/SimpleMenu.cpp \
../src/UI_Helper/StaticItem.cpp \
../src/UI_Helper/TextEdit.cpp 

OBJS += \
./src/UI_Helper/BarGraph.o \
./src/UI_Helper/IntegerEdit.o \
./src/UI_Helper/MenuItem.o \
./src/UI_Helper/SimpleMenu.o \
./src/UI_Helper/StaticItem.o \
./src/UI_Helper/TextEdit.o 

CPP_DEPS += \
./src/UI_Helper/BarGraph.d \
./src/UI_Helper/IntegerEdit.d \
./src/UI_Helper/MenuItem.d \
./src/UI_Helper/SimpleMenu.d \
./src/UI_Helper/StaticItem.d \
./src/UI_Helper/TextEdit.d 


# Each subdirectory must supply rules for building sources it contributes
src/UI_Helper/%.o: ../src/UI_Helper/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_chip_15xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


