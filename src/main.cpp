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

opportunity_t op[4];

int analogPins[4] = {
  A2, A3, A4, A5
};

int outputPins[4] = {
  2, 3, 4, 5
};

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
  for (int i = 0; i < 4; i++) {
    OP_init(op + i, 2, 1023, 3);
    pinMode(outputPins[i], OUTPUT);
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
  for (int i = 0; i < 4; i++) {
    val = analogRead(analogPins[i]);
    // Serial.print("input: ");
    // Serial.println(val, DEC);
    OP_process(op + i, &val, &output);
    // Serial.print("proc: ");
    // Serial.println(output, DEC);
    digitalWrite(outputPins[i], output <= 511 ? LOW : HIGH);
    // Serial.print("out");
    // Serial.println(output <= 511 ? LOW : HIGH, DEC);
  }
}
