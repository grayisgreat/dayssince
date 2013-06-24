
#include <stdint.h>
#include <stdlib.h>
#include <SeeedTouchScreen.h> 

#include <TFT.h>

#ifdef SEEEDUINO
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 14   // can be a digital pin, this is A0
  #define XP 17   // can be a digital pin, this is A3 
#endif

#ifdef MEGA
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 54   // can be a digital pin, this is A0
  #define XP 57   // can be a digital pin, this is A3 
#endif 

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2

TouchScreen ts = TouchScreen(XP, YP, XM, YM);
int numDays = 0;
char buffer[3];

void setup()
{
  Tft.init();  //init TFT library
  Tft.drawString("0",90,40,10,WHITE);
  Tft.drawString("Days",0,160,4,WHITE);
  Tft.drawString("Since...",0,200,4,WHITE);
}

void loop(){
 
  Point p = ts.getPoint();
  
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
  
  // press
  if (p.z > __PRESURE) {
    numDays += 1;
    
    //special pressure points
    if(p.x > 221 && p.x < 241 && p.y > 290 && p.y < 341){
     numDays = 0;
     printScreen(0,90,10);
     return;   
    }else if(p.y > 290 && p.y < 341 && p.x < 20){
      numDays +=9; 
    }
    
    //print days
    if(numDays < 10){
       printScreen(numDays,90,10);
    }else if(numDays > 9 && numDays < 100){
       printScreen(numDays,40,10);
    }else if(numDays >= 99){
       printScreen(numDays,30,8);
    }
  }

  delay(100);
}

void printScreen(int days, int left, int hSize){
        itoa(days, buffer, 10);
        Tft.paintScreenBlack();
        Tft.drawString(buffer,left,40,hSize,WHITE);
        Tft.drawString("Days",0,160,4,WHITE);
        Tft.drawString("Since...",0,200,4,WHITE);
} 
