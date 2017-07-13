#include <string.h> //Memcpy
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
// Local Library
#include "Display.h"
#include "RGB.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif
/* ------ Configuration ------- */
#define LED_PIN D1
#define NUM_RING_ALL_PIX 384
const int NUM_RING_ONE_PIX = 24;
int DELAY_VAL = 1000;


/* ------ Intitialize --------*/
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_RING_ALL_PIX, LED_PIN, NEO_GRB + NEO_KHZ800);
void openSingle(int num, uint32_t RGB){
  for(int i= num*NUM_RING_ONE_PIX ; i< ((num+1)*NUM_RING_ONE_PIX) ;i++){
    pixels.setPixelColor(i,RGB);
  }
  //pixels.show();
 }

 void openSingleRGB(int num, byte r, byte g, byte b){
  for(int i= num*NUM_RING_ONE_PIX ; i< ((num+1)*NUM_RING_ONE_PIX) ;i++){
    pixels.setPixelColor(i,r,g,b);
  }
  //pixels.show();
 }
class DisplayRender{
  const static int map_size = 16;
public:
  byte pos[map_size];
  int color[map_size];
  char type[map_size];
  Display display_map;

  DisplayRender(Display);
  void setDisplay(Display dis){
    display_map = dis;
  }
  void updateMap();
 };

 DisplayRender::DisplayRender(Display disp){
  display_map = disp;
 }


 void DisplayRender::updateMap(){
  for(int i=0;i<16;i++){
      openSingle(i,display_map.getColorAt(i));
      //Serial.print(display_map.getColorAt(i));
      //Serial.print(";");
  }
  //Serial.println();
  pixels.show();
 }

 void ledIntitialize(){
  
 }


/* ------ Main Code --------- */
Display display = Display();
byte box[4] = {5,6,9,10};
byte box2[4] = {0,1,4,5};
byte cpe[8] = {1,2,3,5,9,13,14,15};
byte cpe2[8] = {1,2,3,7,11,13,14,15};
byte line[4] = {0,1,2,3};
byte dot[1] = {5};
DisplayRender render = DisplayRender(display);


void setup() {
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  Serial.begin(9600);

  pixels.begin();
  RGB rgb=RGB(0,0,0);
  
  
  int yyy=0;
 while(yyy<8){
  for(int i=0;i<=360;i++){
    rgb = rgb.hsl2rgb(i,100,50);
    for(int k=0;k<16;k++){
      openSingle(k,rgb.toInt32());
    }
    
    delay(1);
    pixels.show();
  }
  for(int i=360;i>=0;i--){
    rgb = rgb.hsl2rgb(i,100,50);
    for(int k=0;k<16;k++){
      openSingle(k,rgb.toInt32());
    }
    delay(1);
    pixels.show();
  }
  yyy++;
 }
  
   delay(2000);
  
  display.clear_pixel();
  display.add_pixel(box,4);
  render.setDisplay(display);
  render.updateMap();
  delay(2000);

  display.clear_pixel();
  display.add_pixel(box2,4);
  render.setDisplay(display);
  render.updateMap();
  delay(2000);
  
  display.clear_pixel();
  display.add_pixel(cpe2,8);
  render.setDisplay(display);
  render.updateMap();
  delay(2000);

  display.clear_pixel();
  display.add_pixel(cpe,8);
  render.setDisplay(display);
  render.updateMap();
  delay(1000);

  display.clear_pixel();
  display.add_pixel(line,4);
  render.setDisplay(display);
  render.updateMap();
  delay(2000);
  Serial.println("Wait");
  

}

int count = 0;
void loop(){
  render.updateMap();
  //pixels.show();

  if(count > 10){
    display.rotate_left();
    render.setDisplay(display);
   // delay(1000);
  }
  if(count %5 == 0){
    display.add_pixel(dot,1);
    render.setDisplay(display);
  }
  count++;
  
  
 delay(500);
 

}
