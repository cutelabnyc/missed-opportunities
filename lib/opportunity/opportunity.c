#include <opportunity.h>
#include <Arduino.h>

#define ANALOG_IN A3   // ANALOG A5, A4, A3, A2
#define DIGITAL_OUT 10 // DIGITAL 3, 9, 10, 11
#define LED_PIN 13

opportunity_t *OP_init(void)
{
    // TODO: Eventually this will malloc()
    // additional memory?
    opportunity_t *self = malloc(sizeof(void));

    self->cv_in = 0;
    self->cv_out = 0;
    self->isGated = false;

    self->zeroCrossing = false;

    return self;
}

void OP_setPins()
{
    pinMode(ANALOG_IN, INPUT);
    pinMode(DIGITAL_OUT, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void OP_read(opportunity_t *self)
{
    // Sets input CV value to struct varibale
    self->cv_in = analogRead(ANALOG_IN);
}

void OP_process(opportunity_t *self)
{
    self->cv_out = self->cv_in;
}

void OP_write(opportunity_t *self)
{
    digitalWrite(DIGITAL_OUT, self->cv_out);
}
