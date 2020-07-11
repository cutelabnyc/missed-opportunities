#include <opportunity.h>
#include <Arduino.h>

void OP_init(opportunity_t *op, uint8_t skipSize, uint16_t vmax, uint16_t hysteresis)
{
    op->_skipSize = skipSize;
    op->_open = true;
    op->_count = op->_skipSize - 1;
    op->_maxVoltage = vmax;
    op->_crossVoltage = ((vmax + 1) / 2) - 1;
    op->_lastOutput = 0;
    op->_hysteresis = hysteresis;
    op->_downThreshold = op->_crossVoltage - op->_hysteresis;
    op->_upThreshold = op->_crossVoltage + op->_hysteresis;
}

/**
 * Tear down resources associated with 'opportunity' struct
 * 
 * TODO: Add and describe parameters
 */
void OP_destroy(opportunity_t *op)
{
    // nothing to do
}

/**
 * Set the skip size
 * 
 * TODO: Add and describe parameters
 */
void OP_set_skip_size(opportunity_t *op, uint8_t skipSize)
{
    op->_skipSize = skipSize;
}

/**
 * Set the maximum voltage
 * 
 * TODO: Add and describe parameters
 */
void OP_set_max_voltage(opportunity_t *op, uint16_t vmax)
{
    op->_maxVoltage = vmax;
    op->_crossVoltage = ((vmax + 1) / 2) - 1;
    op->_downThreshold = op->_crossVoltage - op->_hysteresis;
    op->_upThreshold = op->_crossVoltage - op->_hysteresis;
}

/**
 * Set the hysteresis as an unsigned integer
 * 
 * TODO: Add and describe parameters
 */
void OP_set_hysteresis(opportunity_t *op, uint16_t hysteresis)
{
    op->_hysteresis = hysteresis;
    op->_downThreshold = op->_crossVoltage - op->_hysteresis;
    op->_upThreshold = op->_crossVoltage - op->_hysteresis;
}

/**
 * void OP_process(opportunity_t *self);
 * 
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *op, uint16_t *in, uint16_t *out)
{
    // First check if you've got a zero crossing
    uint16_t thisSample = *in;

    // Currently above threshold
    if (op->_lastOutput)
    {
        op->_lastOutput = thisSample <= op->_downThreshold ? 0 : op->_maxVoltage;
    }

    // Currently below threshold
    else
    {
        if (thisSample > op->_upThreshold)
        {
            op->_lastOutput = op->_maxVoltage;

            // Increment the count for a 0->1 transition
            op->_count++;

            // Close the op when you've counted enough zero crossings
            if (op->_count >= op->_skipSize)
            {
                op->_open = false;
                op->_count = 0;
            }
            else
            {
                op->_open = true;
            }
        }
    }

    // Moved this from main.cpp, I feel like it should
    // be in the process function
    *out <= 511 ? LOW : HIGH;

    // Write the output
    *out = op->_open ? thisSample : 0;
}
