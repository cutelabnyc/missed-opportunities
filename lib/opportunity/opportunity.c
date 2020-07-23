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
             uint16_t *densities)
{
    // Allocates the number of channels
    self->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);
    self->probability = (uint16_t *)malloc(sizeof(uint16_t) * num_channels);

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

void OP_set_mock_random(opportunity_t *self, bool doMock)
{
	for (int i = 0; i < self->num_channels; i++)
		CH_set_mock_random(&self->channel[i], doMock);
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
        // Process the channel array and send the probability gates
        CH_process(&self->channel[i],
                   &val[i],
				   &self->probability[i],
                   &output[i]);
    }
}
