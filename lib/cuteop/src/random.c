#include "random.h";

uint16_t _random_next()
{
    return rand() & 1023; // hardcoded 10 bits
}

void random_init(t_random *self)
{
    self->_hold = _random_next();
}

void random_process(t_random *self, uint16_t *in, uint16_t *out)
{
    *out = self->_hold;

    if (*in) {
        self->_hold = _random_next();
    }
}
