#include <probability.h>
#include <stdlib.h>

/**
 * void PROB_init(probability_t *self, uint8_t density)
 * 
 * TODO: Add and describe parameters
 */
void PROB_init(probability_t *self, uint8_t density)
{
    self->gate = 0;
    self->density = density;
}

/**
 * void PROB_destroy(probability_t *self)
 * 
 * TODO: Add and describe parameters
 */
void PROB_destroy(probability_t *self)
{
    // nothing to do
}

/**
 * bool PROB_process(probability_t *self)
 * 
 * TODO: Add and describe parameters
 */
bool PROB_process(probability_t *self)
{
    self->gate = (rand() % 100) < self->density;
    return self->gate;
}