#include <opportunity.h>
#include <stdlib.h>
#include <Arduino.h>

void OP_init(opportunity_t *opportunity,
             uint8_t num_channels,
             uint16_t skip_size,
             uint8_t v_max,
             uint16_t hysteresis)
{
    // Allocate number of channels
    opportunity->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);

    // Initialize channels
    for (int i = 0; i < num_channels; i++)
    {
        CH_init(&opportunity->channel[i], skip_size, v_max, hysteresis);
    }
}

void OP_process(opportunity_t *opportunity, uint16_t *val, uint16_t *output)
{
    uint8_t num_channels = 4; //sizeof(opportunity->channel) / sizeof(channel_t);

    for (int i = 0; i < num_channels; i++)
    {
        CH_process(&opportunity->channel[i], &val[i], &output[i]);
    }
}