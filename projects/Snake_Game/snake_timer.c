/*
 * snake_timer.c
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
 * Date: 17/09/2014 - 09:08 PM
 *                      
 */

#include "Snake_Game.h"
#include "../../library/diecimila/lib.h"
#include "../../library/diecimila/timer/timer.h"

#include <avr/interrupt.h>

/**
 * Initialize the Timer1 with prescaler 1024 to interrupt by
 * comparator A
 */
void init_counter_timer()
{
  // Disable interrupts
  cli();

  // Set the comparator register
  OCR1A = 0x3D08;

  // Mode 4, CTC on OCR1A
  TCCR1B |= (1 << WGM12);

  // Set interrupt on compare match
  TIMSK1 |= (1 << OCIE1A); 

  // Set prescaler to 1024 and start the timer
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable interrupts
  sei();
}

/**
 * Stop the Timer1
 */
void stop_counter_timer()
{
  // Diable interrupts
  cli();

  // Reset the registers values
  OCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;

  // Enable interrupts
  sei();
}

/**
 * Clock interrupt every 1 second
 */
ISR (TIMER1_COMPA_vect)
{
  seconds_count++;
  ball_count++;
  
  // Increase the snake velocity
  if(seconds_count==SECONDS_DELAY)
  {
    seconds_count = 0;
    move_delay = MAX(MIN_SPEED,(move_delay-DELTA_SPEED));
  }
  
  // Change the ball color
  if(ball_count==SECONDS_BALL_DELAY){
    draw_block(board->ball.y, board->ball.x, CYAN);

  // Generate a new position for the ball
  }else if(ball_count==SECONDS_BALL_MAX_DELAY){
    draw_block(board->ball.y, board->ball.x, GREEN);
    generate_ball_position();
  }
}