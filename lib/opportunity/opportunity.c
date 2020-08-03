#include <stdlib.h>
#include <opportunity.h>

#define RANDOM_SEED 42
#define RESET_RANDOM_SEQUENCE(x) srand(x)

void OP_init(opportunity_t *self,
			 uint8_t num_channels,
			 uint16_t v_max,
			 uint8_t hysteresis,
			 uint16_t *densities,
			 unsigned int random_seed)
{
	// Allocates the number of channels
	self->channel = (channel_t *)malloc(sizeof(channel_t) * num_channels);
	self->probability = (uint16_t *)malloc(sizeof(uint16_t) * num_channels);
	self->default_densities = (uint16_t *)malloc(sizeof(uint16_t) * num_channels);

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

		// Save default densities for later use if probability inlet is used
		self->default_densities[i] = densities[i];

		// Set default densities as active probabilities
		self->probability[i] = densities[i];
	}

	// Initialize the random sequence by reseting seed
	RESET_RANDOM_SEQUENCE(random_seed);
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
		RESET_RANDOM_SEQUENCE(self->random_seed);
	}
}

static void _OP_process_density(opportunity_t *self, uint16_t *density, bool density_switch)
{
	uint16_t autopulseDensity;

	// If a cable is plugged into the density jack
	if (density_switch)
	{
		for (int i = 0; i < self->num_channels; i++)
		{
			if (self->channel[i]._edge._last != 1)
				self->probability[i] = *density;
		}

		autopulseDensity = *density;
	}
	else
	{
		for (int i = 0; i < self->num_channels; i++)
		{
			self->probability[i] = self->default_densities[i];
		}

		autopulseDensity = self->default_densities[0];
	}

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
				uint16_t msec,
				bool density_switch)
{
	// Process reset input
	_OP_process_reset(self, reset);

	// Process density input
	_OP_process_density(self, density, density_switch);

	// Process the automatic pulsing
	autopulse_process(&self->_autopulse, msec, autopulse);

	*autopulse = (*autopulse > 0) ? self->v_max : 0;

	// Process CV inputs
	_OP_process_CV(self, input, output);
}
