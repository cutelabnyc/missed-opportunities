#include "../test_util.hpp"
#include <unity.h>
#include <time.h>
#include <stdio.h>

extern "C"
{
#include <opportunity.h>
}

#define RESET_SEED(x) srand(x)

opportunity_t self;
uint16_t prob_densities[1] = {511};

void setUp(void)
{
    // set stuff up here
    OP_init(&self, 1, 1023, 0, prob_densities);
    OP_set_mock_random(&self, true);
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
    uint16_t random_reset[4] = {0, 0, 0, 0};

    run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, 4);
}

void test_one_crossing_op(void)
{
    OP_init(&self, 1, 1023, 0, prob_densities);
    OP_set_mock_random(&self, true);

    uint16_t in_data[4] = {
        0, 800, 0, 800};
    uint16_t out_data[4];
    uint16_t exp_data[4] = {
        0, 0, 0, 1};
    uint16_t random_reset[4] = {0, 0, 0, 0};

    run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, 4);
}

void test_hysteresis_op(void)
{
    OP_init(&self, 1, 1023, 3, prob_densities);
    OP_set_mock_random(&self, true);

    uint16_t in_data[8] = {
        0, 512, 600, 510, 600, 400, 600, 512};
    uint16_t out_data[8];
    uint16_t exp_data[8] = {
        0, 0, 0, 0, 0, 0, 1, 1};
    uint16_t random_reset[4] = {0, 0, 0, 0};

    run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, 8);
}

void test_seed_change(void)
{
    OP_init(&self, 1, 1023, 3, prob_densities);

    uint16_t in_data[10] = {
        800, 0, 800, 0, 800, 0, 800, 0, 800, 0};
    uint16_t out_data[10];
    uint16_t exp_data[10];

    // Reset seed at very end of sequence
    uint16_t reset_data[10] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Retrieve expected data
    for (int i = 0; i < 10; i++)
    {
        OP_process(&self, &in_data[i], &exp_data[i], &reset_data[i]);
    }

    // Reset seed
    RESET_SEED(self.random_seed);

    // Get same data from reseting the seed
    run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, reset_data, 10);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_silence_op);
    RUN_TEST(test_one_crossing_op);
    RUN_TEST(test_hysteresis_op);
    RUN_TEST(test_seed_change);
    UNITY_END();

    return 0;
}
