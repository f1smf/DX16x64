/*******************************************************************
* Library for Arduino Control of a Led Panel made by
* DX
*
* Copyright (C) 2013 Patrick CARON f1smf@free.fr
*
* Basic version :LibSpider16x128 Pedro Belasco pbelasco@gmail.com
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program; if not, see http://www.gnu.org/licenses
* or write to the Free Software Foundation,Inc., 51 Franklin Street,
* Fifth Floor, Boston, MA 02110-1301  USA
******************************************************************************/
/*
  Pin Mapping
  Inside the product, there is a 14 pin slot numbered as:

D-IN
	     +----+----+
	SCK  | 15 | 16 | GND
	     +---------+
	STR  | 13 | 14 | GND
	     +---------+
	R    | 11 | 12 | GND
	     +---------
	G    | 09 | 10 | GND
	     +---------+
	OE   | 07 | 08 | GND
	     +---------+
	L0   | 05 | 06 | GND
	     +---------+
	L1   | 03 | 04 | GND
	     +---------+
	L2   | 01 | 02 | L3
	     +---------+
Where, the function of each port is defined by:

  04-08-10-12-14-16. GND
  15. SCK : Serial clock pin.
  13. STR : Serial Latch pin. To write an entire line.
  11. LedR: Flag to determine Led Red
  09. LedG: Flag to determine Led Green
  07. OE  : Led On/Off
  05. L0  : Line Selector.
  03. L1  : Line Selector.
  01. L2  : Line Selector.
  02. L3  : Line Selector.
*/
#ifndef LedPanel_h
#define LedPanel_h

#include <inttypes.h>
#include "Print.h"
#include "Arduino.h"


// Fonts
#define FONT            System5x7
#define CHAR_WIDTH_5x7  2
#define CHAR_HEIGHT_5x7 3
#define FIRST_CHAR_5x7  4
#define FONT_COUNT_5x7  5
#define START_CHARS_5x7 6

// Buffer
#define TYPEOF         uint8_t
#define BITSIZE         4
#define WINDOW_W	64
#define WINDOW_H	32
#define SWITCH_L_OFF()  {PORTD &= 0b00001111;} // digital  4, 5, 6, 7 
#define LATCH(M_STR)   {PORTD |= M_STR; PORTD &= ~M_STR;}
#define CLOCK(M_SCK)   {PORTD |= M_SCK; PORTD &= ~M_SCK;}

class LedPanel {
public:
   LedPanel(uint8_t sck = 2, uint8_t str = 3, uint8_t oe0 = 8,
            uint8_t linea = 4, uint8_t lineb = 5, uint8_t linec = 6, uint8_t lined = 7,
            uint8_t ledg0  = 14, uint8_t ledr0  = 15, uint8_t ledg1  = 16, uint8_t ledr1  = 17);
     
   //  Specifies the dimensions (width and height) of the display.
   void begin();
   void SetBrightness(byte Brightness =  127);
   //  Scan buffer to serial for debug
   void scan2serial();
   void scan(int xini = 0, int yini = 0);
   void clear(byte mode= 0);
   void enqueueChar(byte c, int xPos = 0, int yPos = 0, byte color = 1);
   // Graphic functions
   void line(int x0, int y0, int x1, int y1, byte color);
   void rect(int x0, int y0, int x1, int y1, byte color);
   void circle(int xm, int ym, int r, byte color);
   void ellipse(int x0, int y0, int x1, int y1, byte color);
   void bezier(int x0, int y0, int x1, int y1, int x2, int y2, byte color);
   void SetPixel( byte x0 , byte y0, byte color);
private:
   uint8_t _sck_mask;
   uint8_t _str_mask;
   uint8_t _oe_mask;

   uint8_t _linea_mask;
   uint8_t _lineb_mask;
   uint8_t _linec_mask;
   uint8_t _lined_mask;
   uint8_t _ledr0_mask;
   uint8_t _ledg0_mask;
   uint8_t _ledr1_mask;
   uint8_t _ledg1_mask;
   int _led_Brightness;
   byte _line_lcd;
   uint8_t _buffer[WINDOW_H][WINDOW_W/4];  //Buffer Led

   void drawline(int x1, int y1, int x2, int y2, byte color);
   void setbit(TYPEOF buffer[], byte pos, byte color);
   void spitbit(byte color);
   byte readbit(TYPEOF buffer[], uint8_t pos);
//   void spireadbit(TYPEOF buffer[]);
   void spireadbit(byte h);

   void FastHLine(int x0, int y0, int x1, byte color);
   void FastVLine(int x0, int y0, int y1, byte color);

   void initPin(uint8_t *pro, uint8_t pin);
   void setuptimer(int divider=630);
   /* fast integer (1 byte) modulus */
   // http://code.google.com/p/ht1632c/wiki/Optimizations
   uint8_t _mod(byte n, byte d);
   byte _div(byte n, byte d);
   byte _rnd(byte min, byte max);
   uint8_t _pow(uint8_t a, uint8_t b);
};

#endif
// No newline at end of file
