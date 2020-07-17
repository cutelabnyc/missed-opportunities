#include <channel.h>
#include <stdlib.h>

/**
 * void CH_init(channel_t *self, uint8_t skipSize, uint16_t vmax, uint16_t hysteresis)
 * 
 * TODO: Add and describe parameters
 */
void CH_init(channel_t *self, uint8_t skipSize, uint16_t vmax, uint16_t hysteresis)
{
    self->_open = true;
    self->_count = skipSize - 1;
    self->_crossVoltage = ((vmax + 1) / 2) - 1;
    self->_lastOutput = 0;
    self->_downThreshold = self->_crossVoltage - hysteresis;
    self->_upThreshold = self->_crossVoltage + hysteresis;
}

/**
 * void CH_destroy(channel_t *self)
 * 
 * TODO: Add and describe parameters
 */
void CH_destroy(channel_t *self)
{
    // nothing to do
}

/**
 * void CH_process(channel_t *self,
 *                 uint16_t *in,
 *                 uint16_t *out,
 *                 uint8_t skip_size,
 *                 uint16_t v_max,
 *                 uint8_t hysteresis)
 * 
 * TODO: Add and describe parameters
 */
void CH_process(channel_t *self,
                uint16_t *in,
                uint16_t *out,
                uint8_t skip_size,
                uint16_t v_max,
                uint8_t hysteresis)
{
    // First check if you've got a zero crossing
    uint16_t thisSample = *in;

    // Currently above threshold
    if (self->_lastOutput)
    {
        self->_lastOutput = thisSample <= self->_downThreshold ? 0 : v_max;
    }

    // Currently below threshold
    else
    {
        if (thisSample > self->_upThreshold)
        {
            self->_lastOutput = v_max;

            // Increment the count for a 0->1 transition
            //self->_count++;

            // Close the self when you've counted enough zero crossings
            if (rand() & 1)
            {
                self->_open = false;
                //self->_count = 0;
            }
            else
            {
                self->_open = true;
            }
        }
    }

    // Write the output
    *out = self->_open ? thisSample : 0;

    // Check threshold
    if (*out <= 511)
        *out = 0;
}
