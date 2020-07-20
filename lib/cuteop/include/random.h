#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t _hold;
} t_random;

void random_init(t_random *self);
void random_process(t_random *self, uint16_t *in, uint16_t *out);

#ifdef __cplusplus
}
#endif

#endif // RANDOM_H