#include "LedPanel.h"


// LedPanel init
LedPanel lp;
 
void setup () {
   Serial.begin(115200);
   pinMode(13, OUTPUT);    
   Serial.write("Power on\n");
   lp.begin();
   lp.SetBrightness(10);
}
 
char ch;
int chCnt, xpos, ypos, i, j, k = 0;
void loop () {
   
   byte LedColor;
   lp.SetBrightness(127);
   for(i=0;i<WINDOW_H;i++){
      lp.clear(0);   
      LedColor = 1;
      lp.enqueueChar((i%9)+48, 0, 0, LedColor);
      LedColor = 2;
      lp.line(10, i,  WINDOW_W-10,WINDOW_H - i, LedColor );
      LedColor = 1;
      lp.enqueueChar((i%9)+48, WINDOW_W-6, WINDOW_H -7, LedColor);
      delay(200);
   }
   lp.clear(2);   
   lp.SetBrightness(10);
   for(i=0;i<WINDOW_H;i++){
        LedColor = (i & 3);
        lp.line(0, i,  WINDOW_W-1, i, LedColor );
   }
    for(i=0;i<256;i++){
      lp.SetBrightness(i);
      delay(10);
    }
   lp.clear(1);   
   LedColor = 1;
   byte r=15;
   for(i=0; i<WINDOW_W-1-r;i++) {
      lp.rect(i,0,r+i,r, 1,LedColor);
      delay(25);
      lp.clear();
   }
   LedColor = 2;
   for(i=WINDOW_W-1-r; i>0;i--) {
      lp.rect(i,0,r+i,r,0,LedColor);
      delay(30);
      lp.clear();
   }
    
   r=7;
   for(i=0; i<WINDOW_W-1-( 2 *r);i++) {
      lp.circle(r+i, 15, r, LedColor);
      delay(20);
      lp.clear();
   }
   for(i=WINDOW_W-1-r; i>0;i--) {
      lp.circle(r+i, 15, r, LedColor);
      delay(20);
      lp.clear();
   }

   delay(50);
   lp.clear();
    
   for(i=0;i<15; i++) {
      lp.bezier(0, 0, 32+i, i, 63,0, LedColor);
      delay(50);
      lp.clear();
   } 
   for(i=15;i>0; i--) {
      lp.bezier(0, 0, 32-i, i, 63, 0, LedColor);
      delay(50);
      lp.clear();
    }
        
//    while(Serial.available()) {
//         Serial.read();
//         get the new byte:
//        int c = Serial.read();
//        if (c == 127) {
//            c = ' ';
//            if (chCnt > 0) --chCnt;
//            if (xpos > 0)  xpos -= 6;
//             lp.enqueueChar(c, xpos, ypos);
//         } else {
//             lp.enqueueChar(c, xpos, ypos, LedColor);
//             xpos += 6;
//             ++chCnt;
//             if ((chCnt%20) == 0) { ypos += 8; xpos = 0; }
//         }
//     }
    delay(100);
    
   chCnt=0; 
   xpos=0;
   ypos=0;
   for (j=0; j<96; j++) {
     lp.enqueueChar(j+32, xpos, ypos, LedColor);
     xpos += 6;
     ++chCnt;
     if ((chCnt%10) == 0) { ypos += 8; xpos = 0; }
     delay(50);
     if (ypos >= WINDOW_H) {   
       delay(200);
       lp.clear(2);
       ypos=0;
       xpos=0;
     }
   }
   delay(1000);
}

//Executes on ach TIMER1 overflow.
//Set divider in setuptimer()
ISR(TIMER1_COMPA_vect) { lp.scan(); }

