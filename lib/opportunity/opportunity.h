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

#ifdef __cplusplus
extern "C" {
#endif

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
    uint16_t _lastSample;
    uint16_t _maxVoltage;
    uint16_t _crossVoltage; // should be maxVoltage / 2
} opportunity_t;

/*==========================================*/

/**
 * Initialize the 'opportunity' struct
 * 
 * TODO: Add and describe parameters
 */
void OP_init(opportunity_t *op, uint8_t skipSize, uint16_t vmax);

/**
 * Tear down resources associated with 'opportunity' struct
 * 
 * TODO: Add and describe parameters
 */
void OP_destroy(opportunity_t *op);

/**
 * Set the skip size
 * 
 * TODO: Add and describe parameters
 */
void OP_set_skip_size(opportunity_t *op, uint8_t skipSize);

/**
 * Set the maximum voltage
 * 
 * TODO: Add and describe parameters
 */
void OP_set_max_voltage(opportunity_t *op, uint16_t vmax);

/**
 * Process audio
 * 
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *op, uint16_t *in, uint16_t *out);

#ifdef __cplusplus
}
#endif

#endif /* OPPORTUNITY_H */
