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
      LedColor = 1;
      lp.enqueueChar((i%9)+48, xpos, ypos, LedColor);
      LedColor = 2;
      lp.line(10, i,  WINDOW_W-10,WINDOW_H - i, LedColor );
      LedColor = 1;
      lp.enqueueChar((i%9)+48, 58, 8, LedColor);
      delay(100);
      lp.clear(0);   
   }
   lp.SetBrightness(10);
   for(i=0;i<WINDOW_H;i++){
//      lp.enqueueChar((i%8)+48, xpos, ypos, LedColor);
        LedColor = (i & 3);
        lp.line(0, i,  WINDOW_W-1, i, LedColor );
//        delay(50);
   }
    for(i=0;i<127;i++){
      lp.SetBrightness(i);
      delay(10);
    }
   lp.clear(1);   
   LedColor = 1;
   byte r=15;
   for(i=0; i<WINDOW_W-1-r;i++) {
      lp.rect(i,0,r+i,r, LedColor);
      delay(5);
      lp.clear();
   }
   LedColor = 2;
   for(i=WINDOW_W-1-r; i>0;i--) {
      lp.rect(i,0,r+i,r,LedColor);
      delay(5);
      lp.clear();
   }
    
   r=7;
   for(i=0; i<WINDOW_W-1-r;i++) {
      lp.circle(r+i, r, r, LedColor);
      delay(5);
      lp.clear();
   }
   for(i=WINDOW_W-1-r; i>0;i--) {
      lp.circle(r+i, r, r, LedColor);
      delay(5);
      lp.clear();
   }
    
   delay(50);
   lp.clear();
    
   for(i=0;i<15; i++) {
      lp.bezier(0, 0, 64+i, i, 127,0, LedColor);
      delay(50);
      lp.clear();
   } 
   for(i=15;i>0; i--) {
      lp.bezier(0, 0, 64-i, i, 127, 0, LedColor);
      delay(50);
      lp.clear();
    }
        
    // while(Serial.available()) {
    //     // Serial.read();
    //     // get the new byte:
    //     int c = Serial.read();
    //     if (c == 127) {
    //         c = ' ';
    //         if (chCnt > 0) --chCnt;
    //         if (xpos > 0)  xpos -= 6;
    //         lp.enqueueChar(c, xpos, ypos);
    //     } else {
    //         lp.enqueueChar(c, xpos, ypos, LedColor);
    //         xpos += 6;
    //         ++chCnt;
    //         if ((chCnt%20) == 0) { ypos += 8; xpos = 0; }
    //     }
    // }
    // delay(100);
    
    // lp.scan2serial();
   /* 
   xpos=0;
   ypos=0;
   for (j=0; j<36; j++) {
      for (i=j+20;i<j+60;i++) {
         lp.enqueueChar(i, xpos, ypos, LedColor);
         xpos += 6;
         ++chCnt;
         if ((chCnt%20) == 0) { ypos += 8; xpos = 0; }
         delay(50);
         lp.clear();
      }
   }
 */
  
  //lp.scan2serial();
 //  delay(1000);
   
}

//Executes on ach TIMER1 overflow.
//Set divider in setuptimer()
ISR(TIMER1_COMPA_vect) { lp.scan(); }

