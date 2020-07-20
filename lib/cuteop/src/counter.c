#include "counter.h";

void counter_init(t_counter *self, uint16_t max)
{
    self->_count = 0;
    self->_max = max;
}

void counter_process(t_counter *self, uint16_t *in, uint16_t *out)
{
    *out = self->_count;

    if (*in > 0) {
        self->_count++;
        if (self->_count >= self->_max) {
            self->_count = 0;
        }
    }
}
