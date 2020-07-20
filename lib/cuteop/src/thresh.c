#include "thresh.h"

void thresh_init(t_thresh *self, uint16_t cutoff, uint16_t hysteresis)
{
    self->_cutoff = cutoff;
    self->_lastOutput = 0;
    self->_downThreshold = self->_cutoff - hysteresis;
    self->_upThreshold = self->_cutoff + hysteresis;
}

void thresh_process(t_thresh *self, uint16_t *in, uint16_t *out)
{
    // First check if you've got a zero crossing
    uint16_t thisSample = *in;

    // Currently above threshold
    if (self->_lastOutput > 0)
    {
        self->_lastOutput = thisSample <= self->_downThreshold ? 0 : 1;
    }

    // Currently below threshold
    else
    {
        if (thisSample > self->_upThreshold)
        {
            self->_lastOutput = 1;
        }
    }

    // Write the output
    *out = self->_lastOutput;
}
