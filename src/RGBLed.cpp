#include "RGBLed.hpp"

void RGBLed::begin(){
  pinMode( pinRed_ , OUTPUT );
  pinMode( pinGreen_ , OUTPUT );
  pinMode( pinBlue_ , OUTPUT );
}

void RGBLed::set_write( unsigned int* color , unsigned int bright ){
  bright_ = bright > 8u ? 8u : bright;
  red_ = color[0];
  green_ = color[1];
  blue_ = color[2];

  unsigned int print_red = map( red_ , 0 , 255 , 0 , bright_ ? 32 * bright_ - 1 : 0 );
  unsigned int print_green = map( green_ , 0 , 255 , 0 , bright_ ? 32 * bright_ -1 : 0 );
  unsigned int print_blue = map( blue_ , 0 , 255 , 0 , bright_ ? 32 * bright_ - 1 : 0 );

  analogWrite( pinRed_ , print_red );
  analogWrite( pinGreen_ , print_green );
  analogWrite( pinBlue_ , print_blue );
}

void RGBLed::write( unsigned int bright ){
  bright_ = bright > 8u ? 8u : bright;

  unsigned int print_red = map( red_ , 0 , 255 , 0 , bright_ ? 32 * bright_ - 1 : 0 );
  unsigned int print_green = map( green_ , 0 , 255 , 0 , bright_ ? 32 * bright_ -1 : 0 );
  unsigned int print_blue = map( blue_ , 0 , 255 , 0 , bright_ ? 32 * bright_ - 1 : 0 );

  analogWrite( pinRed_ , print_red );
  analogWrite( pinGreen_ , print_green );
  analogWrite( pinBlue_ , print_blue );
}
