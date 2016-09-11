################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CodePeg.cpp \
../src/CodePegCalculator.cpp \
../src/Configurator.cpp \
../src/InputValidator.cpp \
../src/KeyPeg.cpp \
../src/Main.cpp 

OBJS += \
./src/CodePeg.o \
./src/CodePegCalculator.o \
./src/Configurator.o \
./src/InputValidator.o \
./src/KeyPeg.o \
./src/Main.o 

CPP_DEPS += \
./src/CodePeg.d \
./src/CodePegCalculator.d \
./src/Configurator.d \
./src/InputValidator.d \
./src/KeyPeg.d \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\thang.le\git\general\MasterMind_Game_C_plus\inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


