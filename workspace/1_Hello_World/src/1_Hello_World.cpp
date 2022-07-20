/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/au263437/workspace/hih/E5IoT/workspace/1_Hello_World/src/1_Hello_World.ino"
/*
 * Project 1_Hello_World
 * Description: Blink an LED and print a message to the serial monitor
 * Author: morten opprud
 * Date: June 22, 2022
 */

void setup();
void loop();
#line 8 "/Users/au263437/workspace/hih/E5IoT/workspace/1_Hello_World/src/1_Hello_World.ino"
const pin_t MY_LED = D7;
int count = 0;

SYSTEM_THREAD(ENABLED); 

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(MY_LED, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // Toggle led every 400ms
  digitalWrite(MY_LED, HIGH);
  delay(400);
  digitalWrite(MY_LED, LOW);
  delay(400);
  // increment count var, print to serial port
  count++;
  Serial.printf("Count: %d", count);
}