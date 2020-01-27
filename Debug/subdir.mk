################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO_REQ15.c \
../GPIO_REQ7.c \
../GPIO_REQ8.c \
../GPIO_REQ9.c \
../dcMotor.c \
../gpio.c \
../interrupt.c \
../led.c \
../main.c \
../pushButton.c \
../sevenSeg.c \
../softwareDelay.c \
../timers.c 

OBJS += \
./GPIO_REQ15.o \
./GPIO_REQ7.o \
./GPIO_REQ8.o \
./GPIO_REQ9.o \
./dcMotor.o \
./gpio.o \
./interrupt.o \
./led.o \
./main.o \
./pushButton.o \
./sevenSeg.o \
./softwareDelay.o \
./timers.o 

C_DEPS += \
./GPIO_REQ15.d \
./GPIO_REQ7.d \
./GPIO_REQ8.d \
./GPIO_REQ9.d \
./dcMotor.d \
./gpio.d \
./interrupt.d \
./led.d \
./main.d \
./pushButton.d \
./sevenSeg.d \
./softwareDelay.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


