################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BaseCommand.cpp \
../src/BaseFile.cpp \
../src/Commands.cpp \
../src/Directory.cpp \
../src/Environment.cpp \
../src/FileSystem.cpp \
../src/Files.cpp \
../src/FilesTest1.cpp \
../src/FilesTest2.cpp \
../src/HistoryCommand.cpp \
../src/Main.cpp \
../src/RmCommand.cpp \
../src/Verbose.cpp \
../src/exeCommand.cpp \
../src/generalFunctions.cpp \
../src/rename.cpp \
../src/testMain.cpp 

OBJS += \
./src/BaseCommand.o \
./src/BaseFile.o \
./src/Commands.o \
./src/Directory.o \
./src/Environment.o \
./src/FileSystem.o \
./src/Files.o \
./src/FilesTest1.o \
./src/FilesTest2.o \
./src/HistoryCommand.o \
./src/Main.o \
./src/RmCommand.o \
./src/Verbose.o \
./src/exeCommand.o \
./src/generalFunctions.o \
./src/rename.o \
./src/testMain.o 

CPP_DEPS += \
./src/BaseCommand.d \
./src/BaseFile.d \
./src/Commands.d \
./src/Directory.d \
./src/Environment.d \
./src/FileSystem.d \
./src/Files.d \
./src/FilesTest1.d \
./src/FilesTest2.d \
./src/HistoryCommand.d \
./src/Main.d \
./src/RmCommand.d \
./src/Verbose.d \
./src/exeCommand.d \
./src/generalFunctions.d \
./src/rename.d \
./src/testMain.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Iinclude -O0 -g3 -Wall -c -fmessage-length=0 -Weffc++ -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


