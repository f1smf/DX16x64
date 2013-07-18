// #include <math.h>

#include "SystemFont5x7.h"
#include "LedPanel.h"

LedPanel::LedPanel(uint8_t sck, uint8_t str, uint8_t oe,
        uint8_t linea, uint8_t lineb, uint8_t linec,
        uint8_t lined, uint8_t ledr,  uint8_t ledg)
{
   initPin(&_sck_mask , sck);
   initPin(&_str_mask , str);
   initPin(&_oe_mask  , oe);

   initPin(&_linea_mask, linea);
   initPin(&_lineb_mask, lineb);
   initPin(&_linec_mask, linec);
   initPin(&_lined_mask, lined);
   initPin(&_ledr_mask , ledr);
   initPin(&_ledg_mask , ledg);
}

void LedPanel::initPin(uint8_t *mask_pro, uint8_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    *mask_pro = _pow(2, (pin > 7 ? (pin - (_pow(8, pin / 8))) : pin));
}
void LedPanel::SetBrightness(uint8_t Brightness) {
    if (Brightness > 127)
        Brightness = 127;
    _led_Brightness = Brightness * 3;
}
/**
 * @todo: Transfer setuptimer for this
 */
void LedPanel::begin() {
    setuptimer(300);
    clear();
}

//comme [0,0] de l'ecran, les points de debut et de fin
void LedPanel::scan(int xini, int yini) {
byte i = 0;
int j = 0;
int k = 0 ;
   digitalWrite( 13, digitalRead( 13 ) ^ 1 );
   
   for(i = 0; i < WINDOW_H ; i++) {    
     fastSelectLine(i);
     for(j = 0; j < WINDOW_W; j++){
        spireadbit(_buffer[i], j);
      }
      PORTD |= _str_mask;
         asm("nop;nop;nop;nop;nop;nop;");
      PORTD &= ~_str_mask;
      PORTB &= ~_oe_mask; //pin os low
      for(k = 0; k < _led_Brightness; k++){
         asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
         asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
         asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
         asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
      }
    PORTB |= _oe_mask; // pin oe high
   }

}

// escreve status na porta 3
void LedPanel::spitbit(byte color) {
  PORTB |= _ledr_mask;  // pin ledr high
  PORTB |= _ledg_mask;  // pin ledr high
  PORTD &= ~_sck_mask;
  if (color & 0x01)
      PORTB &= ~_ledr_mask;  // pin ledr low
  if (color & 0x02)
       PORTB &= ~_ledg_mask;  // pin ledr low
   PORTD |= _sck_mask;
}

// Selectionne une ligne en fonction
// des pins L0, L1, L2, L3
void LedPanel::fastSelectLine(uint8_t n) {
   SWITCH_L_OFF();
   if (n & 0x01) PORTD |= _linea_mask; //4
   if (n & 0x02) PORTD |= _lineb_mask; //5
   if (n & 0x04) PORTD |= _linec_mask; //6
   if (n & 0x08) PORTD |= _lined_mask; //7
}

void LedPanel::clear(byte mode) {
   byte i,j,k;
   if (mode ==1) {
      for (j = 0; j < WINDOW_W; j++) {
         for (i = 0; i < WINDOW_H ; i++) {
            if ( i & 1 ) { 
              for (k = 0; k < WINDOW_W - 1; k++) {
                 setbit(_buffer[i],k,(readbit(_buffer[i],k + 1)));
                 if (k==(WINDOW_W - 2)) setbit(_buffer[i],(WINDOW_W -1) ,0);
              }
            }
            else {
              for (k = WINDOW_W-1; k > 0; k--) {
                 setbit(_buffer[i],k,(readbit(_buffer[i],k - 1)));
                 if (k==1) setbit(_buffer[i],0,0);
              }
            }
         }
         delay(2);
      }    
   }
   for (j = 0; j < WINDOW_H; j++) {
      for (i = 0; i < WINDOW_W/BITSIZE; i++)
      _buffer[j][i] = 0;
    }
}

void LedPanel::spireadbit(TYPEOF buffer[], byte pos) {
   uint8_t tmp1 = pos & 3;
   uint8_t tmp2 = pos >> 2;
   PORTB |= _ledr_mask;  // pin ledr high
   PORTB |= _ledg_mask;  // pin ledr high
   PORTD &= ~_sck_mask;
   if (buffer[tmp2] & (0x80 >> (tmp1)))
      PORTB &= ~_ledr_mask;  // pin ledr low
   if (buffer[tmp2] & (0x08 >> (tmp1)))
       PORTB &= ~_ledg_mask;  // pin ledr low
   PORTD |= _sck_mask;
}

void LedPanel::enqueueChar(byte c, int xPos, int yPos, byte color) {
  byte j, i;                                            //bitmask and iterators
   uint8_t off = pgm_read_byte (FONT + FIRST_CHAR_5x7); //offset of charset
   uint8_t w = pgm_read_byte (FONT + CHAR_WIDTH_5x7);   //char width
   uint8_t h = pgm_read_byte (FONT + CHAR_HEIGHT_5x7);  //char height
   int zc = int(FONT) + START_CHARS_5x7;	        //index of 0 char
   for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
         if (pgm_read_byte(zc+((c-off)*w)+j) & (1<<i)) 
            setbit(_buffer[i+yPos],j+xPos,color);
      }
   }
}


void LedPanel::SetPixel( byte x0, byte y0,byte color) {
  if ((x0 >= WINDOW_W) || (y0 >=  WINDOW_H)) 
     return;
  setbit(_buffer[y0], x0, color);
}

byte LedPanel::readbit(TYPEOF buffer[], byte pos) {
   if (pos > WINDOW_W) return(0);
   uint8_t tmp = 0;
   uint8_t tmp1 = pos & 3;
   uint8_t tmp2 = pos >> 2;

   if (buffer[tmp2] & (0x80 >> (tmp1)))
      tmp = 1;
   if (buffer[tmp2] & (0x08 >> (tmp1)))
      tmp += 2;
   return (tmp);
}

void LedPanel::setbit(TYPEOF buffer[], byte pos, byte color ) {
   uint8_t tmp1 = _mod(pos, BITSIZE);
   uint8_t tmp2 = _div(pos, BITSIZE);
   buffer[tmp2]  &=  ~(0x80 >> tmp1);
   buffer[tmp2]  &=  ~(0x08 >> tmp1); 
   if (color & 0x01)      //LEd red
      buffer[tmp2] |=  (0x80 >> tmp1);
   if (color & 0x02)      //LEd Green
      buffer[tmp2] |=  (0x08 >> tmp1);
}

/**
 * Math fast functions
 */
byte LedPanel::_mod(byte n, byte d) {
   while(n >= d) n -= d;
   return n;
}

/* fast integer (1 byte) division */
byte LedPanel::_div(byte n, byte d) {
   byte q = 0;
   while(n >= d) {
      n -= d;
      q++;
   }
   return q;
}

byte LedPanel::_rnd(byte min, byte max) {
   static byte seed;
   seed = (21 * seed + 21);
   return min + _mod(seed, --max);
}

uint8_t LedPanel::_pow(uint8_t a, uint8_t b) {
   if (b==0) return 1;
   if (a==0) return 0;
   if (b%2==0) { return _pow(a * a, b/2); }
   else if (b%2==1) { return a * _pow(a * a, b/2); }
   return 0;
}

/* graphic primitives based on Bresenham's algorithms */
void LedPanel::line(int x0, int y0, int x1, int y1, byte color) {
   int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
   int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
   int err = dx + dy, e2; /* error value e_xy */
   for(;;) {
      if ( (x0 < WINDOW_W) && (y0 < WINDOW_H))
         setbit(_buffer[y0], x0, color);
      if (x0 == x1 && y0 == y1) break;
      if ( (x0 > WINDOW_W) || (y0 > WINDOW_H)) break;
      e2 = 2 * err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

void LedPanel::rect(int x0, int y0, int x1, int y1, byte color) {
   line(x0, y0, x0, y1, color); /* left line   */
   line(x1, y0, x1, y1, color); /* right line  */
   line(x0, y0, x1, y0, color); /* top line    */
   line(x0, y1, x1, y1, color); /* bottom line */
}

void LedPanel::circle(int xm, int ym, int r, byte color) {
   int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
   do {
      if ( ((xm - x) < WINDOW_W) && ((ym + y) < WINDOW_H))
         setbit(_buffer[ym + y], xm - x, color); /*   I. Quadrant */

      if ( ((xm - y) < WINDOW_W) && ((ym - x) < WINDOW_H))
         setbit(_buffer[ym - x], xm - y, color); /*  II. Quadrant */

      if ( ((xm + x) < WINDOW_W) && ((ym - y) < WINDOW_H))
         setbit(_buffer[ym - y], xm + x, color); /* III. Quadrant */

      if ( ((xm + y) < WINDOW_W) && ((ym + x) < WINDOW_H))
         setbit(_buffer[ym + x], xm + y, color); /*  IV. Quadrant */

      r = err;
      if (r >  x) err += ++x * 2 + 1; /* e_xy+e_x > 0 */
      if (r <= y) err += ++y * 2 + 1; /* e_xy+e_y < 0 */
   } while (x < 0);
}

void LedPanel::ellipse(int x0, int y0, int x1, int y1, byte color) {
   int a    = abs(x1 - x0), b = abs(y1 - y0), b1 = b & 1; /* values of diameter */
   long dx  = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; /* error increment */
   long err = dx + dy + b1 * a * a, e2; /* error of 1.step */

   if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
   if (y0 > y1) y0 = y1; /* .. exchange them */
   y0 += (b + 1) / 2; /* starting pixel */
   y1 = y0 - b1;
   a *= 8 * a;
   b1 = 8 * b * b;

   do {

      setbit(_buffer[y0], x1, color); /*   I. Quadrant */
      setbit(_buffer[y0], x0, color); /*  II. Quadrant */
      setbit(_buffer[y1], x0, color); /* III. Quadrant */
      setbit(_buffer[y1], x1, color); /*  IV. Quadrant */

      e2 = 2 * err;
      if (e2 >= dx) { x0++; x1--; err += dx += b1; } /* x step */
      if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
   } while (x0 <= x1);

   while (y0 - y1 < b) {  /* too early stop of flat ellipses a=1 */
      setbit(_buffer[++y0], x0 - 1, color); /* -> complete tip of ellipse */
      setbit(_buffer[--y1], x0 - 1, color);
   }
}

void LedPanel::bezier(int x0, int y0, int x1, int y1, int x2, int y2, byte color) {
   int sx = x0 < x2 ? 1 : -1, sy = y0 < y2 ? 1 : -1; /* step direction */
   int cur = sx * sy * ((x0 - x1) * (y2 - y1) - (x2 - x1) * (y0 - y1)); /* curvature */
   int x = x0 - 2 * x1 + x2, y = y0 - 2 * y1 + y2, xy = 2 * x * y * sx * sy;
                                  /* compute error increments of P0 */
   long dx = (1 - 2 * abs(x0 - x1)) * y * y + abs(y0 - y1) * xy - 2 * cur * abs(y0 - y2);
   long dy = (1 - 2 * abs(y0 - y1)) * x * x + abs(x0 - x1) * xy + 2 * cur * abs(x0 - x2);
                                  /* compute error increments of P2 */
   long ex = (1 - 2 * abs(x2 - x1)) * y * y + abs(y2 - y1) * xy + 2 * cur * abs(y0 - y2);
   long ey = (1 - 2 * abs(y2 - y1)) * x * x + abs(x2 - x1) * xy - 2 * cur * abs(x0 - x2);

   if (cur == 0) { line(x0, y0, x2, y2, color); return; } /* straight line */

   x *= 2 * x; y *= 2 * y;
   if (cur < 0) {                             /* negated curvature */
      x = -x; dx = -dx; ex = -ex; xy = -xy;
      y = -y; dy = -dy; ey = -ey;
   }
   /* algorithm fails for almost straight line, check error values */
   if (dx >= -y || dy <= -x || ex <= -y || ey >= -x) {
      line(x0, y0, x1, y1, color);                /* simple approximation */
      return;
   }
   dx -= xy; ex = dx+dy; dy -= xy;              /* error of 1.step */

   for(;;) {                                         /* plot curve */
      setbit(_buffer[y0], x0, color);
      ey = 2 * ex - dy;                /* save value for test of y step */
      if (2 * ex >= dx) {                                   /* x step */
         if (x0 == x2) break;
         x0 += sx; dy -= xy; ex += dx += y;
      }
      if (ey <= 0) {                                      /* y step */
         if (y0 == y2) break;
         y0 += sy; dx -= xy; ex += dy += x;
      }
   }
}

// initialize Timer1
void LedPanel::setuptimer(int divider) {
   cli();           // disable global interrupts

   TCCR1A = 0;      // set entire TCCR1A register to 0
   TCCR1B = 0;      // same for TCCR1B
   OCR1A = divider; // set compare match register to desired timer count:

   TCCR1B |= (1 << WGM12);  // turn on CTC mode:
   TCCR1B |= (1 << CS10);   // Set CS10 and CS12 bits for 1024 prescaler:
   TCCR1B |= (1 << CS12);   // Set ONLY CS12 bits for 256 prescaler:
   TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt:

   sei(); // enable global interrupts:
}

// Scan buffer to serial for debug
void LedPanel::scan2serial() {
   int i, j = 0;
   byte tmp;
   for(i = 0; i < WINDOW_H; i++) {
       Serial.print("Line");
       Serial.print(i);
       Serial.print(" : ");

      for(j=0; j < WINDOW_W; j++){
        tmp = readbit(_buffer[i], j);
         Serial.print(tmp,HEX);
      }
      Serial.print('\n');
   }
   Serial.print('\n');
}
