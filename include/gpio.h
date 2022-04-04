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

typedef char pin_t;

static uint8_t b_register;
#ifndef ANALOG_READ
static uint8_t c_register;
#endif
static uint8_t d_register;

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

    char densityReadSequence;

} GPIO_t;

#if (NUM_CHANNELS == 4)
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
#elif (NUM_CHANNELS == 3)
GPIO_t self = {
    {A5, A0, A1}, // CV Ins -- AD5, AD0, AD1, AD2
    {4, 12, 10},     // CV Outs -- PD4, PB4, PB2, PB0
    2,				  // Reseed In -- PD2
    A3,               // Reset In -- AD3
    A4,               // Density In -- AD4
    3,                // Pulse out -- PD3
    {6, 5},           // Reset and Density LEDs (respectively) -- PD6, PD5,
    7,				  // PD7 used to set miss/match
    {13, 11},      // "Missed" Opportunities —- PB5, PB3, PB1

    0                 // Only read density every other clock
};
#else
GPIO_t self = {
    {A5, A0},
    {4, 12},
    2,				  // Reseed In -- PD2
    A3,               // Reset In -- AD3
    A4,               // Density In -- AD4
    3,                // Pulse out -- PD3
    {6, 5},           // Reset and Density LEDs (respectively) -- PD6, PD5,
    7,				  // PD7 used to set miss/match
    {13},

    0                 // Only read density every other clock
};
#endif

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

    for (char i = 0; i < NUM_CHANNELS; i++)
    {
        pinMode(self.IN[i], INPUT);
        pinMode(self.OUT[i], OUTPUT);
    }

	pinMode(self.RESEED, INPUT_PULLUP);
    pinMode(self.RESET, INPUT);
    pinMode(self.DENSITY, INPUT);
    pinMode(self.PULSE_OUT, OUTPUT);

    for (char i = 0; i < NUM_LEDS; i++)
    {
        pinMode(self.LEDS[i], OUTPUT);
    }

	pinMode(self.MISMATCH, INPUT);

    for (char i = 0; i < NUM_CHANNELS - 1; i++)
    {
        pinMode(self.MISSED_OPPORTUNITIES[i], OUTPUT);
    }

    return self;
}

/**
 * Reads incoming data from all inputs
 */
void GPIO_read(GPIO_t *self, uint16_t *in, char *reseed, char *reset, uint16_t *density, char *mismatch)
{
    uint16_t analogVal;
    b_register = PINB;
    #ifndef ANALOG_READ
    c_register = PINC;
    #endif
    d_register = PIND;

    #ifdef ANALOG_READ
        for (char i = 0; i < NUM_CHANNELS; i++)
        {
            in[i] = analogRead(self->IN[i]);
        }
    #else
        c_register = PINC;
        for (char i = 0; i < NUM_CHANNELS; i++) {
            in[i] = (c_register & digitalPinToBitMask(self->in[i])) ? 1024 : 0;
        }
    #endif

    *reseed = (d_register & digitalPinToBitMask(self->RESEED)) ? HIGH : LOW;

    #ifdef ANALOG_READ
    analogVal = analogRead(self->RESET);
    *reset = analogVal > V_CUTOFF;
    #else
    *reset = (c_register & digitalPinToBitMask(self->RESET));
    #endif
    if (self->densityReadSequence++ == 2) {
        *density = analogRead(self->DENSITY);
        self->densityReadSequence = 0;
    }
    *mismatch = (d_register & digitalPinToBitMask(self->MISMATCH)) ? HIGH : LOW;

	// *reset = 0;
	// *density = 768;
	// *mismatch = 0; // assume this is match mode

    // Reset should appear to be binary, even though it's reading an analog value
    analogWrite(self->LEDS[0], *reset ? 200 : 0);
    // analogWrite(self->LEDS[0], *reset / 4);
    // analogWrite(self->LEDS[0], 255);

	// analogWrite(self->LEDS[0], *mismatch ? 255 : 0);
    // analogWrite(self->LEDS[1], *density / 32);
	float dreg = (*density / 4) / 255.0;
	analogWrite(self->LEDS[1], (uint8_t) (dreg * dreg * dreg * 255));
    // analogWrite(5, (uint16_t) (dreg * dreg * dreg * 255));
    // analogWrite(5, *mismatch ? 255 : 0 );

    // analogWrite(self->LEDS[0], 255);
    // analogWrite(self->LEDS[1], 255);
}

#define __fastwrite(pin, val) \
(pin < 8) ? \
    (val ? \
        PORTD |= digitalPinToBitMask(pin) : \
        PORTD &= ~digitalPinToBitMask(pin) \
    ) : \
    (val ? \
        PORTB |= digitalPinToBitMask(pin) : \
        PORTB &= ~digitalPinToBitMask(pin) \
    )

/**
 * Writes data to all outputs
 */
void GPIO_write(GPIO_t *self, bool *out, uint16_t *pulse_out, bool* missed_opportunities)
{
    for (char i = 0; i < NUM_CHANNELS; i++)
    {
        __fastwrite(self->OUT[i], out[i]);
		// digitalWrite(self->OUT[i], 255);

        // Write the Missed Opportunities
        if(i < NUM_CHANNELS - 1){
            __fastwrite(self->MISSED_OPPORTUNITIES[i], missed_opportunities[i]);
			// digitalWrite(self->MISSED_OPPORTUNITIES[i], 255);
            // digitalWrite(13, HIGH);
            // digitalWrite(self->MISSED_OPPORTUNITIES[0], HIGH);
        }
    }

    // static bool po = false;
    // po != po;
	// digitalWrite(self->PULSE_OUT, po ? 255 : 0);
    __fastwrite(self->PULSE_OUT, *pulse_out);
    // digitalWrite(self->PULSE_OUT, HIGH);
}

#if 0
void GPIO_write_slow(GPIO_t *self, bool *out, uint16_t *pulse_out, bool* missed_opportunities)
{
    for (char i = 0; i < NUM_CHANNELS; i++)
    {
        digitalWrite(self->OUT[i], out[i]);
		// digitalWrite(self->OUT[i], 255);

        // Write the Missed Opportunities
        if(i < NUM_CHANNELS - 1){
            digitalWrite(self->MISSED_OPPORTUNITIES[i], missed_opportunities[i]);
			// digitalWrite(self->MISSED_OPPORTUNITIES[i], 255);
            // digitalWrite(13, HIGH);
            // digitalWrite(self->MISSED_OPPORTUNITIES[0], HIGH);
        }
    }

    // static bool po = false;
    // po != po;
	// digitalWrite(self->PULSE_OUT, po ? 255 : 0);
    digitalWrite(self->PULSE_OUT, *pulse_out);
    // digitalWrite(self->PULSE_OUT, HIGH);
}
#endif
