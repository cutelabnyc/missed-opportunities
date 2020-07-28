/**
 * opportunity.h —— (Max Ardito, 07/09/20)
 *
 * Class representing the entire module's
 * functionality. Instantiated globally in
 * [/src/main.cpp], initialized, and then used
 * for CV processing in the main loop.
 */

#ifndef OPPORTUNITY_H
#define OPPORTUNITY_H

#include <channel.h>
#include <stdbool.h>
#include <cuteop.h>

/**
 * opportunity_t: Module's main data structure
 *
 * TODO: Add and describe parameters
 */
typedef struct opportunity
{
    channel_t *channel;    // Each individual I/O channel
    uint16_t *probability; // Corresponding probabilities for each I/O channel

    t_thresh _reset_thresh;
    t_edge _reset_edge;

    uint8_t num_channels;
    uint16_t v_max;
    uint8_t hysteresis;
    uint16_t random_seed;

} opportunity_t;

/**
 * Initialize the 'opportunity' struct
 *
 * TODO: Add and describe parameters
 */
void OP_init(opportunity_t *self,
             uint8_t num_channels,
             uint16_t v_max,
             uint8_t hysteresis,
             uint16_t random_seed,
             uint16_t *densities);

/**
 * Frees the 'opportunity' struct
 *
 * TODO: Add and describe parameters
 */
void OP_destroy(opportunity_t *self);

/**
 * Enable or disable mock randomization. Used for testing.
 *
 * doMock - Set true to enable mock randomization
 */
void OP_set_mock_random(opportunity_t *self, bool doMock);

/**
 * Processes the incoming CV data in main.cpp
 * [buffer_t CV_in/CV_out]
 *
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *self, uint16_t *input, uint16_t *output, uint16_t *reset);

#endif /* OPPORTUNITY_H */
