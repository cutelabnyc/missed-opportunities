#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdint.h>
#include <unity.h>

typedef void (*processor_t)(void *handle, uint16_t *in, uint16_t *out);

void run_equality_test(
    void *handle,
    processor_t process,
    uint16_t *ins,
    uint16_t *outs,
    uint16_t *expected,
    uint16_t count
);

#endif // TEST_UTIL_H
