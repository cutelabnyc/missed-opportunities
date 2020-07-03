#ifndef PASS_THRU_H
#define PASS_THRU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct passthru_t {
    uint16_t dummy;
} passthru_t;

void PT_init(passthru_t * pt);
void PT_destroy(passthru_t *pt);

void PT_process(passthru_t *pt, uint16_t *in, uint16_t *out, uint8_t channel_count);

#ifdef __cplusplus
}
#endif

#endif /* PASS_THRU_H */