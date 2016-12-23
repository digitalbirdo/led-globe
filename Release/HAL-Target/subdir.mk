################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL-Target/btm222.c \
../HAL-Target/debug.c \
../HAL-Target/display.c \
../HAL-Target/input.c \
../HAL-Target/reed_switch.c \
../HAL-Target/sync.c \
../HAL-Target/timer.c \
../HAL-Target/uart.c \
../HAL-Target/ws2803.c 

OBJS += \
./HAL-Target/btm222.o \
./HAL-Target/debug.o \
./HAL-Target/display.o \
./HAL-Target/input.o \
./HAL-Target/reed_switch.o \
./HAL-Target/sync.o \
./HAL-Target/timer.o \
./HAL-Target/uart.o \
./HAL-Target/ws2803.o 

C_DEPS += \
./HAL-Target/btm222.d \
./HAL-Target/debug.d \
./HAL-Target/display.d \
./HAL-Target/input.d \
./HAL-Target/reed_switch.d \
./HAL-Target/sync.d \
./HAL-Target/timer.d \
./HAL-Target/uart.d \
./HAL-Target/ws2803.d 


# Each subdirectory must supply rules for building sources it contributes
HAL-Target/%.o: ../HAL-Target/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


