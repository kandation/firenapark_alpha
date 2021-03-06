#include "Display.h"
#include <Arduino.h>

Display::Display(){
  for(int i=0;i<globalconfig.MAP_SIZE;i++){
    color[i] = 0;
    type[i] = 0;
  }  
}

int Display::int2hex(int R, int G, int B){
  return (R<<16)|(G<<8)|B;
}

void Display::add_pixel(byte value[], int arrSize){
/*
 * add pixel by position array and fill by defualt color
 */
  for(int i=0;i<arrSize;i++){
    pos[value[i]] = value[i];
    // White color
    color[value[i]] = int2hex(255,50,0);
  }  
}
void Display::add_pixel(byte value[], int rgb_color[], int arrSize){
/*
 * add pixel by position array and color mapping 
 */
  for(int i=0;i<arrSize;i++){
    pos[value[i]] = value[i];
    color[value[i]] = int2hex(rgb_color[0],rgb_color[1],rgb_color[2]);
    //memo:\ Fix color[] to One ring system not 
  }  
}
void Display::add_pixel_clear(byte value[]){
/*
 * add pixel by position array and color mapping 
 */
  for(int i=0;i<16;i++){
    if(value[i] != 0){
      pos[i] = value[i];
      color[i] = int2hex(255,50,0);
    }else{
      pos[i] = 0;
      color[i] = int2hex(0,0,0);
    }
    
  }  
}

template <typename rotate_arr_pos>
void Display::rotation(rotate_arr_pos arrValue){
  byte temp_pos[globalconfig.MAP_SIZE];
  int temp_color[globalconfig.MAP_SIZE];
  char temp_type[globalconfig.MAP_SIZE];
  for(int i=0; i<globalconfig.MAP_SIZE; i++){
    // Algo; In position 1 goto see box 13 and write down to temp
    temp_pos[i] = pos[arrValue[i]];
    //Serial.print(pos[i]);
    //Serial.print("n=");
    //Serial.print(temp_pos[i]);
    temp_color[i] = color[arrValue[i]];
    temp_type[i] = type[arrValue[i]];
  }
  for(int i=0; i<globalconfig.MAP_SIZE; i++){
    // Algo; In position 1 goto see box 13 and write down to temp
    pos[i] = temp_pos[i];
    color[i] = temp_color[i];
    type[i] = temp_type[i];
  }
  //Serial.print("_________________");
  for(int i=0;i<16;i++){
    //Serial.print(temp_pos[i]);
  }//Serial.println();
 
}

void Display::rotate_left(){
  rotation(rotation_left_grid);  
}

void Display::rotate_right(){
  rotation(rotation_left_grid);  
}

void Display::clear_pixel(){
  for(int i=0;i<globalconfig.MAP_SIZE;i++){
    pos[i] = 0;
    color[i] = 0;
    type[i] = 0;
  }
}

