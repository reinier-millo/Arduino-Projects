/*
 * Snake_Game.h
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

#ifndef Snake_Game_H_INCLUDED
#define Snake_Game_H_INCLUDED

#include "../../library/diecimila/lcd/lcd.h"

/* Board predefined dimensions */
#define BOARD_SIZE 16
#define MAX_SIZE (BOARD_SIZE*BOARD_SIZE)
#define BLOCK_SIZE SCREEN_SIZE/BOARD_SIZE

/* Snake velocity controller */
#define SECONDS_DELAY 5
#define DELTA_SPEED 25
#define MAX_SPEED 500
#define MIN_SPEED 250
int seconds_count;
int move_delay;

/* Ball time controller */
#define SECONDS_BALL_DELAY 7
#define SECONDS_BALL_MAX_DELAY 10
int ball_count;

/* Board point */
struct tpoint{
  int x;
  int y;
};
typedef struct tpoint Point;

/* Movements directions */
enum direction{UP,DOWN,LEFT,RIGHT};
typedef enum direction Direction;

/* Board structure */
struct board{
  int table[BOARD_SIZE][BOARD_SIZE];
  Point snake_head;
  Point snake_tail;
  Point ball;
  Direction move_direction;
  int snake_size;
  char game_over;
};
typedef struct board Board;

/* Game board */
Board *board;

/* Custom LCD functions */
void clear_lcd_screen();
void draw_block(int y, int x, int color);
void draw_small_block(int y, int x, int color);

/* Custom timer functions */
void init_counter_timer();
void stop_counter_timer();

/* Random numbers generator */
void generate_rand_seed();
int rand_number();

/* Initialicer functions */
void init_play_board();
void generate_initial_position();
void generate_ball_position();

/* Board movements functions */
int compare_points(Point p1, Point p2);
void check_snake_tail();
void move_snake();
void make_snake_move();
void check_move_direction();
void game_over();

#endif // Snake_Game_H_INCLUDED
