/**
 * channel.h —— (Max Ardito, 07/16/20)
 * 
 * Structure containing processing variables for
 * each individual channel. This includes threshold and
 * gating, but also the individual [probability_t] structs
 * for each channel.
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * channel_t: Struct containing CV threshold variables
 * and unique [probability_t] data for each I/O channel
 * 
 * TODO: Add and describe parameters
 */
typedef struct channel
{
    bool _open;
    uint16_t _lastOutput;
    uint16_t _crossVoltage; // should be maxVoltage / 2
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
 * Process a single element in the incoming [buffer_t] array
 * in main.cpp
 * 
 * TODO: Add and describe parameters
 */
void CH_process(channel_t *self,
                uint16_t *in,
                uint16_t *out,
                bool prob,
                uint8_t skip_size,
                uint16_t v_max,
                uint8_t hysteresis);

#endif /* CHANNEL_H */
