#ifndef GATE_H
#define GATE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
} t_gate;

void gate_init(t_gate *self);
void gate_process(t_gate *self, uint16_t *in1, uint16_t *openOrClosed, uint16_t *out);

#ifdef __cplusplus
}
#endif

#endif // GATE_H