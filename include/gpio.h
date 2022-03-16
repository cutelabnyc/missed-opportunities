/**
 * gpio.h —— (Max Ardito, 07/10/20)
 *
 * Wrapper classs used in order to create a layer of abstraction
 * in between the hardware and the module's API. Consists of the general
 * structure for the pin layout used on the ATMEGA328, as well as
 * read/write wrapper functions based on the <Arduino.h> lib.
 */

#include "globals.h"
#include <Arduino.h>

typedef uint8_t pin_t;

/**
 * Struct representing the entire IO for the module
 */
typedef struct GPIO
{
    pin_t IN[NUM_CHANNELS];
    pin_t OUT[NUM_CHANNELS];
	pin_t RESEED;
    pin_t RESET;
    pin_t DENSITY;
    pin_t PULSE_OUT;
    pin_t LEDS[NUM_LEDS];
	pin_t MISMATCH;
    pin_t MISSED_OPPORTUNITIES[NUM_CHANNELS - 1];

    int densityReadSequence;

} GPIO_t;

/**
 * Returns the global pin IO struct
 */
GPIO_t GPIO_init(void)
{
	/** Old configuration
    GPIO_t self = {
        {A4, A5, A2, A3}, // CV Ins -- AD4, AD5, AD2, AD3
        {2, 3, 8, 9},     // CV Outs -- PD2, PD3, PB0, PB1
        A0,               // Reset In -- AD0
        A1,               // Density In -- AD1
        5,                // Pulse out -- PD5
        {7, 6},           // Reset and Density LEDs -- PD7, PD6,
        {4, 10, 11}       // "Missed" Opportunities —- PD4, PB2, PB3
    };
	*/

    GPIO_t self = {
        {A5, A0, A1, A2}, // CV Ins -- AD5, AD0, AD1, AD2
        {4, 12, 10, 8},     // CV Outs -- PD4, PB4, PB2, PB0
		2,				  // Reseed In -- PD2
        A3,               // Reset In -- AD3
        A4,               // Density In -- AD4
        3,                // Pulse out -- PD3
        {6, 5},           // Reset and Density LEDs (respectively) -- PD6, PD5,
		7,				  // PD7 used to set miss/match
        {13, 11, 9},      // "Missed" Opportunities —- PB5, PB3, PB1

        0                 // Only read density every other clock
    };

    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        pinMode(self.IN[i], INPUT);
        pinMode(self.OUT[i], OUTPUT);
    }

	pinMode(self.RESEED, INPUT_PULLUP);
    pinMode(self.RESET, INPUT);
    pinMode(self.DENSITY, INPUT);
    pinMode(self.PULSE_OUT, OUTPUT);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        pinMode(self.LEDS[i], OUTPUT);
    }

	pinMode(self.MISMATCH, INPUT);

    for (int i = 0; i < NUM_CHANNELS - 1; i++)
    {
        pinMode(self.MISSED_OPPORTUNITIES[i], OUTPUT);
    }

    return self;
}

/**
 * Reads incoming data from all inputs
 */
void GPIO_read(GPIO_t *self, uint16_t *in, uint16_t *reseed, uint16_t *reset, uint16_t *density, uint16_t *mismatch)
{
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        #ifdef ANALOG_READ
        in[i] = analogRead(self->IN[i]);
        #else
        in[i] = digitalRead(self->IN[i]) * 1024;
        #endif
    }
	*reseed = digitalRead(self->RESEED);
    #ifdef ANALOG_READ
    *reset = analogRead(self->RESET);
    #else
    *reset = digitalRead(self->RESET) * 1024;
    #endif
    if (self->densityReadSequence++ == 2) {
        *density = analogRead(self->DENSITY);
        self->densityReadSequence = 0;
    }
	*mismatch = digitalRead(self->MISMATCH);

	// *reset = 0;
	// *density = 768;
	// *mismatch = 0; // assume this is match mode

    // Reset should appear to be binary, even though it's reading an analog value
    analogWrite(self->LEDS[0], *reset > V_CUTOFF ? 200 : 0);
    // analogWrite(self->LEDS[0], *reset / 4);
    // analogWrite(self->LEDS[0], 255);

	// analogWrite(self->LEDS[0], *mismatch ? 255 : 0);
    // analogWrite(self->LEDS[1], *density / 32);
	double dreg = (*density / 4) / 255.0;
	analogWrite(self->LEDS[1], (uint16_t) (dreg * dreg * dreg * 255));

    // analogWrite(self->LEDS[0], 255);
    // analogWrite(self->LEDS[1], 255);
}

/**
 * Writes data to all outputs
 */
void GPIO_write(GPIO_t *self, uint16_t *out, uint16_t *pulse_out, uint16_t* missed_opportunities)
{
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        // Write the channels
        digitalWrite(self->OUT[i], out[i]);
		// digitalWrite(self->OUT[i], 255);

        // Write the Missed Opportunities
        if(i < NUM_CHANNELS - 1){
            digitalWrite(self->MISSED_OPPORTUNITIES[i], missed_opportunities[i]);
			// digitalWrite(self->MISSED_OPPORTUNITIES[i], 255);
        }
    }

    // static bool po = false;
    // po != po;
	// digitalWrite(self->PULSE_OUT, po ? 255 : 0);
    digitalWrite(self->PULSE_OUT, *pulse_out);
    // digitalWrite(self->PULSE_OUT, HIGH);
}
