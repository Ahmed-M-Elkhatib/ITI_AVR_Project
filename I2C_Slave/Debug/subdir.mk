################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Program.c \
../I2C_Program.c \
../I2C_main_slave.c \
../LCDI2C_slave.c \
../LCD_program.c 

OBJS += \
./DIO_Program.o \
./I2C_Program.o \
./I2C_main_slave.o \
./LCDI2C_slave.o \
./LCD_program.o 

C_DEPS += \
./DIO_Program.d \
./I2C_Program.d \
./I2C_main_slave.d \
./LCDI2C_slave.d \
./LCD_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


