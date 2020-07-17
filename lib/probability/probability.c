#include <probability.h>
#include <stdlib.h>

/**
 * static bool _rand_50()
 * 
 * TODO: Add and describe parameters
 */
static bool _rand_50()
{
    return rand() & 1;
}

/**
 * static bool _rand_25()
 * 
 * TODO: Add and describe parameters
 */
static bool _rand_25()
{
    return !(_rand_50() | _rand_50());
}

/**
 * void PROB_init(probability_t *self, prob_value_t prob_value)
 * 
 * TODO: Add and describe parameters
 */
void PROB_init(probability_t *self, prob_value_t prob_value)
{
    self->rando = 0;
    self->prob_value = prob_value;
}

/**
 * bool PROB_process(probability_t *probability)
 * 
 * TODO: Add and describe parameters
 */
bool PROB_process(probability_t *self)
{
    if (self->prob_value == p_50)
    {
        self->rando = _rand_50();
        return self->rando;
    }
    else if (self->prob_value == p_25)
    {
        self->rando = _rand_25();
        return self->rando;
    }
    else
    {
        return 0;
    }
}