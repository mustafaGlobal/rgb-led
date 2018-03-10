#include <Arduino.h>
#include <LiquidCrystal.h>
#include "boje.hpp"
#include "daljinski.hpp"
#include "RGBLed.hpp"
#include <IRremote.h>


//const int rs = 7, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(7,11,2,3,4,5);

#define RED_PIN 6
#define GREEN_PIN 9
#define BLUE_PIN 10



int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

unsigned int bright = 8u;

RGBLed rgb{ RED_PIN , GREEN_PIN , BLUE_PIN };

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  rgb.begin();
  lcd.begin(16,2);
}

void loop() {

//  int temp_input = analogRead(A0);
  //float temp = ( temp_input / 1024.0 ) * 500.0;



if (irrecv.decode(&results)) {

  switch( results.value ){
    case IR_BPLUS:
      if( bright < 8u ) ++bright;
      rgb.write( bright );
      break;

    case IR_BMINUS:
      if( bright != 0u ) --bright;
      rgb.write( bright );
      break;

    case IR_OFF:

    break;
    case IR_ON:

    break;
    case IR_R:
      rgb.set_write( RED_COLOR, bright );
      lcd.clear();
      lcd.print("RED");
      break;

    case IR_G:
      rgb.set_write( GREEN_COLOR, bright );
      lcd.clear();
      lcd.print("green");
    break;

    case IR_B:
      rgb.set_write( BLUE_COLOR , bright );
      lcd.clear();
      lcd.print("blue");
    break;

    case IR_W:
    rgb.set_write( WHITE_COLOR, bright );
    lcd.clear();
    lcd.print("white");
    break;

    case IR_B1:
    rgb.set_write( ORANGE_COLOR, bright );
    lcd.clear();
    lcd.print("orange");
    break;
    case IR_B2:
    rgb.set_write( TURQUOISE_COLOR, bright );
    lcd.clear();
    lcd.print("tirkiz");
    break;
    case IR_B3:
    rgb.set_write( VIOLET_DARK_COLOR, bright );
    lcd.clear();
    lcd.print("violet");
    break;
    case IR_FLASH:
    rgb.set_write( YELLOW_COLOR, bright );
    lcd.clear();
    lcd.print("yellow");
    break;
    case IR_B4:
    rgb.set_write( YELLOW_COLOR, bright );
    lcd.clear();
    lcd.print("yellow");
    break;
    case IR_B5:
    rgb.set_write( LIGHTSKY_BLUE_COLOR, bright );
    lcd.clear();
    lcd.print("l blue");
    break;
    case IR_B6:
    rgb.set_write( ORCHID_MEDIUM_COLOR, bright );
    lcd.clear();
    lcd.print("orchid med");
    break;
    case IR_STROBE:
    rgb.set_write( WHITE_COLOR, bright );
    break;
    case IR_B7:
    rgb.set_write( GREEN_YELLOW_COLOR, bright );
    lcd.clear();
    lcd.print("green yel");
    break;
    case IR_B8:
    rgb.set_write( DODGER_BLUE_COLOR, bright );
    lcd.clear();
    lcd.print("dd blue");
    break;
    case IR_B9:
    rgb.set_write( MAGENTA_DARK_COLOR, bright );
    lcd.clear();
    lcd.print("magenta");
    break;
    case IR_FADE:
    rgb.set_write( WHITE_COLOR, bright );
    lcd.clear();
    lcd.print("Rfade");
    break;
    case IR_B10:
    rgb.set_write( LIME_GREEN_COLOR, bright );
    lcd.clear();
    lcd.print("lime green");
    break;
    case IR_B11:
    rgb.set_write( MIDNIGHT_BLUE_COLOR, bright );
    lcd.clear();
    lcd.print("midnigtlbue");
    break;
    case IR_B12:
    rgb.set_write( PINK_DEEP_COLOR, bright );
    lcd.clear();
    lcd.print("pink deep");
    break;
    case IR_SMOOTH:
    rgb.set_write( WHITE_COLOR, bright );
    break;
  }

  irrecv.resume();
}

  delay(100);



}
