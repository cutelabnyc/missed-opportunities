#include <channel.h>

typedef struct opportunity
{
    channel_t *channel; // TODO: Should be a pointer, init num channels

    uint8_t num_channels;
} opportunity_t;

void OP_init(opportunity_t *opportunity,
             uint8_t num_channels,
             uint8_t skip_size,
             uint16_t v_max,
             uint8_t hysteresis);

void OP_process(opportunity_t *opportunity, uint16_t *val, uint16_t *output);
