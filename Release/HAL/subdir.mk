################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LCD.c \
../HAL/NFC_13_56MHZ.c \
../HAL/buzzer.c \
../HAL/keypad.c 

OBJS += \
./HAL/LCD.o \
./HAL/NFC_13_56MHZ.o \
./HAL/buzzer.o \
./HAL/keypad.o 

C_DEPS += \
./HAL/LCD.d \
./HAL/NFC_13_56MHZ.d \
./HAL/buzzer.d \
./HAL/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


