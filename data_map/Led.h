#ifndef LED_H
#define LED_H
#include <Arduino.h>

class Led{
  private:
    byte _r;
    byte _g;
    byte _b;
    byte _w;
  public:
    Led();
    Led(byte,byte,byte);
    Led(byte,byte,byte,byte);
    Led::hsl(uint16_t, uint8_t, uint8_t);
};

#endif
