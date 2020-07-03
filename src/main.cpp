#include "../include/init.h"

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
  Serial.println(block->cv_out);
}

/**====================================*/
opportunity_t *OP_init(void)
{
  // TODO: Eventually this will malloc() all
  // the space needed
  opportunity_t *self = {0}; //= malloc(sizeof(opportunity_t));

  return self;
}

void OP_read(opportunity *self, uint16_t cv_in)
{
  // TODO: Next time, uncomment below and check
  // if the alternation is good

  // Flip gate for zero-crossing
  //if (cv_in == 0)
  //{
  //  opt->isGated = !opt->isGated;
  //}

  // Detect zero crossing
  //if (opt->isGated == false)
  //{
  self->cv_out = cv_in;
  //}
  //else
  //{
  //  opt->cv_out = 0;
  //}
}
