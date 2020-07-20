#include "gate.h";

void gate_init(t_gate *self) { /* no-op */}

void gate_process(t_gate *self, uint16_t *in1, uint16_t *openOrClosed, uint16_t *out)
{
    *out = (*openOrClosed > 0) ? *in1 : 0;
}
