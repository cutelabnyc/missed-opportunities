#include <opportunity.h>
#include <stdlib.h>

/**
 * void OP_init(opportunity_t *opportunity,
 *              uint8_t num_channels,
 *              uint8_t skip_size,
 *              uint16_t v_max,
 *              uint8_t hysteresis);
 * 
 * Allocates and sets all the default values for the module's
 * signal processing. These values originate at [/include/globals.h]
 * and should be changed there.
 * 
 * TODO: Add and describe parameters
 */
void OP_init(opportunity_t *opportunity,
             uint8_t num_channels,
             uint8_t skip_size,
             uint16_t v_max,
             uint8_t hysteresis)
{
    // Allocates the number of channels
    opportunity->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);

    // Sets all the default values from [/include/globals.h]
    opportunity->num_channels = num_channels;
    opportunity->skip_size = skip_size;
    opportunity->v_max = v_max;
    opportunity->hysteresis = hysteresis;

    // Initialize each channel
    for (int i = 0; i < num_channels; i++)
    {
        CH_init(&opportunity->channel[i],
                opportunity->skip_size,
                opportunity->v_max,
                opportunity->hysteresis);
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
}

/**
 * void OP_process(opportunity_t *opportunity, uint16_t *val, uint16_t *output)
 * 
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *opportunity, uint16_t *val, uint16_t *output)
{
    // Cycles through the channels and processes the CV sent to each channel
    for (int i = 0; i < opportunity->num_channels; i++)
    {
        CH_process(&opportunity->channel[i],
                   &val[i],
                   &output[i],
                   opportunity->skip_size,
                   opportunity->v_max,
                   opportunity->hysteresis);
    }
}