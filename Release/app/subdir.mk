################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/idle_state.c \
../app/init_state.c \
../app/load_card_state.c \
../app/setting_card_state.c \
../app/user_card_state.c 

OBJS += \
./app/idle_state.o \
./app/init_state.o \
./app/load_card_state.o \
./app/setting_card_state.o \
./app/user_card_state.o 

C_DEPS += \
./app/idle_state.d \
./app/init_state.d \
./app/load_card_state.d \
./app/setting_card_state.d \
./app/user_card_state.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o: ../app/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


