/*
 * lcd.h
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

#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED 

#include <inttypes.h>

typedef volatile unsigned char  int8;

/* Pin configurations for the display */
#define SCK_P  1
#define CS     2
#define DIO    3
#define RESET  4

/* ESPON message constants */
#define DISON 0xAF // Display on
#define DISOFF 0xAE // Display off
#define DISNOR 0xA6 // Normal display
#define DISINV 0xA7 // Inverse display
#define SLPIN 0x95 // Sleep in
#define SLPOUT 0x94 // Sleep out
#define COMSCN 0xBB // Common scan direction
#define DISCTL 0xCA // Display control
#define PASET 0x75 // Page address set
#define CASET 0x15 // Column address set
#define DATCTL 0xBC // Data scan direction, etc.
#define RGBSET8 0xCE // 256-color position set
#define RAMWR 0x5C // Writing to memory
#define RAMRD 0x5D // Reading from memory
#define PTLIN 0xA8 // Partial display in
#define PTLOUT 0xA9 // Partial display out
#define RMWIN 0xE0 // Read and modify write
#define RMWOUT 0xEE // End
#define ASCSET 0xAA // Area scroll set
#define SCSTART 0xAB // Scroll start set
#define OSCON 0xD1 // Internal oscillation on
#define OSCOFF 0xD2 // Internal osciallation off
#define PWRCTR 0x20 // Power control
#define VOLCTR 0x81 // Electronic volume control
#define VOLUP 0xD6 // Increment electronic control by 1
#define VOLDOWN 0xD7 // Decrement electronic control by 1
#define TMPGRD 0x82 // Temperature gradient set
#define EPCTIN 0xCD // Control EEPROM
#define EPCOUT 0xCC // Cancel EEPROM control
#define EPMWR 0xFC // Write into EEPROM
#define EPMRD 0xFD // Read from EEPROM
#define EPSRRD1 0x7C // Read register 1
#define EPSRRD2 0x7D // Read register 2
#define NOP 0x25 // No op

/* 12 bits(RGB) Colors */
#define BLACK 0x000
#define NAVY 0x008
#define BLUE 0x00F
#define TEAL 0x088
#define EMERALD 0x0C5
#define GREEN 0x0F0
#define CYAN 0x0FF
#define SLATE 0x244
#define INDIGO 0x408
#define TURQUOISE 0x4ED
#define OLIVE 0x682
#define MAROON 0x800
#define PURPLE 0x808
#define GRAY 0x888
#define SKYBLUE 0x8CE
#define BROWN 0xB22
#define CRIMSON 0xD13
#define ORCHID 0xD7D
#define RED 0xF00
#define MAGENTA 0xF0F
#define ORANGE 0xF40
#define PINK 0xF6A
#define CORAL 0xF75
#define SALMON 0xF87
#define GOLD 0xFD0
#define YELLOW 0xFF0
#define WHITE 0xFFF

#define SCREEN_SIZE  132

void init_lcd_screen();
void draw_filled_rectangle(int x, int y, int width, int height, int color);
void set_pixel(int color, unsigned char x, unsigned char y);
void draw_circle(int x0, int y0, int radius, int color, int lineThickness);
void draw_filled_circle(int x0, int y0, int radius, int color, int lineThickness);
void draw_semicircle(int x0, int y0, int radius, int color, int lineThickness);

#endif //SNAKE_H_INCLUDED
