/*
 * lcd.c
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
 * Copyright (C) 2014 Christophe Scholliers
 * Copyright (C) 2014 Reinier Millo Sánchez <rmillo@uclv.cu>
 *                    Universidad Central "Marta Abreu" de Las Villas
 * 
 * Date: 17/09/2014 - 04:10 PM
 *                      
 */

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "../lib.h"

/*
  ___________________.___  __________                __                      .__
 /   _____/\______   \   | \______   \_______  _____/  |_  ____   ____  ____ |  |
 \_____  \  |     ___/   |  |     ___/\_  __ \/  _ \   __\/  _ \_/ ___\/  _ \|  |
 /        \ |    |   |   |  |    |     |  | \(  <_> )  | (  <_> )  \__(  <_> )  |__
/_______  / |____|   |___|  |____|     |__|   \____/|__|  \____/ \___  >____/|____/
 \/                                                           \/
 */

void pulsePin(int pin)
{
  CBI(PORTB,pin);
  SBI(PORTB,pin);
  CBI(PORTB,pin);
}

void sendSPIData(int data)
{
  CBI(PORTB,CS);
  int mask=1<<8;
  while (mask>0){
    if(data & mask)
      SBI(PORTB,DIO);
    else
      CBI(PORTB,DIO);
    pulsePin(SCK_P);
    mask = mask >>1 ;
  }
  SBI(PORTB,CS);
}

void writeLCDCommand(int command)
{
  sendSPIData(command & (~(1<<8)));
}

void writeLCDData(int data)
{
  sendSPIData(data | ((1<<8)));
}

/*
________  .__               .__                
\______ \ |__| ____________ |  | _____  ___.__.
 |    |  \|  |/  ___/\____ \|  | \__  \<   |  |
 |    `   \  |\___ \ |  |_> >  |__/ __ \\___  |
/_______  /__/____  >|   __/|____(____  / ____|
        \/        \/ |__|             \/\/
*/

/**
 * Initialize LCD display connected to PORTB
 */
void init_lcd_screen()
{
  //Initalize the display pins as output 
  SBI(DDRB, RESET);
  SBI(DDRB, DIO);
  SBI(DDRB, SCK_P);
  SBI(DDRB, CS);

  CBI(PORTB,SCK_P);          // CLK = LOW
  CBI(PORTB,DIO);            // DIO = LOW
  _delay_ms(10);             // 10us delay
  SBI(PORTB,CS);             // CS = HIGH
 _delay_ms(10);              // 10uS Delay

  CBI(PORTB,RESET);          // RESET = LOW
  _delay_ms(200);            // 200ms delay
  SBI(PORTB,RESET);          // RESET = HIGH
  _delay_ms(200);            // 200ms delay
  SBI(PORTB,SCK_P);          // SCK_P = HIGH
  SBI(PORTB,DIO);            // DIO = HIGH

  writeLCDCommand(DISCTL);   // Display control (0xCA)
  writeLCDData(0x00);
  writeLCDData(0x20);
  writeLCDData(0x00);
  		
  writeLCDCommand(COMSCN);   // common scanning direction (0xBB)
  writeLCDData(0x01);        // 1->68, 132<-69 scan direction
  		
  writeLCDCommand(OSCON);    // internal oscialltor ON (0xD1)
  writeLCDCommand(SLPOUT);   // sleep out (0x94)
  
  writeLCDCommand(VOLCTR);   // electronic volume, this is the contrast/brightness (0x81)
  writeLCDData(32);          // volume (contrast) setting - fine tuning, original (0-63)
  writeLCDData(3);           // internal resistor ratio - coarse adjustment (0-7)
  		
  writeLCDCommand(PWRCTR);   // power ctrl (0x20)
  writeLCDData(0xf);         // everything on, no external reference resistors
  		
  writeLCDCommand(DISINV);   // invert display mode (0xA7)
  		
  writeLCDCommand(DATCTL);   // data control (0xBC)
  writeLCDData(0x01);        // Inverse page address, reverse rotation column address, column scan-direction !!! try 0x01
  writeLCDData(0x00);        // normal RGB arrangement
  writeLCDData(0x02);        // 16-bit Grayscale Type A (12-bit color)
  		
  writeLCDCommand(NOP);      // nop (0x25)
  writeLCDCommand(DISON);    // display on (0xAF) */
}

/**
 * Draw a filled rectangle on the screen
 */
void draw_filled_rectangle(int x, int y, int width, int height, int color)
{
  int x2=  x+width;
  int y2 = y+height;
  int i  = (width*height);
  int index;
  writeLCDCommand(PASET);
  writeLCDData(x);
  writeLCDData(x2);
  writeLCDCommand(CASET);
  writeLCDData(y);
  writeLCDData(y2);
  writeLCDCommand(RAMWR);         
  for(index=0; index<i; index++) {
    writeLCDData((color >> 4) & 0xFF); 
    writeLCDData(((color & 0xF) << 4) | ((color >> 8) & 0xF)); 
    writeLCDData(color & 0xFF); 
  }
}

/**
 * Draw a pixel on the screen
 */
void set_pixel(int color, unsigned char x, unsigned char y)
{
  y	=	(SCREEN_SIZE - 1) - y;
  x = (SCREEN_SIZE - 1) - x;
  writeLCDCommand(PASET); // page start/end ram
  writeLCDData(x);
  writeLCDData(132);
  writeLCDCommand(CASET); // column start/end ram
  writeLCDData(y);
  writeLCDData(130);
  writeLCDCommand(RAMWR); // write
  writeLCDData((color>>4)&0x00FF);
  writeLCDData(((color&0x0F)<<4)|(color>>8));
  writeLCDData(color&0x0FF);
}

/**
 * Draw an empty circle on the screen
 */
void draw_circle(int x0, int y0, int radius, int color, int lineThickness)
{
  int r;
  if(lineThickness == 0) lineThickness = radius;
  for(r = 0; r < lineThickness; r++)
  {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    set_pixel(color, x0, y0 + radius);
    set_pixel(color, x0, y0 - radius);
    set_pixel(color, x0 + radius, y0);
    set_pixel(color, x0 - radius, y0);
    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;
      set_pixel(color, x0 + x, y0 + y);
      set_pixel(color, x0 - x, y0 + y);
      set_pixel(color, x0 + x, y0 - y);
      set_pixel(color, x0 - x, y0 - y);
      set_pixel(color, x0 + y, y0 + x);
      set_pixel(color, x0 - y, y0 + x);
      set_pixel(color, x0 + y, y0 - x);
      set_pixel(color, x0 - y, y0 - x);
    }
    radius--;
  }
}

/**
 * Draw a filled circle on the screen
 */
void draw_filled_circle(int x0, int y0, int radius, int color, int lineThickness)
{
  int i;
  for(i=radius; i>=0; --i)
    draw_circle(x0,y0,i,color,lineThickness);
}

/**
 * Draw a semicircle on the screen
 */
void draw_semicircle (int x0, int y0, int radius, int color, int lineThickness)
{
  int r;
  if(lineThickness == 0) lineThickness = radius;
  for(r = 0; r < lineThickness; r++)
  {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    set_pixel(color, x0, y0 + radius);
    set_pixel(color, x0, y0 - radius);
    //setPixel(color, x0 + radius, y0);
    set_pixel(color, x0 - radius, y0);
    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;
      //set_pixel(color, x0 + x, y0 + y);
      set_pixel(color, x0 - x, y0 + y);
      //set_pixel(color, x0 + x, y0 - y);
      set_pixel(color, x0 - x, y0 - y);
      //set_pixel(color, x0 + y, y0 + x);
      set_pixel(color, x0 - y, y0 + x);
      //set_pixel(color, x0 + y, y0 - x);
      set_pixel(color, x0 - y, y0 - x);
    }
    radius--;
  }
}