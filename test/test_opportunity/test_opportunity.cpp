#include "../test_util.hpp"
#include <unity.h>
#include <time.h>
#include <stdio.h>

extern "C"
{
#include <opportunity.h>
}

#define RANDOM_SEED 42

opportunity_t self;
uint16_t prob_densities[1] = {511};
uint16_t fixed_msec = 16;
uint16_t msec_register[32];

void setUp(void)
{
	// set stuff up here
	OP_init(&self, 1, 1023, 0, prob_densities, RANDOM_SEED);
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

<<<<<<< HEAD
	run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, NULL, msec_register, fixed_msec, false, 4);
	== == == =
				 run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, NULL, false, 4);
>>>>>>> ch108/density-input
}

void test_one_crossing_op(void)
{
	OP_init(&self, 1, 1023, 0, prob_densities, RANDOM_SEED);
	OP_set_mock_random(&self, true);

	uint16_t in_data[4] = {
		0, 800, 0, 800};
	uint16_t out_data[4];
	uint16_t exp_data[4] = {
		0, 0, 0, 1};
	uint16_t random_reset[4] = {0, 0, 0, 0};

<<<<<<< HEAD
	run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, NULL, msec_register, fixed_msec, false, 4);
	== == == =
				 run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, NULL, false, 4);
>>>>>>> ch108/density-input
}

void test_hysteresis_op(void)
{
	OP_init(&self, 1, 1023, 3, prob_densities, RANDOM_SEED);
	OP_set_mock_random(&self, true);

	uint16_t in_data[8] = {
		0, 512, 600, 510, 600, 400, 600, 512};
	uint16_t out_data[8];
	uint16_t exp_data[8] = {
		0, 0, 0, 0, 0, 0, 1, 1};
	uint16_t random_reset[4] = {0, 0, 0, 0};

<<<<<<< HEAD
	run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, NULL, msec_register, fixed_msec, false, 8);
	== == == =
				 run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, random_reset, NULL, false, 8);
>>>>>>> ch108/density-input
}

void test_seed_change(void)
{
	OP_init(&self, 1, 1023, 3, prob_densities, RANDOM_SEED);

	uint16_t in_data[10] = {
		800, 0, 800, 0, 800, 0, 800, 0, 800, 0};
	uint16_t out_data[10];
	uint16_t exp_data[10];

	// Reset seed at very end of sequence
	uint16_t reset_data[10] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 800};

	// Null density input
	uint16_t density_data[10] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Retrieve expected data, twice, to make sure the seed is reset
	for (int i = 0; i < 10; i++)
	{
		OP_process(&self, &in_data[i], &exp_data[i], &reset_data[i], &density_data[i], &msec_register[i], fixed_msec, false);
	}
	for (int i = 0; i < 10; i++)
	{
		OP_process(&self, &in_data[i], &exp_data[i], &reset_data[i], &density_data[i], &msec_register[i], fixed_msec, false);
	}

	// Get same data from reseting the seed
	run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, reset_data, NULL, msec_register, fixed_msec, false, 10);
}

void test_density_input(void)
{
	OP_init(&self, 1, 1023, 3, prob_densities, RANDOM_SEED);

	uint16_t in_data[10] = {
		800, 0, 800, 0, 800, 0, 800, 0, 800, 0};
	uint16_t out_data[10];
	uint16_t exp_data[10];

	// Null reset data
	uint16_t reset_data[10] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 800};

	// Density input data
	uint16_t density_data[10] = {
		300, 200, 0, 942, 1000, 22, 444, 330, 200, 0};

	for (int i = 0; i < 10; i++)
	{
		OP_process(&self, &in_data[i], &exp_data[i], &reset_data[i], &density_data[i], &msec_register[i], fixed_msec, true);
	}

	run_equality_test(&self, (processor_t)OP_process, in_data, out_data, exp_data, reset_data, density_data, msec_register, fixed_msec, true, 10);
}

void test_autopulse(void)
{
	OP_init(&self, 1, 1023, 3, prob_densities, RANDOM_SEED);

	const uint16_t SAMPLE_SIZE = 30000;
	uint16_t edgeCount = 0;

	uint16_t in_data = 0;
	uint16_t out_data = 0;
	uint16_t reset_data = 0;
	uint16_t autopulse_out, autopulse_last = 0;
	uint16_t density = 0;
	uint16_t msec = 1;

	for (uint16_t i = 0; i < SAMPLE_SIZE; i++)
	{
		OP_process(&self, &in_data, &out_data, &reset_data, &density, &autopulse_out, msec, true);
		if (autopulse_last == 0 && autopulse_out > 0)
			edgeCount++;
		autopulse_last = autopulse_out;
	}

	TEST_ASSERT_UINT16_WITHIN(20, (SAMPLE_SIZE * msec) / (2000), edgeCount);
}

int main(int argc, char **argv)
{
	UNITY_BEGIN();
	RUN_TEST(test_silence_op);
	RUN_TEST(test_one_crossing_op);
	RUN_TEST(test_hysteresis_op);
	RUN_TEST(test_seed_change);
	RUN_TEST(test_density_input);
	RUN_TEST(test_autopulse);
	UNITY_END();

	return 0;
}
