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
 * static bool _rand_25()
 * 
 * TODO: Add and describe parameters
 */
static bool _rand_15()
{
    return !(_rand_25() | _rand_25());
}

/**
 * static bool _rand_25()
 * 
 * TODO: Add and describe parameters
 */
static bool _rand_5()
{
    return !(_rand_15() | _rand_15());
}

/**
 * void PROB_init(probability_t *self, prob_value_t prob_value)
 * 
 * TODO: Add and describe parameters
 */
void PROB_init(probability_t *self, prob_value_t prob_value)
{
    self->gate = 0;
    self->prob_value = prob_value;
}

/**
 * bool PROB_process(probability_t *self)
 * 
 * TODO: Add and describe parameters
 */
bool PROB_process(probability_t *self)
{
    if (self->prob_value == p_50)
    {
        self->gate = _rand_50();
        return self->gate;
    }
    else if (self->prob_value == p_25)
    {
        self->gate = _rand_25();
        return self->gate;
    }
    else if (self->prob_value == p_15)
    {
        self->gate = _rand_15();
        return self->gate;
    }
    else if (self->prob_value == p_5)
    {
        self->gate = _rand_5();
        return self->gate;
    }
    else
        return 0;
}