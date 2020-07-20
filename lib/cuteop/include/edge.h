#ifndef EDGE_H
#define EDGE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t _last;
} t_edge;

void edge_init(t_edge *self);
void edge_process(t_edge *self, uint16_t *in, uint16_t *out);

#ifdef __cplusplus
}
#endif

#endif // EDGE_H