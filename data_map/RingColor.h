#include "RGB.h"

#ifndef RINGCOLOR_H
#define RINGCOLOR_H
class RingColor{
  RGB rgb;
  char type;

  public:
  RingColor();
  RingColor(byte, byte, byte);
};
#endif
