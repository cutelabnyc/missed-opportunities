#include <opportunity.h>
#include <stdlib.h>

#define RESET_SEED_SEQUENCE(x) srand(x)

/**
 * void OP_init(opportunity_t *self,
 *              uint8_t num_channels,
 *              uint16_t v_max,
 *              uint8_t hysteresis,
 *              uint16_t random_seed
 *              uint8_t *densities);
 *
 * Allocates and sets all the default values for the module's
 * signal processing. These values originate at [/include/globals.h]
 * and should be changed there.
 *
 * TODO: Add and describe parameters
 */
void OP_init(opportunity_t *self,
             uint8_t num_channels,
             uint16_t v_max,
             uint8_t hysteresis,
             uint16_t random_seed,
             uint16_t *densities)
{
    // Allocates the number of channels
    self->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);
    self->probability = (uint16_t *)malloc(sizeof(uint16_t) * num_channels);

    // Initialize threshold and edge for reset seed inlet
    thresh_init(&self->_reset_thresh, (v_max / 2) - 1, hysteresis);
    edge_init(&self->_reset_edge);

    // Sets all the default values from [/include/globals.h]
    self->num_channels = num_channels;
    self->v_max = v_max;
    self->hysteresis = hysteresis;
    self->random_seed = random_seed;

    // Initialize each channel
    for (int i = 0; i < num_channels; i++)
    {
        CH_init(&self->channel[i],
                self->v_max,
                self->hysteresis,
                self->random_seed);

        self->probability[i] = densities[i];
    }
}

/**
 * void OP_destroy(opportunity_t *self);
 *
 * TODO: Add and describe parameters
 */
void OP_destroy(opportunity_t *self)
{
    free(self->channel);
    free(self->probability);
}

/**
 * void OP_set_mock_random(opportunity_t *self, bool doMock)
 *
 * TODO: Add and describe parameters
 */
void OP_set_mock_random(opportunity_t *self, bool doMock)
{
    for (int i = 0; i < self->num_channels; i++)
        CH_set_mock_random(&self->channel[i], doMock);
}

/**
 * static void _OP_process_reset(opportunity_t *self, uint16_t *reset)
 *
 * TODO: Add and describe parameters
 */
static bool _OP_process_reset(opportunity_t *self, uint16_t *reset)
{
    // Threshold the input to +/- 2.5V
    uint16_t postThresh;
    thresh_process(&self->_reset_thresh, reset, &postThresh);

    // // Convert to 0 -> 1 transition
    uint16_t postEdge;
    edge_process(&self->_reset_edge, &postThresh, &postEdge);

    // // Reset random value sequence if an edge is detected from reset inlet
    if (postEdge)
    {
        RESET_SEED_SEQUENCE(self->random_seed);
        return 1;
    }
    else
        return 0;
}

/**
 * static void _OP_process_CV(opportunity_t *self, uint16_t *input, uint16_t *output)
 *
 * TODO: Add and describe parameters
 */
static void _OP_process_CV(opportunity_t *self, uint16_t *input, uint16_t *output)
{
    // Cycles through the channels and processes the CV sent to each channel
    for (int i = 0; i < self->num_channels; i++)
    {
        // Process the channel array and send the probability gates
        CH_process(&self->channel[i],
                   &input[i],
                   &self->probability[i],
                   &output[i]);
    }
}

/**
 * void OP_process(opportunity_t *self, uint16_t *input, uint16_t *output, uint16_t reset)
 *
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *self, uint16_t *input, uint16_t *output, uint16_t *reset)
{
    // Process reset input
    _OP_process_reset(self, reset);

    // Process CV inputs
    _OP_process_CV(self, input, output);
    //}
}
