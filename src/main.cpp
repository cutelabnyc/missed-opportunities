#include <Arduino.h>

// Extern for all the local C headers
extern "C"
{
#include "opportunity.h"
}

opportunity_t *block;

void setup()
{
  OP_setPins();
  block = OP_init();

  Serial.begin(9600);
}

void loop()
{
  OP_read(block);
  OP_process(block);
  OP_write(block);
}