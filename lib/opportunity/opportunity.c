#include <opportunity.h>
#include <stdlib.h>

void OP_init(opportunity_t *opportunity,
             uint8_t num_channels,
             uint8_t skip_size,
             uint16_t v_max,
             uint8_t hysteresis)
{
    // Allocate number of channels
    opportunity->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);

    opportunity->num_channels = num_channels;

    // Initialize channels
    for (int i = 0; i < num_channels; i++)
    {
        CH_init(&opportunity->channel[i], skip_size, v_max, hysteresis);
    }
}

void OP_process(opportunity_t *opportunity, uint16_t *val, uint16_t *output)
{
    for (int i = 0; i < opportunity->num_channels; i++)
    {
        CH_process(&opportunity->channel[i], &val[i], &output[i]);
    }
}