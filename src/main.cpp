/**
 * main.cpp —— (Max Ardito, 07/09/20)
 *
 * Main functional loop for the Missed Opportunities module. It's the
 * place where the hardware [GPIO_t] and the code API [/lib/] go on
 * expensive and indulgent, yet rewarding dinner dates, noshing on
 * the signals served by [buffer_t CV_in/CV_out].
 *
 * NOTE: Might be worth eventually including a debugging argument
 * for use of the Serial monitor, if QA situations ever arose where
 * that was needed
 */

#include "gpio.h"
#include "limits.h"

extern "C"
{
#include "opportunity.h"
}

/**
 * BUG: Random seeds should be triggered by a hardware
 * input that initializes a random value from noise
 */

opportunity_t opportunity;
GPIO_t GPIO;

buffer_t CV_in[NUM_CHANNELS];
buffer_t CV_out[NUM_CHANNELS];

uint16_t RESET_in;
uint16_t DENSITY_in;
uint16_t AUTOPULSE_out;

uint16_t lastMsec = 0;
bool DENSITY_switch;

// TODO: Stash these probabilities in the hardware
uint16_t default_densities[NUM_CHANNELS] = {511, 267, 150, 100};

static unsigned int makeRandomSeed()
{
  unsigned int out = 0;
  buffer_t in[NUM_CHANNELS];
  uint16_t reset;
  uint16_t density;
  unsigned int readBits = 0;
  while (readBits < CHAR_BIT * sizeof(unsigned int))
  {
    GPIO_read(&GPIO, in, &reset, &density);
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

  DENSITY_switch = true;
  Serial.begin(9600);

  unsigned int random_seed = makeRandomSeed();

  OP_init(&opportunity,
          NUM_CHANNELS,
          V_MAX,
          HYSTERESIS,
          default_densities,
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
  GPIO_read(&GPIO, CV_in, &RESET_in, &DENSITY_in);

  uint16_t time = millis();
  uint16_t msec = time - lastMsec;
  lastMsec = time;

  OP_process(&opportunity,
             CV_in,
             CV_out,
             &RESET_in,
             &DENSITY_in,
			 &AUTOPULSE_out,
			 msec,
             DENSITY_switch);

  GPIO_write(&GPIO, CV_out);
}
