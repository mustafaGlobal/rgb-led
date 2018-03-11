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

#define STANDARD 0
#define FLASH 1
#define STROBE 2
#define FADE 3
#define SMOOTH 4


int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

unsigned int bright = 8u;
unsigned int mode = STANDARD;
unsigned int last_mode = STANDARD;
float tmp = 0.0f;

RGBLed rgb{ RED_PIN , GREEN_PIN , BLUE_PIN };

unsigned int protekloVrijeme;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  rgb.begin();
  lcd.begin(16,2);
  rgb.turn_off();
}



unsigned int decode(){

  switch( results.value ){
    case IR_BPLUS:
      if( last_mode != STANDARD )
        return 1;
      if( bright < 8u ) ++bright;
      rgb.write( bright );
      break;

    case IR_BMINUS:
      if( last_mode != STANDARD )
        return 1;
      if( bright != 1u ) --bright;
      rgb.write( bright );
      break;

    case IR_OFF:
      rgb.turn_off();
      rgb.write();
      lcd.clear();
      lcd.print("DEVICE OFF");
    break;

    case IR_ON:
      rgb.turn_on();
      bright = 8u;
      rgb.set_write( WHITE_COLOR, bright );
      lcd.clear();
      lcd.print("WHITE");
    break;

    case IR_R:
      rgb.set_write( RED_COLOR, bright );
      lcd.clear();
      lcd.print("RED");
      break;

    case IR_G:
      rgb.set_write( GREEN_COLOR, bright );
      lcd.clear();
      lcd.print("GREEN");
    break;

    case IR_B:
      rgb.set_write( BLUE_COLOR , bright );
      lcd.clear();
      lcd.print("BLUE");
    break;

    case IR_W:
    rgb.set_write( WHITE_COLOR, bright );
    lcd.clear();
    lcd.print("WHITE");
    break;

    case IR_B1:
    rgb.set_write( ORANGE_COLOR, bright );
    lcd.clear();
    lcd.print("ORANGE");
    break;

    case IR_B2:
    rgb.set_write( TURQUOISE_COLOR, bright );
    lcd.clear();
    lcd.print("TIRKIZ");
    break;

    case IR_B3:
    rgb.set_write( VIOLET_DARK_COLOR, bright );
    lcd.clear();
    lcd.print("VIIOLETNA");
    break;


    case IR_B4:
    rgb.set_write( YELLOW_COLOR, bright );
    lcd.clear();
    lcd.print("YELLOW");
    break;

    case IR_B5:
    rgb.set_write( LIGHTSKY_BLUE_COLOR, bright );
    lcd.clear();
    lcd.print("LIGHTSKY BLUE");
    break;

    case IR_B6:
    rgb.set_write( ORCHID_MEDIUM_COLOR, bright );
    lcd.clear();
    lcd.print("ORCHID MEDIUM");
    break;


    case IR_B7:
    rgb.set_write( GREEN_YELLOW_COLOR, bright );
    lcd.clear();
    lcd.print("GREEN YELLOW");
    break;

    case IR_B8:
    rgb.set_write( DODGER_BLUE_COLOR, bright );
    lcd.clear();
    lcd.print("DODGER BLUE");
    break;

    case IR_B9:
    rgb.set_write( MAGENTA_DARK_COLOR, bright );
    lcd.clear();
    lcd.print("MAGENTA");
    break;


    case IR_B10:
    rgb.set_write( LIME_GREEN_COLOR, bright );
    lcd.clear();
    lcd.print("LIME GREEN");
    break;

    case IR_B11:
    rgb.set_write( MIDNIGHT_BLUE_COLOR, bright );
    lcd.clear();
    lcd.print("MIDNIGHT BLUE");
    break;

    case IR_B12:
    rgb.set_write( PINK_DEEP_COLOR, bright );
    lcd.clear();
    lcd.print("PINK DEEP");
    break;

    default:
      return 1;

  }
  irrecv.resume();
  return 0;

}

unsigned int flash(){

  for( auto i = 0u ; i < 16u ; ++i ){
      for( auto j = 0u ; j < 3u ; ++j ){
        if (irrecv.decode(&results))
          return 1;
        rgb.set_write( COLORS[i] , bright );
        delay(300);
        rgb.set_write( BLACK_COLOR , bright );
        delay(300);
    }
  }

  return 0;
}

unsigned int strobe(){

  for( auto i = 0u ; i < 16u ; ++i ){
    if (irrecv.decode(&results))
      return 1;
    rgb.set_write( COLORS[i] , 8 );
    delay(100);
  }
  return 0;
}


unsigned int smooth(){

  if(millis()-protekloVrijeme>=350)
  {
  protekloVrijeme = millis();
  lcd.clear();
  lcd.print("SMOOTH ");
  lcd.setCursor(0,1);
  lcd.print("TEMP = ");
  lcd.print(tmp);
  lcd.print(" *C");
  }

    if( tmp < 25.0f )
      rgb.set_write( DODGER_BLUE_COLOR, 8 );
    else if( tmp < 30.0f )
      rgb.set_write( LIGHTSKY_BLUE_COLOR, 8 );
    else if( tmp < 35.0f )
      rgb.set_write( TURQUOISE_COLOR, 8 );
    else if( tmp < 40.0f )
      rgb.set_write( LIME_GREEN_COLOR, 8 );
    else if( tmp < 45.0f  )
      rgb.set_write( GREEN_YELLOW_COLOR, 8 );
    else if( tmp < 50.0f )
      rgb.set_write( YELLOW_COLOR, 8 );
    else if( tmp < 55.0f )
      rgb.set_write( ORANGE_COLOR, 8 );
    else
      rgb.set_write( RED_COLOR , 8 );
    if (irrecv.decode(&results))
      return 1;
  return 0;
}


unsigned int fade(){

  for( auto i = 7u ; i > 3u ; --i )
    rgb.set_write( WHITE_COLOR , i );
  delay(20);

  for( auto i = 6u ; i < 11u ; ++i ){
    for( auto j = 7u ; j  >  1u ; --j ){
      if (irrecv.decode(&results))
        return 1;
      rgb.set_write( COLORS[i] , bright );
      delay(17);
    }
    for( auto j = 2u ; j  <  8u ; ++j ){
      if (irrecv.decode(&results))
        return 1;
      rgb.set_write( COLORS[i] , bright );
      delay(17);
    }
  }

  for( auto i = 10u ; i > 5u ; --i ){
    for( auto j = 7u ; j  >  1u ; --j ){
      if (irrecv.decode(&results))
        return 1;
      rgb.set_write( COLORS[i] , bright );
      delay(17);
    }
    for( auto j = 2u ; j  <  8u ; ++j ){
      if (irrecv.decode(&results))
        return 1;
      rgb.set_write( COLORS[i] , bright );
      delay(17);
    }
  }
  rgb.set_write( WHITE_COLOR , 8 );
  delay(20);
  return 0;
}



void loop() {

  int temp_input = analogRead(A0);
  tmp = ( temp_input / 1024.0 ) * 500.0;

if (irrecv.decode(&results)) {

TEST:
  last_mode = mode;

  if( results.value == IR_FLASH )
    mode = FLASH;
  else if( results.value == IR_STROBE )
    mode = STROBE;
  else if( results.value == IR_FADE )
    mode = FADE;
  else if( results.value == IR_SMOOTH )
    mode = SMOOTH;
  else
    mode = STANDARD;


  if( !rgb.getState() && results.value != IR_ON ){
    irrecv.resume();
    delay(50);
    return;
  }

  if( mode == STANDARD )
    if( decode() != 0 )
      mode = last_mode;

  irrecv.resume();
}

if( rgb.getState() ){
  if( mode == FLASH){
    lcd.clear();
    lcd.print("FLASH");
    if( flash() != 0 )
      goto TEST;
  }

  if( mode == STROBE){
    lcd.clear();
    lcd.print("STROBE");
    if( strobe() != 0 )
      goto TEST;
  }

  if( mode == FADE){
    lcd.clear();
    lcd.print("FADE");
    if( fade() != 0 )
      goto TEST;
  }

  if( mode == SMOOTH){

    if( smooth() != 0 )
      goto TEST;
  }
}

  delay(100);

}
