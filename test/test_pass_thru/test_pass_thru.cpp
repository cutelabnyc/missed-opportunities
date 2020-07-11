#include <pass-thru.h>
#include <unity.h>

passthru_t pt;

void setUp(void)
{
    // set stuff up here
    PT_init(&pt);
}

void tearDown(void)
{
    // clean stuff up here
    PT_destroy(&pt);
}

void test_pt(void)
{
    uint16_t in_data[4][2] = {
        {0, 1},
        {0, 2},
        {0, 3},
        {0, 4}};
    uint16_t out_data[4][2];

    for (uint8_t s = 0; s < 4; s++)
    {
        PT_process(&pt, in_data[s], out_data[s], 2);
    }

    for (uint8_t c = 0; c < 2; c++)
    {
        for (uint8_t s = 0; s < 4; s++)
        {
            TEST_ASSERT_EQUAL_UINT16(in_data[s][c], out_data[s][c]);
        }
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_pt);
    UNITY_END();

    return 0;
}
