/*
 * random.c
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
 * Date: 17/09/2014 - 08:15 PM
 *                      
 */
 
 #include "../../library/diecimila/eeprom/eeprom.h"
 
/**
 * Read the random numbers seed from EEPROM Memory to prevent the
 * same sequence of random numbers on each reboot
 */
void generate_rand_seed()
{
  // Read seed from EEPROM
  int rand_seed = read_word(0);
  // Set the random number seed
  srand(rand_seed);
}

/**
 * Generate a new random number and store it in EEPROM to be
 * used as seed on next reboot
  */
int rand_number()
{
  // Generate the new random number
  int rnd = rand();
  // Store the number on EEPROM
  write_word(0,rnd);
  
  return rnd;
}