/*
 * usart.c
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

#include "usart.h"

#include <stdlib.h>
#include <string.h>

/**
 * Initialize the USART
 */
void init_usart(unsigned int ubrr)
{
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  
  /*Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

/**
 * Transmit a single character over the USART
 */
void transmit_usart( unsigned char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

/**
 * Receive a single character from the USART
 */
unsigned char receive_usart( void )
{
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) );
  
  /* Get and return received data from buffer */
  return UDR0;
}

/**
 * Transmit an unsigned number over the USART
 */
void transmit_usart_word(unsigned int data )
{
  char pointer[20];
  int size;
  int i;
  itoa(data,pointer,10);
  size=strlen(pointer);
  for(i=0; i<size; ++i)
    transmit_usart(pointer[i]);
}