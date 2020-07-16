/**
 * channel.h —— (Max Ardito, 07/09/20)
 * 
 * Class representing the entire Missed channel 
 * module's functionality. Instantiated globally in 
 * [/src/main.cpp], initialized, and then used for 
 * CV processing in the main loop.
 */

#ifndef channel_H
#define channel_H

#include <stdint.h>
#include <stdbool.h>

/**
 * channel_t:
 * 
 * Main struct for the module. 
 * TODO: Add and describe parameters
 */
typedef struct channel
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
} channel_t;

/*==========================================*/

/**
 * Initialize the 'channel' struct
 * 
 * TODO: Add and describe parameters
 */
void CH_init(channel_t *self, uint8_t skipSize, uint16_t vmax, uint16_t hysteresis);

/**
 * Tear down resources associated with 'channel' struct
 * 
 * TODO: Add and describe parameters
 */
void CH_destroy(channel_t *self);

/**
 * Set the skip size
 * 
 * TODO: Add and describe parameters
 */
void CH_set_skip_size(channel_t *self, uint8_t skipSize);

/**
 * Set the maximum voltage
 * 
 * TODO: Add and describe parameters
 */
void CH_set_max_voltage(channel_t *self, uint16_t vmax);

/**
 * Set the hysteresis as an unsigned integer
 * 
 * TODO: Add and describe parameters
 */
void CH_set_hysteresis(channel_t *self, uint16_t hysteresis);

/**
 * Process audio
 * 
 * TODO: Add and describe parameters
 */
void CH_process(channel_t *self, uint16_t *in, uint16_t *out);

#endif /* channel_H */
