/*
 * lib.h
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
 * Date: 15/09/2014 - 03:32 PM
 *                      
 */

#ifndef AVRLIB_H_INCLUDED
#define AVRLIB_H_INCLUDED

/* PORT B Address */
#define DDRB *((volatile unsigned char*)(0x24))
#define PORTB *((volatile unsigned char*)(0x25))
#define PINB *((volatile unsigned char*)(0x23))

/* PORT C Address */
#define DDRC *((volatile unsigned char*)(0x27))
#define PORTC *((volatile unsigned char*)(0x28))
#define PINC *((volatile unsigned char*)(0x26))

/* PORT D Address */
#define DDRD *((volatile unsigned char*)(0x2A))
#define PORTD *((volatile unsigned char*)(0x2B))
#define PIND *((volatile unsigned char*)(0x29))

/* Macro to set/clear/get a bit in a port */
#define SBI(addr,bit) (addr |= (1<<bit))
#define CBI(addr,bit) (addr &= ~(1<<bit))
#define GBI(value,addr,bit) (value = (addr) & (1<<bit)))

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#endif // AVRLIB_H_INCLUDED