#include <Arduino.h>

#define ANALOG_IN A5
#define DIGITAL_OUT 9
#define LED_PIN 13

void setup()
{
  pinMode(ANALOG_IN, INPUT);
  pinMode(DIGITAL_OUT, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

/*
CV IO Cookbook:
1. Take in analog input
2. Compute the average
*/
void loop()
{
  bool cv_in;
  //val = analogRead(analogIn);
  if (analogRead(ANALOG_IN) > 300)
  {
    cv_in = HIGH;
  }
  else
  {
    cv_in = LOW;
  }
  digitalWrite(DIGITAL_OUT, cv_in);
}
