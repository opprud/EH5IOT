/*
 * Project webhook_renewableenergy
 * Description:
 * Author:
 * Date:
 */

int led = D7; // The on-board LED

/**
 * @brief Webhook response handler, splits incoming data separated by '~' and prints
 * Response template is {{#result}}{{#records}}{{OffshoreWindPower}}~{{OnshoreWindPower}}~{{SolarPower}}{{/records}}{{/result}}
 * @param event
 * @param data
 */
void responseHandler(const char *event, const char *data)
{

  int offshoreWindMW, onshoreWindMW, solarMW;

   // split the response (data) using the separator '~' inserted in the webhook builder
  offshoreWindMW = atoi(strtok((char*)data,"~"));
  onshoreWindMW = atoi(strtok(NULL,"~"));
  solarMW = atoi(strtok(NULL,"~"));

  Serial.printf("\n===== Renewable energy production in Denmark ====");
  Serial.printf("\n\tOffshore wind \t : %d [MW]\n\tOnshore wind \t : %d [MW]\n\tSolar energy \t : %d [MW]",offshoreWindMW, onshoreWindMW, solarMW);

#ifdef DEBUG_RESPONSE
  char *token;
  // get first separator
  token = strtok((char*)data, sep);

  /* walk through other separators */
  while (token != NULL)
  {
    Serial.printf(" %s\n", token);

    token = strtok(NULL, sep);
  }
#endif
}

void setup()
{
  pinMode(led, OUTPUT);

  // Subscribe to the webhook response event
  // Particle.subscribe("hook-response/renewable/0", responseHandler);
  Particle.subscribe("renewable", responseHandler, MY_DEVICES);

  Serial.printf("webhook demo...");
}

void loop()
{
  digitalWrite(led, HIGH); // Turn ON the LED

  Particle.publish("dk_renewable_production", PRIVATE);
  delay(30000); // Wait for 30 seconds

  digitalWrite(led, LOW); // Turn OFF the LED
  delay(30000);           // Wait for 30 seconds
}