################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LiquidCrystal_PCF8574.c \
../Src/adc.c \
../Src/adc2.c \
../Src/dht.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/i2c_lcd_driver.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer.c \
../Src/uart.c 

OBJS += \
./Src/LiquidCrystal_PCF8574.o \
./Src/adc.o \
./Src/adc2.o \
./Src/dht.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/i2c_lcd_driver.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer.o \
./Src/uart.o 

C_DEPS += \
./Src/LiquidCrystal_PCF8574.d \
./Src/adc.d \
./Src/adc2.d \
./Src/dht.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/i2c_lcd_driver.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 '-Dstm32f103x6.h' -DSTM32F103xB -c -I../Inc -I/Users/mazen/Desktop/STM32CubeIDE/workspace_1.14.0/chip_headers/CMSIS/Device/ST/STM32F1xx/Include -I/Users/mazen/Desktop/STM32CubeIDE/workspace_1.14.0/chip_headers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/LiquidCrystal_PCF8574.cyclo ./Src/LiquidCrystal_PCF8574.d ./Src/LiquidCrystal_PCF8574.o ./Src/LiquidCrystal_PCF8574.su ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/adc2.cyclo ./Src/adc2.d ./Src/adc2.o ./Src/adc2.su ./Src/dht.cyclo ./Src/dht.d ./Src/dht.o ./Src/dht.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/i2c_lcd_driver.cyclo ./Src/i2c_lcd_driver.d ./Src/i2c_lcd_driver.o ./Src/i2c_lcd_driver.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

