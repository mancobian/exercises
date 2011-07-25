################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Facebook/Breathalyzer/BkTree.cpp \
../Facebook/Breathalyzer/Breathalyzer.cpp \
../Facebook/Breathalyzer/Dictionary.cpp \
../Facebook/Breathalyzer/Levenshtein.cpp 

OBJS += \
./Facebook/Breathalyzer/BkTree.o \
./Facebook/Breathalyzer/Breathalyzer.o \
./Facebook/Breathalyzer/Dictionary.o \
./Facebook/Breathalyzer/Levenshtein.o 

CPP_DEPS += \
./Facebook/Breathalyzer/BkTree.d \
./Facebook/Breathalyzer/Breathalyzer.d \
./Facebook/Breathalyzer/Dictionary.d \
./Facebook/Breathalyzer/Levenshtein.d 


# Each subdirectory must supply rules for building sources it contributes
Facebook/Breathalyzer/%.o: ../Facebook/Breathalyzer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/arris/Code/Exercises" -I/Developer/SDKs/MacOSX10.6.sdk/usr/include/c++/4.2.1/ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


