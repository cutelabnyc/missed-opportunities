#include "opportunity.h"
#include <Arduino.h>

opportunity_t *OP_init(void)
{
    // TODO: Eventually this will malloc() all
    // the space needed
    opportunity_t *self = {0}; //= malloc(sizeof(opportunity_t));

    return self;
}

void OP_read(opportunity_t *self, uint16_t cv_in)
{
    // TODO: Next time, uncomment below and check
    // if the alternation is good

    // Flip gate for zero-crossing
    self->cv_in = cv_in;

    //bool isZeroCrossing = (self->cv_in == 0 && self->cv_in != self->cv_out);

    // Toggle zero crossing on enter
    //if (isZeroCrossing)
    ///    self->isGated = true;

    //  If the output is not gated, copy IO
    //if (!self->isGated)
    //   self->cv_out = self->cv_in;
}
