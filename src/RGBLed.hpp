#ifndef RGBLED_HPP
#define RGBLED_HPP

#include<Arduino.h>

class RGBLed{
  public:
    RGBLed( unsigned int pinRed , unsigned int pinGreen , unsigned int pinBlue ):
      pinRed_{ pinRed },
      pinGreen_{ pinGreen },
      pinBlue_ { pinBlue } {}

    void begin();
    void set_write( unsigned int* color , unsigned int bright = 8u );
    void write( unsigned int bright );
    void write();
    void turn_on(){ on_off_state_ = true; }
    void turn_off(){ on_off_state_ = false; }
    bool getState(){ return on_off_state_; }

  private:
    unsigned int red_ = 255u;
    unsigned int green_ = 255u;
    unsigned int blue_ = 255u;

    unsigned int pinRed_;
    unsigned int pinGreen_;
    unsigned int pinBlue_;

    unsigned int bright_ = 8u;
    bool on_off_state_ = true;
};

#endif
