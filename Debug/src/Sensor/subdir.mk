################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Sensor/CO2Sensor.cpp \
../src/Sensor/I2C.cpp \
../src/Sensor/PressureSensor.cpp \
../src/Sensor/TemperatureSensor.cpp 

OBJS += \
./src/Sensor/CO2Sensor.o \
./src/Sensor/I2C.o \
./src/Sensor/PressureSensor.o \
./src/Sensor/TemperatureSensor.o 

CPP_DEPS += \
./src/Sensor/CO2Sensor.d \
./src/Sensor/I2C.d \
./src/Sensor/PressureSensor.d \
./src/Sensor/TemperatureSensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/Sensor/%.o: ../src/Sensor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/nguyenluong/Documents/LPCXpresso_8.0.0/workspace/lpc_chip_15xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


