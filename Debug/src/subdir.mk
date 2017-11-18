################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BaseFile.cpp \
../src/Directory.cpp \
../src/Files.cpp \
../src/Main.cpp 

OBJS += \
./src/BaseFile.o \
./src/Directory.o \
./src/Files.o \
./src/Main.o 

CPP_DEPS += \
./src/BaseFile.d \
./src/Directory.d \
./src/Files.d \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Iinclude -O0 -g3 -Wall -c -fmessage-length=0 -Weffc++ -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


