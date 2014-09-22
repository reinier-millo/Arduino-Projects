/*
 * accelerometer.c
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
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
 * Date: 17/09/2014 - 01:20 PM
 *                      
 */
 
#include "accelerometer.h"
#include "../lib.h"

/**
 * Initialice the accelerometer setting hte pin 2 and 3 of PORTD
 */
void init_accelerometer()
{
  CBI(DDRD,XPIN); // x-pin
  CBI(DDRD,YPIN); // y-pin
}

/**
 * Read the pin value
 */
int read_pin_value(int pin)
{
	int pin_value = 0;
	while(PIND & (1<<pin));
  while(!(PIND & (1<<pin)));
  while(PIND & (1<<pin)){
    ++pin_value;
  }
  return pin_value;
}