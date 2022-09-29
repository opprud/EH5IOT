/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/au263437/workspace/hih/E5IoT/workspace/5_energy_meter/electricity_meter/src/electricity_meter.ino"
/*
 * Project electricity_meter
 * Description:
 * Author:
 * Date:
 */
void wattHourTick(void);
void responseHandler(const char *event, const char *data);
void setup();
void loop();
#line 7 "/Users/au263437/workspace/hih/E5IoT/workspace/5_energy_meter/electricity_meter/src/electricity_meter.ino"
#define LED D7

int32_t WattHours;
int32_t WattCurrent;

bool ledOn = false;
char hour, minute, second;
unsigned long tickMs, lastTickMs, tp;
String t;


/**
 * @brief isr callback, emeter give 1000pulses / Kwh, 1 pulse = 1Wh
 *
 */
void wattHourTick(void)
{
  WattHours++;

  tickMs = millis();
  tp = tickMs - lastTickMs;
  lastTickMs = tickMs;
  WattCurrent = (int32_t)3600000 / tp;

  digitalWrite(LED, ledOn);
  ledOn = !ledOn;
}

// watt calculation
// 1000W = 1KHw/hour = 1000 pulses / hour
// 1hour = 3600sec = 1 pulse every 3,6 sec
// Tp in sec 3,6=1000W, 7,2=500W
//
// X/3600ms(Tp) = 1000 --> X = 3600*1000 = 3.600.000
// Watt(Tp in millisec) = 3.6000.000/ Tp

/**
 * @brief Webhook response handler, splits incoming data separated by '~' and prints
 * response from: https://api.energidataservice.dk/datastore_search?resource_id=powersystemrightnow&limit=1
 * Response template is {{#result}}{{#records}}{{OffshoreWindPower}}~{{OnshoreWindPower}}~{{SolarPower}}{{/records}}{{/result}}
 * @param event
 * @param data
 */
void responseHandler(const char *event, const char *data)
{
  Serial.printf("\nData %s", data);
  Serial.printf("\nEvent %s", event);
#ifdef DEBUG_RESPONSE
  char *token;
  // get first separator
  token = strtok((char *)data, sep);

  /* walk through other separators */
  while (token != NULL)
  {
    Serial.printf(" %s\n", token);

    token = strtok(NULL, sep);
  }
#endif
}

// setup() runs once, when the device is first turned on.
void setup()
{
  pinMode(LED, OUTPUT);

  pinMode(D1, INPUT);
  attachInterrupt(D1, wattHourTick, RISING);
  Particle.variable("WattHours", WattHours);
  Particle.variable("WattCurrent", WattCurrent);
  Particle.variable("LedPeriodMs", tp);
  Particle.variable("TimeString", t);

  Particle.subscribe("elpris_dk", responseHandler, MY_DEVICES);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // Once an hour, get the current energy price
  if (Time.isValid())
  {
    //if (Time.hour() != hour)
    if (Time.minute() != hour)
    {
      //hour = Time.hour();
      hour = Time.minute();
      //Serial.print(Time.timeStr());
      t = String(Time.timeStr());
      Particle.publish("energyprice_dk_vest", PRIVATE);
    }
  }
}