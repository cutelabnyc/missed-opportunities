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

extern "C"
{
#include "opportunity.h"
}

opportunity_t opportunity;
GPIO_t GPIO;

buffer_t CV_in[NUM_CHANNELS];
buffer_t CV_out[NUM_CHANNELS];

uint16_t prob_densities[NUM_CHANNELS] = {511, 267, 130, 70};

/**
 * void setup(): 
 * 
 * Initializes the ATMEGA328's pins, initializes
 * the channel_t* struct's variables, starts off the Serial
 * monitor for possible debugging
 */
void setup()
{
  GPIO = GPIO_init();

  OP_init(&opportunity,
          NUM_CHANNELS,
          V_MAX,
          HYSTERESIS,
          prob_densities);

  Serial.begin(9600);
}

/**
 * void loop(): 
 * 
 * The three step process of the loop consists of reading CV values 
 * passed through the four channels of module by the ATMEGA328's
 * ADC [GPIO_read()], finding zero crossings and gating certain
 * crossings based on markov probabilities [OP_process()], and
 * finally writing the values to the four outputs on the module
 * [GPIO_write()]. 
 */
void loop()
{
  GPIO_read(&GPIO, CV_in);

  OP_process(&opportunity, CV_in, CV_out);

  GPIO_write(&GPIO, CV_out);
}
