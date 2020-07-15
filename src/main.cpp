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

#include "gpio.h"

extern "C"
{
#include "opportunity.h"
}

opportunity_t op[4];
GPIO_t GPIO;

uint16_t val[NUM_CHANNELS];
uint16_t output[NUM_CHANNELS];

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
  GPIO = GPIO_init();
  for (int i = 0; i < 4; i++)
  {
    OP_init(op + i, 2, 1023, 3);
  }

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
  GPIO_read(&GPIO, val);

  for (int i = 0; i < NUM_CHANNELS; i++)
  {
    //val = analogRead(analogPins[i]);
    // Serial.print("input: ");
    // Serial.println(val, DEC);
    OP_process(&op[i], &val[i], &output[i]);
    // Serial.print("proc: ");
    // Serial.println(output, DEC);
    // Serial.print("out");
    // Serial.println(output <= 511 ? LOW : HIGH, DEC);
  }
  GPIO_write(&GPIO, output);
}
