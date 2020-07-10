/**
 * main.cpp —— (Max Ardito, 07/09/20)
 * 
 * Main functional loop for the Missed Opportunities module, 
includes a single pointer-to-struct [opportunity_t* block]
 * and the Arduino framework's setup() and loop() functions
 * 
 * NOTE: Might be worth eventually including a debugging argument
 * for use of the Serial monitor, if QA situations ever arose where
 * that was needed
 */

#include <Arduino.h>

extern "C"
{
#include "opportunity.h"
}

/**
 * opportunity_t* block: [/lib/opportunity/opportunity.h]
 * 
 * Highest abstraction of the module's functionality.
 * Includes all parameters from IO channel to probability
 * chain
 */
opportunity_t *block;

/**
 * void setup(): 
 * 
 * Initializes the ATMEGA328's pins, initializes
 * the opportunity_t* struct's variables, starts off the Serial
 * monitor for possible debugging
 * 
 * NOTE: The Serial monitor maybe should be turned off once board 
 * is in production?
 */
void setup()
{
  OP_setPins();
  block = OP_init();

  Serial.begin(9600);
}

/**
 * void loop(): 
 * 
 * The three step process of the loop consists of reading CV values 
 * passed through the four channels of module by the ATMEGA328's
 * ADC [OP_read()], finding zero crossings and gating certain
 * crossings based on markov probabilities [OP_process()], and
 * finally writing the values to the four outputs on the module
 * [OP_write()]. 
 */
void loop()
{
  OP_read(block);
  OP_process(block);
  OP_write(block);
}
