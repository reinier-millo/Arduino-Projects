/*
 * usart.h
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
 * Date: 17/09/2014 - 03:39 PM
 *                      
 */

#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

// USART Registers
#define UBRR0H *((volatile unsigned char*)(0xC5))
#define UBRR0L *((volatile unsigned char*)(0xC4))
#define UCSR0B *((volatile unsigned char*)(0xC1))
#define UCSR0C *((volatile unsigned char*)(0xC2))
#define UCSR0A *((volatile unsigned char*)(0xC0))

#define UDR0  *((volatile unsigned char*)(0xC6))

// Bits UCSR0B
#define RXEN0 4
#define TXEN0 3
#define RXC0 7
#define TXC0 6

// Bits UCSR0C 
#define USBS0 3
#define UCSZ00 1

// Bits UCSR0A
#define UDRE0 5

#define FOSC 16000000
#define BAUD 9600
#define MYUBBRR FOSC/16/BAUD-1

void init_usart(unsigned int ubrr);
void transmit_usart( unsigned char data );
unsigned char receive_usart( void );
void transmit_usart_int(unsigned int data);

#endif // USART_H_INCLUDED
