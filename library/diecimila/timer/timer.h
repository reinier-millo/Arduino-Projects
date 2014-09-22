/*
 * timer.h
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
 * Date: 19/09/2014 - 10:46 AM
 *                      
 */
 
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

/* Timer1 Registers */
#define TCCR1B *((volatile unsigned char*)(0x81))
#define TIMSK1 *((volatile unsigned char*)(0x6F))
#define OCR1A *((volatile unsigned char*)(0x88))

/* Bit register TIMSK1 */
#define OCIE1A 1

/* Bit register TCCR1B */
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

#endif // TIMER_H_INCLUDED