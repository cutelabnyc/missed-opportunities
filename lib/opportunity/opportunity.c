#include <opportunity.h>

void OP_init(opportunity_t *op, uint8_t skipSize, uint16_t vmax)
{
    op->_skipSize = skipSize;
    op->_open = true;
    op->_count = op->_skipSize - 1;
    op->_maxVoltage = vmax;
    op->_crossVoltage = ((vmax + 1) / 2) - 1;
    op->_lastSample = op->_crossVoltage;

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
    if (op->_lastSample <= op->_crossVoltage && thisSample > op->_crossVoltage) {
        op->_count++;

        // Close the op when you've counted enough zero crossings
        if (op->_count >= op->_skipSize) {
            op->_open = false;
            op->_count = 0;
        } else {
            op->_open = true;
        }
    }

    // Set the last sample
    op->_lastSample = thisSample;

    // Write the output
    *out = op->_open ? thisSample : 0;
}
