################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/modes/conway.c \
../Application/modes/flappy.c \
../Application/modes/modes.c \
../Application/modes/pacman.c \
../Application/modes/pacman_field.c \
../Application/modes/pong.c \
../Application/modes/snake.c \
../Application/modes/text.c \
../Application/modes/world.c 

OBJS += \
./Application/modes/conway.o \
./Application/modes/flappy.o \
./Application/modes/modes.o \
./Application/modes/pacman.o \
./Application/modes/pacman_field.o \
./Application/modes/pong.o \
./Application/modes/snake.o \
./Application/modes/text.o \
./Application/modes/world.o 

C_DEPS += \
./Application/modes/conway.d \
./Application/modes/flappy.d \
./Application/modes/modes.d \
./Application/modes/pacman.d \
./Application/modes/pacman_field.d \
./Application/modes/pong.d \
./Application/modes/snake.d \
./Application/modes/text.d \
./Application/modes/world.d 


# Each subdirectory must supply rules for building sources it contributes
Application/modes/%.o: ../Application/modes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


