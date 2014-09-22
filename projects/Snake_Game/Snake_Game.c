/*
 * Snake_Game.c
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * Copyright (C) 2014 Reinier Millo Sánchez <rmillo@uclv.cu>
 *                    Universidad Central "Marta Abreu" de Las Villas
 * 
 * Date: 17/09/2014 - 08:07 PM
 *                      
 */

#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "Snake_Game.h"
#include "../../library/diecimila/lib.h"
#include "../../library/diecimila/accelerometer/accelerometer.h"
#include "../../library/diecimila/lcd/lcd.h"
#include "../../library/diecimila/timer/timer.h"
#include "../../library/diecimila/usart/usart.h"

/**
 * Change the snake direction according the accelerometer pins values.
 * The values must be tested for each accelerometer device.
 */
void check_move_direction()
{
  int xpin=read_pin_value(XPIN);
  int ypin=read_pin_value(YPIN);

  // Turn movement to right
  if (ypin<8900){
    board->move_direction=RIGHT;

  // Turn movement to left
  }else if (ypin>10000){
    board->move_direction=LEFT;

  // Turn movemento down
  }else if (xpin<8200){
  board->move_direction=DOWN;

  // Turn movement up
  }else if (xpin>10000){
    board->move_direction=UP;
  }
}

/**
 * Generate an initial random position for the snake on the board
 */
void generate_initial_position()
{
  // Random position
  int rnd_position = rand_number()%MAX_SIZE; 
  int row = rnd_position/BOARD_SIZE;
  int col = rnd_position%BOARD_SIZE;

  // Vertical snake moving up
  if(row>2)
  {
    board->snake_head.y = row-1;
    board->snake_head.x = col;
    board->snake_tail.y = row;
    board->snake_tail.x = col;
    board->move_direction = UP;
    
  // Vertical snake moving down
  }else
  {
    board->snake_head.y = row+1;
    board->snake_head.x = col;
    board->snake_tail.y = row;
    board->snake_tail.x = col;
    board->move_direction = DOWN;
  }
  
  // Set the snake position on the board
  board->table[board->snake_head.y][board->snake_head.x] = 5000;
  board->table[board->snake_tail.y][board->snake_tail.x] = 4999;
  board->snake_size = 2;
  
  // Draw the snake on the board
  draw_block(board->snake_tail.y, board->snake_tail.x, BLUE);
  draw_block(board->snake_head.y, board->snake_head.x, RED);
}

/**
 * Initialize the board
 */
void init_play_board()
{
  int i,j;
  for(i=0; i<BOARD_SIZE; ++i)
    for(j=0; j<BOARD_SIZE; ++j)
      board->table[i][j] = 0;
  board->game_over = 0;
}

/**
 * Generate a random position for the ball on the board
 */
void generate_ball_position()
{
  // Random position
  int rnd_position = rand_number()%MAX_SIZE;
  int row = rnd_position/BOARD_SIZE;
  int col = rnd_position%BOARD_SIZE;

  // Find next empty position
  while(board->table[row][col]!=0)
  {
    rnd_position = (rnd_position+1)%MAX_SIZE;
    row = rnd_position/BOARD_SIZE;
    col = rnd_position%BOARD_SIZE;
  }

  // Store the ball position
  board->ball.y = row;
  board->ball.x = col;

  // Restore the time counter
  ball_count = 0;

  // Draw the ball on the screen
  draw_block(row, col, YELLOW);
}

/**
 * Compare to point to check if the snake has catch the ball
 */
int compare_points(Point p1, Point p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

/**
 * Check if the snake tail must be removed form the screen after
 * a snake movement
 */
void check_snake_tail()
{
  // Check if the snake catch the ball
  if(compare_points(board->snake_head, board->ball))
  {
    // Increase the snake size
    board->snake_size++;
    // Generate a new posicion for the ball
    generate_ball_position();
    return;
  }
  
  int y=board->snake_tail.y;
  int x=board->snake_tail.x;

  // Verify if the precedent position is above the current position
  if(board->table[board->snake_tail.y-1][board->snake_tail.x]-1
      ==board->table[board->snake_tail.y][board->snake_tail.x])
  {
    board->snake_tail.y--;

  // Verify if the precedent position is below the current position
  }else if(board->table[board->snake_tail.y+1][board->snake_tail.x]-1
      ==board->table[board->snake_tail.y][board->snake_tail.x])
  {
    board->snake_tail.y++;

  // Verify if the precedent position is at the left of the curren position
  }else if(board->table[board->snake_tail.y][board->snake_tail.x-1]-1
      ==board->table[board->snake_tail.y][board->snake_tail.x])
  {
    board->snake_tail.x--;

  // Verify if the precedent position is at the right of the curren position
  }else if(board->table[board->snake_tail.y][board->snake_tail.x+1]-1
      ==board->table[board->snake_tail.y][board->snake_tail.x])
  {
    board->snake_tail.x++;
  }
  
  // Remove the snake tail
  draw_block(y,x,GREEN);
  board->table[y][x] = 0;
}

/**
 * Make a snake movement.
 * Fisrt we check if the snake have catched the ball, because in this
 * case the tail must be keep in the same position and the snake grown.
 */
void move_snake()
{
  check_snake_tail();
  make_snake_move();
}

/**
 * Mueve la serpiente en la dirección establecida
 */
void make_snake_move()
{
  int x = board->snake_head.x;
  int y = board->snake_head.y;
  switch(board->move_direction)
  {
    // The snake is moving up
    case UP:
      board->snake_head.y--;
      break;

    // The snake is moving down
    case DOWN:
      board->snake_head.y++;
      break;

    // The snake is moving to left
    case LEFT:
      board->snake_head.x--;
      break;

    // The snake is moving to right
    case RIGHT:
      board->snake_head.x++;
      break;
  }

  // Check if the snake is in a valid position or not
  if(board->snake_head.y<0 || board->snake_head.y==BOARD_SIZE || 
    board->snake_head.x<0 || board->snake_head.x==BOARD_SIZE || 
    board->table[board->snake_head.y][board->snake_head.x]!=0)
  {
    game_over();
    return;
  }

  // Update the snake position on the board
  board->table[board->snake_head.y][board->snake_head.x] = board->table[y][x] + 1; 

  // Remove the old snake head
  draw_block(y,x,BLUE);

  // Draw the new snake head
  draw_block(board->snake_head.y,board->snake_head.x,RED);
}

/**
 * Stop the game and draw a sad face
 */
void game_over()
{
  // Stop the time counter
  stop_counter_timer();
  _delay_ms(3000);

  // Stop the game and make a red screen
  board->game_over=1;
  draw_filled_rectangle(0, 0, SCREEN_SIZE, SCREEN_SIZE, RED);

  // Draw a sad face
  draw_filled_circle(66, 66, 40, GREEN, 1);
  draw_filled_circle(56, 46, 5, YELLOW, 1);
  draw_filled_circle(56, 86, 5, YELLOW, 1);
  draw_semicircle (90,66, 20, YELLOW, 1);
}

/**
 * Draw a small logo
 */
void draw_game_logo()
{
  /* Draw S */
  draw_small_block(24, 2, RED);
  draw_small_block(24, 3, RED);
  draw_small_block(24, 4, RED);

  draw_small_block(23, 1, RED);
  draw_small_block(22, 1, RED);
  draw_small_block(21, 1, RED);

  draw_small_block(20, 2, RED);
  draw_small_block(20, 3, RED);
  draw_small_block(20, 4, RED);

  draw_small_block(19, 5, RED);
  draw_small_block(18, 5, RED);
  draw_small_block(17, 5, RED);

  draw_small_block(16, 2, RED);
  draw_small_block(16, 3, RED);
  draw_small_block(16, 4, RED);

  /* Draw N */  
  draw_small_block(24, 7, RED);
  draw_small_block(23, 7, RED);
  draw_small_block(22, 7, RED);
  draw_small_block(21, 7, RED);
  draw_small_block(20, 7, RED);
  draw_small_block(19, 7, RED);
  draw_small_block(18, 7, RED);
  draw_small_block(17, 7, RED);
  draw_small_block(16, 7, RED);

  draw_small_block(24, 8, RED);
  draw_small_block(23, 8, RED);
  draw_small_block(22, 8, RED);

  draw_small_block(21, 9, RED);
  draw_small_block(20, 9, RED);
  draw_small_block(19, 9, RED);

  draw_small_block(18, 10, RED);
  draw_small_block(17, 10, RED);
  draw_small_block(16, 10, RED);

  draw_small_block(24, 11, RED);
  draw_small_block(23, 11, RED);
  draw_small_block(22, 11, RED);
  draw_small_block(21, 11, RED);
  draw_small_block(20, 11, RED);
  draw_small_block(19, 11, RED);
  draw_small_block(18, 11, RED);
  draw_small_block(17, 11, RED);
  draw_small_block(16, 11, RED);

  /* Draw A */    
  draw_small_block(23, 13, RED);
  draw_small_block(22, 13, RED);
  draw_small_block(21, 13, RED);
  draw_small_block(20, 13, RED);
  draw_small_block(19, 13, RED);
  draw_small_block(18, 13, RED);
  draw_small_block(17, 13, RED);
  draw_small_block(16, 13, RED);
  
  draw_small_block(24, 14, RED);
  draw_small_block(24, 15, RED);
  draw_small_block(24, 16, RED);
  
  draw_small_block(20, 14, RED);
  draw_small_block(20, 15, RED);
  draw_small_block(20, 16, RED);

  draw_small_block(23, 17, RED);
  draw_small_block(22, 17, RED);
  draw_small_block(21, 17, RED);
  draw_small_block(20, 17, RED);
  draw_small_block(19, 17, RED);
  draw_small_block(18, 17, RED);
  draw_small_block(17, 17, RED);
  draw_small_block(16, 17, RED);

  /* Draw K */
  draw_small_block(24, 19, RED);
  draw_small_block(23, 19, RED);
  draw_small_block(22, 19, RED);
  draw_small_block(21, 19, RED);
  draw_small_block(20, 19, RED);
  draw_small_block(19, 19, RED);
  draw_small_block(18, 19, RED);
  draw_small_block(17, 19, RED);
  draw_small_block(16, 19, RED);

  draw_small_block(24, 23, RED);
  draw_small_block(23, 22, RED);
  draw_small_block(22, 21, RED);
  draw_small_block(21, 20, RED);
  draw_small_block(20, 20, RED);
  draw_small_block(19, 20, RED);
  draw_small_block(18, 21, RED);
  draw_small_block(17, 22, RED);
  draw_small_block(16, 23, RED);

  /* Draw E */
  draw_small_block(24, 25, RED);
  draw_small_block(23, 25, RED);
  draw_small_block(22, 25, RED);
  draw_small_block(21, 25, RED);
  draw_small_block(20, 25, RED);
  draw_small_block(19, 25, RED);
  draw_small_block(18, 25, RED);
  draw_small_block(17, 25, RED);
  draw_small_block(16, 25, RED);

  draw_small_block(24, 26, RED);
  draw_small_block(24, 27, RED);
  draw_small_block(24, 28, RED);
  draw_small_block(24, 29, RED);

  draw_small_block(20, 26, RED);
  draw_small_block(20, 27, RED);
  draw_small_block(20, 28, RED);

  draw_small_block(16, 26, RED);
  draw_small_block(16, 27, RED);
  draw_small_block(16, 28, RED);
  draw_small_block(16, 29, RED);

  /* Draw a small snake */
  draw_small_block(11, 10, BLUE);
  draw_small_block(11, 11, BLUE);
  draw_small_block(11, 12, BLUE);
  draw_small_block(11, 13, BLUE);
  draw_small_block(11, 14, BLUE);
  draw_small_block(11, 15, BLUE);
  draw_small_block(10, 15, BLUE);
  draw_small_block(10, 16, BLUE);
  draw_small_block(10, 17, BLUE);
  draw_small_block(10, 18, BLUE);
  draw_small_block(10, 19, BLUE);
  draw_small_block(9, 19, BLUE);
  draw_small_block(8, 19, BLUE);
  draw_small_block(7, 19, BLUE);
  draw_small_block(7, 18, BLUE);
  draw_small_block(7, 17, BLUE);
  draw_small_block(7, 16, BLUE);
  draw_small_block(7, 15, BLUE);
  draw_small_block(7, 14, BLUE);
  draw_small_block(7, 13, RED);
}

int main(void)
{
  // Initialize the UART
  init_usart(MYUBBRR);

  // Initialize the random number seed
  generate_rand_seed();
  
  // Initialize the LCD display
  init_lcd_screen();
  clear_lcd_screen();
  
  // Draw the logo
  draw_game_logo();
  
  // Wait 4 seconds to start the game
  _delay_ms(4000);
  clear_lcd_screen();
  
  // Initialize the board game
  board = malloc(sizeof(Board));
  init_play_board();
  generate_initial_position();
  generate_ball_position();
  
  // Initialice the accelerometer
  init_accelerometer();
  
  // Initialice the timer
  init_counter_timer();
  move_delay = MAX_SPEED;
  
  // Play the game until the game over
  while(board->game_over==0){
    check_move_direction();
    move_snake();
    _delay_ms(move_delay);
  }
}