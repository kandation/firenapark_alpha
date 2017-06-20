// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            D1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      384

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1000; // delay for half a secon
const int pixelNum = 24;
const String pattern[] = {"255000000","255255000","000255000","000255255","000000255","255000255"};
int state = 0;
String defaultRGB = "000000000";
int ledstatus[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
   Serial.begin(115200);
}

void checkStatus(int s[16]){
  for(int i = 0; i < 16; i++){
    if(s[i] == 0){
        Serial.print("LED NUMBER" );
        Serial.print(i);
        Serial.println(": CLOSE ");
    }
    else if(s[i] == 1){
        Serial.print("LED NUMBER" );
        Serial.print(i);
        Serial.println(": OPEN ");
    }  
  }  
}

void setStatus(int num , int stat){
    switch (stat){
      case 0:
        ledstatus[num] = stat;
        openSingle(num,defaultRGB);
        break;
      case 1:
        ledstatus[num] = stat;
        openSingle(num,"255255255");
        break;
    }
}

void rotateClockwise(){
     
}

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int rgbArray(String RGB,char color){
      if(color=='R'){
 //        Serial.println(RGB.substring(0,3));
        return RGB.substring(0,3).toInt();
      }
      else if(color=='G'){
//        Serial.println(RGB.substring(3,6));
        return RGB.substring(3,6).toInt();
      }
      else if(color=='B'){
//        Serial.println(RGB.substring(6,9));
        return RGB.substring(6,9).toInt();
      }
}

void multiQuadant(int num, int q1 , int q2 , int q3 , int q4 ,  String RGB){ //choose circle ,quadrant1 ,quadrant2 ,quadrant3 ,quadrant4 ,RGB
   if(q1==1){
    for(int i=num*pixelNum ; i< (num*pixelNum)+(pixelNum/4) ;i++){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B'))); 
    }
   }
   
   if(q2==1){
    for(int i=(num*pixelNum)+(pixelNum/4) ; i< (num*pixelNum)+(2*pixelNum/4) ;i++){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B'))); 
    }
   }
   
   if(q3==1){
    for(int i=(num*pixelNum)+(2*pixelNum/4) ; i< (num*pixelNum)+(3*pixelNum/4) ;i++){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
    }
   }
   
   if(q4==1){
    for(int i=(num*pixelNum)+(3*pixelNum/4) ; i< (num*pixelNum)+(pixelNum) ;i++){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B'))); // Moderately bright green color.
    }
   }
   
    pixels.show(); // This sends the updated pixel color to the hardware.

}


void quadantChoose(int num, int q , String RGB){ //choose circle ,quadrant ,RED , GREEN , BLUE
    for(int i=(num*pixelNum)+(pixelNum*(q-1)/4) ; i< (num*pixelNum)+(pixelNum*q/4) ;i++){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
       // Serial.println(i); 
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
}

void openSingle(int num , String RGB){ //choose circle ,quadrant ,RED , GREEN , BLUE
    for(int i= num*pixelNum ; i< ((num+1)*pixelNum) ;i++){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
       // Serial.println(i); 
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
}

void circleLight(int num , String RGB){
    for(int i= num*pixelNum ; i< ((num+1)*pixelNum) ;i+=3){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
        pixels.setPixelColor(i+1, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
        pixels.setPixelColor(i+2, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
       // Serial.println(i); 
        pixels.show();
        delay(100);
        pixels.setPixelColor(i, 0,0,0);
        pixels.setPixelColor(i+1, 0,0,0);
        pixels.setPixelColor(i+2, 0,0,0);
        pixels.show();
    }
       
}

void circleLightReverse(int num , String RGB){
    for(int i= ((num+1)*pixelNum) ; i> num*pixelNum ;i-=3){
        pixels.setPixelColor(i, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
        pixels.setPixelColor(i-1, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
        pixels.setPixelColor(i-2, pixels.Color(rgbArray(RGB,'R'),rgbArray(RGB,'G'),rgbArray(RGB,'B')));
       // Serial.println(i); 
        pixels.show();
        delay(100);
        pixels.setPixelColor(i, 0,0,0);
        pixels.setPixelColor(i-1, 0,0,0);
        pixels.setPixelColor(i-2, 0,0,0);
        pixels.show();
    }
       
}

/*void beepLight(int num, String RGB){
    openSingle (num , RGB);
    delay(100);
    openSingle (num , "000000000");
}*/
void loop() {
int i = 0;
while(i < 6){
  if(state == 0){
   openSingle(0,pattern[i]);
   delay(delayval); 
   openSingle(0,"000000000");
   state = 1;
   i++;
  }
  else if(state == 1){
   quadantChoose(0,i%4+1,pattern[i]);
   delay(delayval); 
   quadantChoose(0,i%4+1,"000000000");
   state = 2;
   i++;
  }
  else if(state == 2){
   quadantChoose(0,(i+1)%4+1,pattern[i]);
   delay(delayval); 
   quadantChoose(0,(i+1)%4+1,"000000000");
   state = 3;
   i++;
  }
  else if(state == 3){
   circleLight(0,pattern[i]);
   delay(delayval); 
   state = 4;
   i++;
  }
  else if(state == 4){
   circleLightReverse(0,pattern[i]);
   delay(delayval); 
   state = 0;
   i++;
  }
 
   
  //checkStatus(ledstatus);
}  
  

  

 

}
