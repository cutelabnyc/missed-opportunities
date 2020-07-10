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

opportunity_t op;

int analogPin = A3;
int outputPin = 10;
uint16_t val = 0;
uint16_t output;

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
  OP_init(&op, 2, 1023, 3);

  pinMode(outputPin, OUTPUT);

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
  val = analogRead(analogPin);
  OP_process(&op, &val, &output);
  digitalWrite(outputPin, val <= 511 ? LOW : HIGH);
}
