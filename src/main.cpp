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
channel_t channels[NUM_CHANNELS];
GPIO_t GPIO;

buffer_t GATE_in[NUM_CHANNELS];
bool GATE_out[NUM_CHANNELS];
bool MISSED_opportunities[NUM_CHANNELS - 1];

char RESEED_in;
char RESET_in;
uint16_t DENSITY_in;
char MISMATCH_in;
uint16_t AUTOPULSE_out;
char last_reseed = 0;
uint16_t random_counter = 0;
uint16_t original_seed;

uint16_t lastMsec = 0;

float time_dilation = SPEEDUP;


static unsigned int makeRandomSeed()
{
  unsigned int out = 0;
  buffer_t in[NUM_CHANNELS];
  char reseed;
  char reset;
  uint16_t density;
  char mismatch;
  unsigned int readBits = 0;
  while (readBits < CHAR_BIT * sizeof(unsigned int))
  {
    GPIO_read(&GPIO, in, &reseed, &reset, &density, &mismatch);
    for (char i = 0; i < NUM_CHANNELS; i++)
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

  // Serial.begin(9600);

  original_seed = makeRandomSeed();

  OP_init(&opportunity,
          channels,
          NUM_CHANNELS,
          V_MAX,
				  V_CUTOFF,
          HYSTERESIS,
          original_seed);
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
  GPIO_read(&GPIO, GATE_in, &RESEED_in, &RESET_in, &DENSITY_in, &MISMATCH_in);

  uint16_t time = millis();
  uint16_t msec = (time - lastMsec) * time_dilation;
  lastMsec = time;
  bool reseed = RESEED_in == HIGH;
  if (!last_reseed && reseed) {
	  random_counter++;
	  OP_set_seed(&opportunity, original_seed + random_counter * 69 + time);
  }
  last_reseed = reseed;

  OP_process(&opportunity,
             GATE_in,
             GATE_out,
             RESET_in > 0,
             &DENSITY_in,
             &AUTOPULSE_out,
             MISSED_opportunities,
             (char) msec);

	// In "match" mode, copy from outputs to the missed opportunities
	// This is basically the same as the straight normalization from before
	if (MISMATCH_in == 1) {
		for (char i = 0; i < NUM_CHANNELS - 1; i++) {
			MISSED_opportunities[i] = GATE_out[i];
		}
	}

  GPIO_write(&GPIO, GATE_out, &AUTOPULSE_out, MISSED_opportunities);
}
