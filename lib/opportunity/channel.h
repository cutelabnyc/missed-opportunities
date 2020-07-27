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
#include <cuteop.h>
#include <stdbool.h>

/**
 * channel_t: Struct containing CV threshold variables
 * and unique [probability_t] data for each I/O channel
 *
 * TODO: Add and describe parameters
 */
typedef struct channel
{
    t_thresh _input_thresh;
    t_gate _gate;
    t_random _random;
    t_edge _edge;
    t_thresh _random_thresh;
} channel_t;

/*==========================================*/

/**
 * Initialize the 'channel' struct
 *
 * TODO: Add and describe parameters
 */
void CH_init(channel_t *self, uint16_t v_max, uint16_t hysteresis);

/**
 * Tear down resources associated with 'channel' struct
 *
 * TODO: Add and describe parameters
 */
void CH_destroy(channel_t *self);

/**
 * Enable or disable mock randomization. Used for testing.
 *
 * doMock - Set true to enable mock randomization
 */
void CH_set_mock_random(channel_t *self, bool doMock);

/**
 * Process a single element in the incoming [buffer_t] array
 * in main.cpp
 *
 * TODO: Add and describe parameters
 */
void CH_process(channel_t *self,
                uint16_t *in,
                uint16_t *prob,
                uint16_t reset,
                uint16_t *out);

#endif /* CHANNEL_H */
