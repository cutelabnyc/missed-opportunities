#include "../test_util.hpp"
#include <unity.h>

extern "C"
{
#include <opportunity.h>
}

opportunity_t self;

void setUp(void)
{
    uint8_t prob_densities[1] = {100};
    // set stuff up here
    OP_init(&self, 1, 1023, 0, prob_densities);
}

void tearDown(void)
{
    // clean stuff up here
    OP_destroy(&self);
}

void test_silence_op(void)
{
    uint16_t in_data[4] = {
        0, 0, 0, 0};
    uint16_t out_data[4];
    uint16_t exp_data[4] = {
        0, 0, 0, 0};

    run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, 4);
}

/*void test_hysteresis_op(void)
{
    uint8_t prob_densities[1] = {100};

    OP_init(&self, 1, 1023, 3, prob_densities);

    uint16_t in_data[8] = {
        0, 512, 600, 510, 600, 400, 600, 512};
    uint16_t out_data[8];
    uint16_t exp_data[8] = {
        0, 512, 0, 0, 0, 0, 600, 512};

    run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, 8);
}*/

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_silence_op);
    // RUN_TEST(test_hysteresis_op);
    UNITY_END();

    return 0;
}
