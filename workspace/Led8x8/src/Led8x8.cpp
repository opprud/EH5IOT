/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/au263437/workspace/hih/E5IoT/workspace/Led8x8/src/Led8x8.ino"
/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
//#include <Adafruit_GFX.h>
#include "adafruit-led-backpack.h"

void setup();
void loop();
void loop();
#line 26 "/Users/au263437/workspace/hih/E5IoT/workspace/Led8x8/src/Led8x8.ino"
Adafruit_8x8matrix m1 = Adafruit_8x8matrix();
Adafruit_8x8matrix m2 = Adafruit_8x8matrix();

void setup()
{
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test.");
  /*
    matrix[0] = Adafruit_8x8matrix();
    m2 = Adafruit_8x8matrix();

    matrix[0].begin(0x71); // pass in the address
    m2.begin(0x70); // pass in the address
  */
  m1.begin(0x71); // pass in the address
  m2.begin(0x70); // pass in the address

  Particle.syncTime();
  Time.zone(+2);
}
void loop()
{
  static char last_min, last_sec;
  char min, sec;
  m1.setTextSize(1);
  m1.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
  m1.setTextColor(LED_ON);
  m2.setTextSize(1);
  m2.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
  m2.setTextColor(LED_ON);

  // format time string, extract Hour, Minuts seconds
  char ts[10];

  min = Time.minute();
  sec = Time.second();
  if (min != last_min)
  {
    last_min = min;
    for (int8_t x = 0; x >= -31; x--)
    {
      sprintf(ts, "%02d:%02d:%02d", Time.hour(), Time.minute(), Time.second());
      m1.clear();
      m1.setCursor(x, 0);
      m1.print(ts);
      m1.writeDisplay();
      m2.clear();
      m2.setCursor(x - 8, 0);
      m2.print(ts);
      m2.writeDisplay();
      delay(100);
    }
  }
  else if (sec != last_sec)
  {
    sprintf(ts, "%02d:%02d:%02d", Time.hour(), Time.minute(), Time.second());

    m1.clear();
    m1.setCursor(-31, 0);
    m1.print(ts);
    m1.writeDisplay();
    m2.clear();
    m2.setCursor(-39, 0);
    m2.print(ts);
    m2.writeDisplay();
  }
}

#if 0
static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {
  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();      // clear display
  matrix.drawPixel(0, 0, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawLine(0,0, 7,7, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0,0, 8,8, LED_ON);
  matrix.fillRect(2,2, 4,4, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3,3, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
matrix.setRotation(3);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("World");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
#endif