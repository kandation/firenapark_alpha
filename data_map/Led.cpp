#include "Led.h"
#include <Arduino.h>

Led::Led(){
  this->_r = 0;
  this->_g = 0;
  this->_b = 0;
  this->_w = 0;
}
Led::Led(byte r, byte g, byte b){
  this->_r = r;
  this->_g = g;
  this->_b = b;
  this->_w = 0;
}
Led::Led(byte r, byte g, byte b, byte w){
  this->_r = 0;
  this->_g = 0;
  this->_b = 0;
  this->_w = 0;
  
}

uint32_t Led::hsl(uint16_t ih, uint8_t is, uint8_t il) {
  /*
   * H is HUE range(0,360)
   * S i stu
  */
  float h, s, l, t1, t2, tr, tg, tb;
  uint8_t r, g, b;

  h = (ih % 360) / 360.0;
  s = constrain(is, 0, 100) / 100.0;
  l = constrain(il, 0, 100) / 100.0;

  if ( s == 0 ) { 
    r = g = b = 255 * l;
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  } 
  
  if ( l < 0.5 ) t1 = l * (1.0 + s);
  else t1 = l + s - l * s;
  
  t2 = 2 * l - t1;
  tr = h + 1/3.0;
  tg = h;
  tb = h - 1/3.0;

  r = hsl_convert(tr, t1, t2);
  g = hsl_convert(tg, t1, t2);
  b = hsl_convert(tb, t1, t2);

  // NeoPixel packed RGB color
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

