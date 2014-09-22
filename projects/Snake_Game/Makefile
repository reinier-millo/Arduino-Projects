# Cross-Compiler Tool
AVR_CC = /usr/bin/avr-gcc
AVR_OO = /usr/bin/avr-objcopy
AVR_DU = /usr/bin/avrdude
AVR_CONF = /home/millo/Working/Arduino/Arduino-Projects/tools/avrdude.conf

# Project name
PROJECT_NAME = Snake_Game

# Source code files
C_SOURCE = $(PROJECT_NAME).c\
	../../library/diecimila/accelerometer/accelerometer.c\
	../../library/diecimila/eeprom/eeprom.c\
	../../library/diecimila/lcd/lcd.c\
	../../library/diecimila/usart/usart.c\
	random.c\
	snake_lcd.c\
	snake_timer.c

all:compile upload

compile:
	$(AVR_CC) -Os -DF_CPU=16000000UL -mmcu=atmega168 $(C_SOURCE) -o $(PROJECT_NAME)
	$(AVR_OO) -O ihex -R .eeprom $(PROJECT_NAME) $(PROJECT_NAME).hex

upload:
	$(AVR_DU) -C $(AVR_CONF) -F -V -c arduino -p ATMEGA168 -P /dev/ttyUSB* -b 19200 -U flash:w:$(PROJECT_NAME).hex -v

clean:
	rm $(PROJECT_NAME)
	rm *.hex
