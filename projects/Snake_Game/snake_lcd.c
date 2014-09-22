/*
 * snake_lcd.c
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
 * Date: 17/09/2014 - 09:04 PM
 *                      
 */

#include "Snake_Game.h"

/**
 * Clear the screen drawing s green square
 */
void clear_lcd_screen()
{
  draw_filled_rectangle(0, 0, SCREEN_SIZE, SCREEN_SIZE, GREEN);
}

/**
 * Draw a screen block to represent the snake
 */
void draw_block(int y, int x, int color)
{
  draw_filled_rectangle(y*BLOCK_SIZE, x*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
}

/**
 * Draw a small block on the screen */
void draw_small_block(int y, int x, int color)
{
  draw_filled_rectangle(y*4, x*4, 4, 4, color);
}