#include <Arduino.h>

// Extern for all the local C headers
extern "C"
{
#include "opportunity.h"
}

// TODO: Rename these struct variables lol
opportunity_t *block = OP_init();

void setup()
{
  pinMode(ANALOG_IN, INPUT);
  pinMode(DIGITAL_OUT, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  OP_read(block, analogRead(ANALOG_IN));
  digitalWrite(DIGITAL_OUT, block->cv_out);
}