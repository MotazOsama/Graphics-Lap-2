################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Circle.cpp \
../src/InitShader.cpp \
../src/Model.cpp \
../src/main.cpp \
../src/view.cpp 

OBJS += \
./src/Circle.o \
./src/InitShader.o \
./src/Model.o \
./src/main.o \
./src/view.o 

CPP_DEPS += \
./src/Circle.d \
./src/InitShader.d \
./src/Model.d \
./src/main.d \
./src/view.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


