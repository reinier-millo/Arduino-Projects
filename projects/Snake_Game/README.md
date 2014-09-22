Snake Game
================

**About the game**

  This is a very simple game. The main idea is going
  moving the snake and eating the ball. When the snake
  eat the ball he will increase his size in one unit.
  The game board have a dimension of 16 rows and 16
  columns. At the begin of the game the snake have a
  size of two cells, and exist a delay of 500 ms
  between snake movements. The delay between movements
  and the time without eat the ball is regulated in the
  following way:

   - After 5 seconds the delay between movements of the
     snake is decreased in 25 ms until it reach 250 ms,
     thats mean, the snake is more faster every 5 seconds.
   - If the ball is not eaten after 10 seconds, change
     it's position to another random position (In the 7
     second the ball changes it's color as a warning).

  At the begining of the game the snake will be put in a
  random position in the board, giving a warranty of a
  valid movement for the two firsts movements of the snake.

**Electrical connection**

  The game was developed on Arduino Diecimila for ATMEGA168.

  The LCD display is conected to PORTB in pins 1 to 4:
   - SCK_P -> PIN 1
   - CS    -> PIN 2
   - DIO   -> PIN 3
   - RESET -> PIN 4
   
  The accelerometer is conected to PORTD in pins 2 and 3:
   - XPIN -> PIN 2
   - YPIN -> PIN 3
   - TPIN -> (NOT CONNECTED)
   
**Notes**

  - The EEPROM Memory is used to prevent the same sequence of
    random numbers on each reset. At the begining of the game
    a value is readed from EEPROM and used as random number
    seed. When a new random number is generated, then this
    number is stored on EEPROM to be used as seed at next reset.

  - The serial port USART must be used to test and calibrate
    the readed values from the accelerometer hardware. This
    values must be updated in the check_move_direction function
    (Snake_Game.c), in order to get a correct function of the game.