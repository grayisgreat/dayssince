
#include <stdint.h>
#include <stdlib.h>
#include <SeeedTouchScreen.h> 
#include <TFT.h>
#include <SoftwareSerial.h>

#ifdef SEEEDUINO
  #define YP A2   // A2 must be an analog pin, use "An" notation!
  #define XM A1   // A1 must be an analog pin, use "An" notation!
  #define YM 14   // 14 can be a digital pin, this is A0
  #define XP 17   // 17 can be a digital pin, this is A3 
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
int bluetoothTx = 18;  //A4 matches jumper
int bluetoothRx = 19;  //A5 atches jumper
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup(){
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
  Tft.init();
  Tft.drawString("0",90,40,10,WHITE);
  Tft.drawString("Days",0,160,4,WHITE);
  Tft.drawString("Since...",0,200,4,WHITE);
}

void loop(){
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()){
    char toSend = (char)bluetooth.read();
    
    switch (toSend) {
      case 'd':    
        zeroScale("DAVE!"); 
        Tft.drawString("DAVE!",0,240,4,RED);
        break;
      case 'm':    
        zeroScale("MARTY!"); 
        Tft.drawString("MARTY!",0,240,4,RED);
        break;
      case 'a':    
        zeroScale("ARJAY!"); 
        Tft.drawString("ARJAY!",0,240,4,RED);
        break;
      case 'n':    
        zeroScale("ANDREA!"); 
        Tft.drawString("ANDREA!",0,240,4,RED);
        break;
      case 'r':    
        zeroScale("ROBIN!"); 
        Tft.drawString("ROBIN!",0,240,4,RED);
        break;
      case '+':    
        numDays += 1;
        printScreen(numDays);
        break;  
      case '-':    
        if(numDays > 0){
          numDays -= 1;
          printScreen(numDays);
        }
        break;  
      case 'x':    
        numDays += 10;
        printScreen(numDays);
        break;        
      default:
        break;
    }
  }
  
//    Point p = ts.getPoint();
//    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
//    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
//    
//    // press
//    if (p.z > __PRESURE) {
//      if(p.y > 290 && p.y < 341 && p.x < 20){
//        numDays +=10; 
//        printScreen(numDays);
//      }else if(p.y < 20 && p.x < 20){
//        numDays +=1;
//       printScreen(numDays); 
//      }
//    }
}

void printScreen(int days){
  int left = 0;
  if(days < 10){
     left=90;
  }else if(numDays > 9 && numDays < 100){
     left=40;
  }else if(numDays >= 99){
    left=30;
  }
  
  itoa(days, buffer, 10);
  Tft.paintScreenBlack();
  Tft.drawString(buffer,left,40,10,WHITE);
  Tft.drawString("Days",0,160,4,WHITE);
  Tft.drawString("Since...",0,200,4,WHITE);
} 

void zeroScale(String who){
      char wBuff[10];
      who.toCharArray(wBuff, 10); 
      numDays = 0;
      printScreen(0);
//      Tft.drawString("DAVE!",0,240,4,RED);
}
