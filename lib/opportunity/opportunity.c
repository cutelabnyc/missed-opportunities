#include <opportunity.h>
#include <stdlib.h>

/**
 * void OP_init(opportunity_t *self,
 *              uint8_t num_channels,
 *              uint16_t v_max,
 *              uint8_t hysteresis,
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
             uint8_t *densities)
{
    // Allocates the number of channels
    self->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);
    self->probability = (probability_t *)malloc(sizeof(probability_t) * num_channels);

    // Sets all the default values from [/include/globals.h]
    self->num_channels = num_channels;
    self->v_max = v_max;
    self->hysteresis = hysteresis;

    // Initialize each channel
    for (int i = 0; i < num_channels; i++)
    {
        CH_init(&self->channel[i],
                self->v_max,
                self->hysteresis);

        PROB_init(&self->probability[i], densities[i]);
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
 * void OP_process(opportunity_t *self, uint16_t *val, uint16_t *output)
 * 
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *self, uint16_t *val, uint16_t *output)
{
    // Cycles through the channels and processes the CV sent to each channel
    for (int i = 0; i < self->num_channels; i++)
    {
        // First process the probability array
        PROB_process(&self->probability[i]);

        // Then process the channel array and send the probability gates
        CH_process(&self->channel[i],
                   &val[i],
                   &output[i],
                   self->probability[i].gate,
                   self->v_max,
                   self->hysteresis);
    }
}