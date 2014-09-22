/*
 * eeprom.c
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
 * Date: 16/09/2014 - 09:17 AM
 *                      
 */
 
#include "eeprom.h" 
#include "../lib.h" 

/**
 * Write a byte to the EEPROM Memory in the
 * corresponding memory address
 */
void write_byte(unsigned int addr, unsigned char data)
{
  /* Wait for completion of previous write */
  while(EECR & (1<<EEPE));

  /* Set up address and Data Registers */
  EEAR = addr;
  EEDR = data;

  /* Write logical one to EEMPE */
  SBI(EECR,EEMPE); // EECR |= (1<<EEMPE);

  /* Start eeprom write by setting EEPE */
  SBI(EECR,EEPE); //EECR |= (1<<EEPE);
}

/**
 * Read a byte from the EEPROM Memory in the
 * corresponding memory address
 */
unsigned char read_byte(unsigned int addr)
{
  /* Wait for completion of previous write */
  while(EECR & (1<<EEPE));

  /* Set up address register */
  EEAR = addr;

  /* Start eeprom read by writing EERE */
  SBI(EECR,EERE); // EECR |= (1<<EERE);

  /* Return data from Data Register */
  return EEDR;
}

/**
 * Write a 16 bit integer to the EEPROM Memory in the
 * corresponding memory address
 */
void write_word(unsigned int addr, unsigned int data){
  write_byte(addr,((unsigned char)(data>>8)));
  write_byte(addr+1,((unsigned char)data));
}

/**
 * Read a 16 bit number from the EEPROM Memory in the
 * corresponding memory address
 */
unsigned int read_word(unsigned int addr){
  int number = 0;
  number |= (((unsigned int)read_byte(addr))<<8);
  number |= (((unsigned int)read_byte(addr+1)));
  return number;
}