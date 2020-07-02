#include "../include/init.h"

// TODO: Rename these struct variables lol
opportunity_t *op_cv = OP_init();

void setup()
{
  pinMode(ANALOG_IN, INPUT);
  pinMode(DIGITAL_OUT, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(ANALOG_IN));
  OP_read(op_cv, analogRead(ANALOG_IN));
  digitalWrite(DIGITAL_OUT, op_cv->cv_out);
}

/**====================================*/
opportunity_t *OP_init(void)
{
  // TODO: Eventually this will malloc() all
  // the space needed
  opportunity_t *self = {0}; //= malloc(sizeof(opportunity_t));

  return self;
}

void OP_read(opportunity *opt, uint16_t cv_in)
{
  if (cv_in > INPUT_THRESHOLD)
    opt->cv_out = HIGH;
  else
    opt->cv_out = LOW;
}