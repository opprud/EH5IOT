/*
 * Project 1_Hello_World
 * Description: Blink an LED and print a message to the serial monitor
 * Author: morten opprud
 * Date: June 22, 2022
 */
#include <Math.h>
#include "myMath.hpp"

const pin_t MY_LED = D7;
int count = 0;
 

float x_b[] =
    {
#include "../data/float/x_b"
};

SYSTEM_THREAD(ENABLED);

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  pinMode(MY_LED, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  float myVar;
  // Toggle led every 400ms
  digitalWrite(MY_LED, HIGH);
  delay(200);
  digitalWrite(MY_LED, LOW);
  delay(400);

  // get variance from x_a
  cmsis_arm_variance(x_b, sizeof(x_b)/sizeof(float), &myVar);
  Serial.printf("CMSIS Variance : %f", myVar);

  // get variance from x_a
  myVar=variance(x_b, sizeof(x_b)/sizeof(float));
  Serial.printf("Normal Variance : %f", myVar);

  // Serial.printf("Len x_a : %d", sizeof(x_b)/sizeof(int));
}




