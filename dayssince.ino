
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
  
  // press
  if (p.z > __PRESURE) {
     if(numDays < 9){
        printScreen(90,10);
     }else if(numDays > 8 && numDays < 99){
        printScreen(40,10);
     }else if(numDays >= 99){
        printScreen(30,8);
     }
  }

  delay(100);
}

void printScreen(int left, int hSize){
        numDays += 1;
        itoa(numDays, buffer, 10);
        Tft.paintScreenBlack();
        Tft.drawString(buffer,left,40,hSize,WHITE);
        Tft.drawString("Days",0,160,4,WHITE);
        Tft.drawString("Since...",0,200,4,WHITE);
} 
