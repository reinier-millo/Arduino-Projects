/*
 * eeprom.h
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
 
#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

/* EEPROM Registers */
#define EEARH *((volatile unsigned char*)(0x42))
#define EEARL *((volatile unsigned char*)(0x41))
#define EEAR *((volatile unsigned char*)(0x41))
#define EEDR *((volatile unsigned char*)(0x40))
#define EECR *((volatile unsigned char*)(0x3F))

/* Bits from register EECR */
#define EERE 0
#define EEPE  1
#define EEMPE 2

/* Functions to access EEPROM */
void write_byte(unsigned int addr, unsigned char data);
unsigned char read_byte(unsigned int addr);
void write_word(unsigned int addr, unsigned int data);
unsigned int read_word(unsigned int addr);

#endif // EEPROM_H_INCLUDED