#include <channel.h>

void CH_init(channel_t *self, uint8_t skipSize, uint16_t vmax, uint16_t hysteresis)
{
    self->_skipSize = skipSize;
    self->_open = true;
    self->_count = self->_skipSize - 1;
    self->_maxVoltage = vmax;
    self->_crossVoltage = ((vmax + 1) / 2) - 1;
    self->_lastOutput = 0;
    self->_hysteresis = hysteresis;
    self->_downThreshold = self->_crossVoltage - self->_hysteresis;
    self->_upThreshold = self->_crossVoltage + self->_hysteresis;
}

/**
 * Tear down resources associated with 'channel' struct
 * 
 * TODO: Add and describe parameters
 */
void CH_destroy(channel_t *self)
{
    // nothing to do
}

/**
 * Set the skip size
 * 
 * TODO: Add and describe parameters
 */
void CH_set_skip_size(channel_t *self, uint8_t skipSize)
{
    self->_skipSize = skipSize;
}

/**
 * Set the maximum voltage
 * 
 * TODO: Add and describe parameters
 */
void CH_set_max_voltage(channel_t *self, uint16_t vmax)
{
    self->_maxVoltage = vmax;
    self->_crossVoltage = ((vmax + 1) / 2) - 1;
    self->_downThreshold = self->_crossVoltage - self->_hysteresis;
    self->_upThreshold = self->_crossVoltage - self->_hysteresis;
}

/**
 * Set the hysteresis as an unsigned integer
 * 
 * TODO: Add and describe parameters
 */
void CH_set_hysteresis(channel_t *self, uint16_t hysteresis)
{
    self->_hysteresis = hysteresis;
    self->_downThreshold = self->_crossVoltage - self->_hysteresis;
    self->_upThreshold = self->_crossVoltage - self->_hysteresis;
}

/**
 * void CH_process(channel_t *self);
 * 
 * TODO: Add and describe parameters
 */
void CH_process(channel_t *self, uint16_t *in, uint16_t *out)
{
    // First check if you've got a zero crossing
    uint16_t thisSample = *in;

    // Currently above threshold
    if (self->_lastOutput)
    {
        self->_lastOutput = thisSample <= self->_downThreshold ? 0 : self->_maxVoltage;
    }

    // Currently below threshold
    else
    {
        if (thisSample > self->_upThreshold)
        {
            self->_lastOutput = self->_maxVoltage;

            // Increment the count for a 0->1 transition
            self->_count++;

            // Close the self when you've counted enough zero crossings
            if (self->_count >= self->_skipSize)
            {
                self->_open = false;
                self->_count = 0;
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
