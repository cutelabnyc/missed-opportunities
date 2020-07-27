#include <channel.h>

/**
 * void CH_init(channel_t *self, uint8_t skipSize, uint16_t v_max, uint16_t hysteresis)
 *
 * TODO: Add and describe parameters
 */
void CH_init(channel_t *self, uint16_t v_max, uint16_t hysteresis)
{
    thresh_init(&self->_input_thresh, (v_max / 2) - 1, hysteresis);
    random_init(&self->_random);
    gate_init(&self->_gate);
    edge_init(&self->_edge);
    thresh_init(&self->_random_thresh, (v_max / 2) - 1, 0);
}

/**
 * void CH_destroy(channel_t *self)
 *
 * TODO: Add and describe parameters
 */
void CH_destroy(channel_t *self)
{
    // nothing to do
}

/**
 * void CH_set_mock_random(channel_t *self, bool doMock)
 *
 * TODO: Add and describe parameters
 */
void CH_set_mock_random(channel_t *self, bool doMock)
{
    random_set_mock(&self->_random, doMock);
}

/**
 * void CH_process(channel_t *self,
 *               uint16_t *in,
 *               uint16_t *prob,
 *               uint16_t reset
 *               uint16_t *out)
 *
 * TODO: Add and describe parameters
 */
void CH_process(channel_t *self,
                uint16_t *in,
                uint16_t *prob,
                uint16_t reset,
                uint16_t *out)
{
    // Threshold the input to +/- 2.5V
    uint16_t postThresh;
    thresh_process(&self->_input_thresh, in, &postThresh);

    // // Convert to 0 -> 1 transition
    uint16_t postEdge;
    edge_process(&self->_edge, &postThresh, &postEdge);

    // // Reset random value sequence if an edge is detected from reset inlet
    if (reset)
    {
        random_reset(&self->_random, self->_random._seed);
    }

    // // Generate a new random number on an edge
    uint16_t randomOutput;
    random_process(&self->_random, &postEdge, &randomOutput);

    // // Threshold the random value
    uint16_t postRandomThresh;
    thresh_set_cutoff(&self->_random_thresh, 1023 - *prob);
    thresh_process(&self->_random_thresh, &randomOutput, &postRandomThresh);

    // // Gate the output accordingly
    gate_process(&self->_gate, &postThresh, &postRandomThresh, out);
}
