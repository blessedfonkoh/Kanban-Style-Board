################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bk-Assignment3-eclipse.c \
../src/boardEditFunctions.c \
../src/listEditFunctions.c \
../src/loadFromFile.c \
../src/tempCodeRunnerFile.c 

C_DEPS += \
./src/bk-Assignment3-eclipse.d \
./src/boardEditFunctions.d \
./src/listEditFunctions.d \
./src/loadFromFile.d \
./src/tempCodeRunnerFile.d 

OBJS += \
./src/bk-Assignment3-eclipse.o \
./src/boardEditFunctions.o \
./src/listEditFunctions.o \
./src/loadFromFile.o \
./src/tempCodeRunnerFile.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/bk-Assignment3-eclipse.d ./src/bk-Assignment3-eclipse.o ./src/boardEditFunctions.d ./src/boardEditFunctions.o ./src/listEditFunctions.d ./src/listEditFunctions.o ./src/loadFromFile.d ./src/loadFromFile.o ./src/tempCodeRunnerFile.d ./src/tempCodeRunnerFile.o

.PHONY: clean-src

