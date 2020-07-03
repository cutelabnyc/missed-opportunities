#include "pass-thru.h"

static uint16_t magic = 42;

void PT_init(passthru_t * pt)
{
    pt->dummy = magic;
}

void PT_destroy(passthru_t *pt)
{

}

void PT_process(passthru_t *pt, uint16_t *in, uint16_t *out, uint8_t channel_count)
{
    for (uint8_t i = 0; i < channel_count; i++) {
        out[i] = in[i];
    }
}
