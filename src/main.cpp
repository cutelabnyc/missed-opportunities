/**
 * main.cpp —— (Max Ardito, 07/09/20)
 * 
 * Main functional loop for the Missed Opportunities module, 
 * includes a single pointer-to-struct [channel_t* block]
 * and the Arduino framework's setup() and loop() functions
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

uint16_t val[NUM_CHANNELS];
uint16_t output[NUM_CHANNELS];

/**
 * void setup(): 
 * 
 * Initializes the ATMEGA328's pins, initializes
 * the channel_t* struct's variables, starts off the Serial
 * monitor for possible debugging
 * 
 * NOTE: The Serial monitor maybe should be turned off once board 
 * is in production?
 */
void setup()
{
  GPIO = GPIO_init();

  OP_init(&opportunity,
          NUM_CHANNELS,
          SKIP_SIZE,
          V_MAX,
          HYSTERESIS);

  Serial.begin(9600);
}

/**
 * void loop(): 
 * 
 * The three step process of the loop consists of reading CV values 
 * passed through the four channels of module by the ATMEGA328's
 * ADC [CH_read()], finding zero crossings and gating certain
 * crossings based on markov probabilities [CH_process()], and
 * finally writing the values to the four outputs on the module
 * [CH_write()]. 
 */
void loop()
{
  GPIO_read(&GPIO, val);

  OP_process(&opportunity, val, output);

  GPIO_write(&GPIO, output);
}
