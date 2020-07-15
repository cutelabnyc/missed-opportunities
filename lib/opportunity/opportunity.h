/**
 * opportunity.h —— (Max Ardito, 07/09/20)
 * 
 * Class representing the entire Missed Opportunity 
 * module's functionality. Instantiated globally in 
 * [/src/main.cpp], initialized, and then used for 
 * CV processing in the main loop.
 */

#ifndef OPPORTUNITY_H
#define OPPORTUNITY_H

#include <stdint.h>
#include <stdbool.h>

/**
 * opportunity_t:
 * 
 * Main struct for the module. 
 * TODO: Add and describe parameters
 */
typedef struct opportunity
{
    bool _open;
    uint8_t _skipSize;
    uint8_t _count;
    uint16_t _lastOutput;
    uint16_t _maxVoltage;
    uint16_t _crossVoltage; // should be maxVoltage / 2
    uint16_t _hysteresis;
    uint16_t _downThreshold;
    uint16_t _upThreshold;
} opportunity_t;

/*==========================================*/

/**
 * Initialize the 'opportunity' struct
 * 
 * TODO: Add and describe parameters
 */
void OP_init(opportunity_t *self, uint8_t skipSize, uint16_t vmax, uint16_t hysteresis);

/**
 * Tear down resources associated with 'opportunity' struct
 * 
 * TODO: Add and describe parameters
 */
void OP_destroy(opportunity_t *self);

/**
 * Set the skip size
 * 
 * TODO: Add and describe parameters
 */
void OP_set_skip_size(opportunity_t *self, uint8_t skipSize);

/**
 * Set the maximum voltage
 * 
 * TODO: Add and describe parameters
 */
void OP_set_max_voltage(opportunity_t *self, uint16_t vmax);

/**
 * Set the hysteresis as an unsigned integer
 * 
 * TODO: Add and describe parameters
 */
void OP_set_hysteresis(opportunity_t *self, uint16_t hysteresis);

/**
 * Process audio
 * 
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *self, uint16_t *in, uint16_t *out);

#endif /* OPPORTUNITY_H */
