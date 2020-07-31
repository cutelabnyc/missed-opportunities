#include "test_util.hpp"

void run_equality_test(
    void *handle,
    processor_t process,
    uint16_t *ins,
    uint16_t *outs,
    uint16_t *expected,
    uint16_t *random_reset,
    uint16_t *density_input,
    bool density_switch,
    uint16_t count)
{
    for (uint16_t i = 0; i < count; i++)
    {
        process(handle, ins + i, outs + i, random_reset + i, density_input + i, density_switch);
    }
    for (uint16_t i = 0; i < count; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(expected[i], outs[i]);
    }
}
