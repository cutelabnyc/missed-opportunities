#include <opportunity.h>
#include <stdlib.h>

#define RESET_RANDOM_SEQUENCE(x) srand(x)
#define DENSITY_RANGE 1023
#define DENSITY_THRESHOLD (DENSITY_RANGE * 0.70)

static void _reset_random_sequence(opportunity_t *self, uint16_t random_seed)
{
    for (int i = 0; i < self->num_channels; i++)
    {
        CH_reset_random(self->channel + i, random_seed);
    }
}

void OP_init(opportunity_t *self,
             uint8_t num_channels,
             uint16_t v_max,
             uint8_t hysteresis,
             unsigned int random_seed)
{
    // Allocates the number of channels
    self->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);
    self->probability = (uint16_t *)malloc(sizeof(uint16_t) * num_channels);

    // NOTE: We might not need this density variable
    self->density = (uint16_t *)malloc(sizeof(uint16_t) * num_channels);

    // Initialize threshold and edge for reset seed inlet
    thresh_init(&self->_reset_thresh, (v_max / 2) - 1, hysteresis);
    edge_init(&self->_reset_edge);
    autopulse_init(&self->_autopulse);

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

        // Initialize density values
        self->density[i] = 0;

        // Initialize probability values
        self->probability[i] = 0;
    }

    // Initialize the random sequence by reseting seed
    _reset_random_sequence(self, random_seed);
}

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

static void _OP_process_reset(opportunity_t *self, uint16_t *reset)
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
        _reset_random_sequence(self, self->random_seed);
    }
}

static void _OP_process_density(opportunity_t *self, uint16_t *density)
{
    uint16_t autopulseDensity;

    // ANCHOR: If the density is greater than the lack of voltage
    // set densities based off of default value, else set densities
    // based off of incoming value

    for (int i = 0; i < self->num_channels; i++)
    {
        if (self->channel[i]._edge._last != 1)
        {
            uint16_t probability = DENSITY_THRESHOLD / (i + 1);

            if (*density < DENSITY_THRESHOLD)
            {
                self->probability[i] = probability * (*density / probability);
            }
            else
            {
                uint16_t remainder = (DENSITY_RANGE - probability);
                self->probability[i] = probability + remainder * (DENSITY_RANGE - *density / remainder);
            }
        }
    }

    autopulseDensity = *density;

    double autopulseRange = (MAX_AUTO_PPS - MIN_AUTO_PPS);
    double scaleFactor = (double)autopulseDensity / (double)self->v_max;
    autopulse_set_pulses_per_second(&self->_autopulse, scaleFactor * autopulseRange + MIN_AUTO_PPS);
}

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

void OP_process(opportunity_t *self,
                uint16_t *input,
                uint16_t *output,
                uint16_t *reset,
                uint16_t *density,
                uint16_t *autopulse,
                uint16_t msec)
{
    // Process reset input
    _OP_process_reset(self, reset);

    // Process density input
    _OP_process_density(self, density);

    // Process the automatic pulsing
    autopulse_process(&self->_autopulse, msec, autopulse);

    *autopulse = (*autopulse > 0) ? self->v_max : 0;

    // Process CV inputs
    _OP_process_CV(self, input, output);
}
