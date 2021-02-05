/**
 * main.cpp —— (Max Ardito, 07/09/20)
 *
 * Main functional loop for the Missed Opportunities module. It's the
 * place where the hardware [GPIO_t] and the code API [/lib/] go on
 * expensive and indulgent, yet rewarding dinner dates, noshing on
 * the signals served by [buffer_t CV_in/CV_out].
 */

#include "gpio.h"
#include "limits.h"

extern "C"
{
#include "opportunity.h"
}

opportunity_t opportunity;
GPIO_t GPIO;

buffer_t CV_in[NUM_CHANNELS];
buffer_t CV_out[NUM_CHANNELS];
buffer_t MISSED_opportunities[NUM_CHANNELS - 1];

uint16_t RESET_in;
uint16_t DENSITY_in;
uint16_t MISMATCH_in;
uint16_t AUTOPULSE_out;

uint16_t lastMsec = 0;

static unsigned int makeRandomSeed()
{
  unsigned int out = 0;
  buffer_t in[NUM_CHANNELS];
  uint16_t reset;
  uint16_t density;
  uint16_t mismatch;
  unsigned int readBits = 0;
  while (readBits < CHAR_BIT * sizeof(unsigned int))
  {
    GPIO_read(&GPIO, in, &reset, &density, &mismatch);
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
      out = out << 1;
      out = out | (in[i] & 1);
      readBits++;
    }
  }

  return out;
}

/**
 * Initializes the ATMEGA328's pins, initializes
 * the channel_t* struct's variables, starts off the Serial
 * monitor for possible debugging
 */
void setup()
{
  GPIO = GPIO_init();

  Serial.begin(9600);

  unsigned int random_seed = makeRandomSeed();

  OP_init(&opportunity,
          NUM_CHANNELS,
          V_MAX,
		      V_CUTOFF,
          HYSTERESIS,
          random_seed);
}

/**
 * The three step process of the loop consists of reading CV values
 * passed through the four channels of module by the ATMEGA328's
 * ADC [GPIO_read()], finding zero crossings and gating certain
 * crossings based on markov probabilities [OP_process()], and
 * finally writing the values to the four outputs on the module
 * [GPIO_write()].
 */
void loop()
{
  GPIO_read(&GPIO, CV_in, &RESET_in, &DENSITY_in, &MISMATCH_in);

  uint16_t time = millis();
  uint16_t msec = time - lastMsec;
  lastMsec = time;

  OP_process(&opportunity,
             CV_in,
             CV_out,
             &RESET_in,
             &DENSITY_in,
             &AUTOPULSE_out,
             MISSED_opportunities,
             msec);

	// In "match" mode, copy from outputs to the missed opportunities
	// This is basically the same as the straight normalization from before
	if (MISMATCH_in == 0) {
		for (int i = 0; i < NUM_CHANNELS - 1; i++) {
			MISSED_opportunities[i] = CV_out[i];
		}
	}

  GPIO_write(&GPIO, CV_out, &AUTOPULSE_out, MISSED_opportunities);
}
