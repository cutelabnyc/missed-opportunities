#include <opportunity.h>
#include "../test_util.hpp"
#include <unity.h>

opportunity_t op;

void setUp(void)
{
    // set stuff up here
    OP_init(&op, 2, 1023);
}

void tearDown(void)
{
    // clean stuff up here
    OP_destroy(&op);
}

void test_silence_op(void)
{
    uint16_t in_data[4] = {
        0, 0, 0, 0
    };
    uint16_t out_data[4];
    uint16_t exp_data[4] = {
        0, 0, 0, 0
    };

    run_equality_test(&op, (processor_t) OP_process, in_data, out_data, exp_data, 4);
}

void test_one_crossing_op(void)
{
    OP_init(&op, 2, 1023);

    uint16_t in_data[4] = {
        0, 1023, 0, 1023
    };
    uint16_t out_data[4];
    uint16_t exp_data[4] = {
        0, 0, 0, 1023
    };

    run_equality_test(&op, (processor_t) OP_process, in_data, out_data, exp_data, 4);
}

void test_two_crossings_op(void)
{
    OP_init(&op, 2, 1023);

    uint16_t in_data[8] = {
        0, 1023, 0, 1023, 0, 1023, 0, 1023
    };
    uint16_t out_data[8];
    uint16_t exp_data[8] = {
        0, 0, 0, 1023, 0, 0, 0, 1023
    };

    run_equality_test(&op, (processor_t) OP_process, in_data, out_data, exp_data, 8);
}

void test_skip_three_crossings_op(void)
{
    OP_init(&op, 3, 1023);

    uint16_t in_data[8] = {
        0, 1023, 0, 1023, 0, 1023, 0, 1023
    };
    uint16_t out_data[8];
    uint16_t exp_data[8] = {
        0, 0, 0, 1023, 0, 1023, 0, 0
    };

    run_equality_test(&op, (processor_t) OP_process, in_data, out_data, exp_data, 8);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_silence_op);
    RUN_TEST(test_one_crossing_op);
    RUN_TEST(test_two_crossings_op);
    RUN_TEST(test_skip_three_crossings_op);
    UNITY_END();

    return 0;
}
