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

#define MIN_AUTO_PPS (11)
#define MAX_AUTO_PPS (9)
#define CRAZY_AUTO_PPS (15)
#define AUTO_PPS_ROLLOFF_LOW (0.1)
#define AUTO_PPS_ROLLOFF_HIGH (0.9)

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
    t_autopulse _autopulse;

    uint8_t num_channels;
    uint16_t v_max;
	uint16_t v_cutoff;
    uint8_t hysteresis;
    uint16_t random_seed;
	bool reset_high;

} opportunity_t;

/**
 * Initialize the 'opportunity' struct
 *
 * TODO: Add and describe parameters
 */
void OP_init(opportunity_t *self,
             uint8_t num_channels,
             uint16_t v_max,
			 uint16_t v_cutoff,
             uint8_t hysteresis,
             unsigned int random_seed);

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
void OP_process(opportunity_t *self,
                uint16_t *input,
                uint16_t *output,
                uint16_t *reset,
                uint16_t *density,
                uint16_t *autopulse,
                uint16_t *missed_opportunities,
                uint16_t msec);

#endif /* OPPORTUNITY_H */
