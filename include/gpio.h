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
    pin_t RESET;
    pin_t DENSITY;
    pin_t PULSE_OUT;
    pin_t LEDS[NUM_LEDS];
    pin_t MISSED_OPPORTUNITIES[NUM_CHANNELS - 1];

} GPIO_t;

/**
 * Returns the global pin IO struct
 */
GPIO_t GPIO_init(void)
{
    GPIO_t self = {
        {A4, A5, A2, A3}, // CV Ins -- AD4, AD5, AD2, AD3
        {2, 3, 8, 9},     // CV Outs -- PD2, PD3, PB0, PB1
        A0,               // Reset In -- AD0
        A1,               // Density In -- AD1
        5,                // Pulse out -- PD5
        {7, 6},           // Reset and Density LEDs -- PD7, PD6,
        {4, 10, 11}       // "Missed" Opportunities —- PD4, PB2, PB3
    };

    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        pinMode(self.IN[i], INPUT);
        pinMode(self.OUT[i], OUTPUT);
    }

    pinMode(self.RESET, INPUT);
    pinMode(self.DENSITY, INPUT);
    pinMode(self.PULSE_OUT, OUTPUT);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        pinMode(self.LEDS[i], OUTPUT);
    }

    for (int i = 0; i < NUM_CHANNELS - 1; i++)
    {
        pinMode(self.MISSED_OPPORTUNITIES[i], OUTPUT);
    }

    return self;
}

/**
 * Reads incoming data from all inputs
 */
void GPIO_read(GPIO_t *self, uint16_t *in, uint16_t *reset, uint16_t *density)
{
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        in[i] = analogRead(self->IN[i]);
    }
    *reset = analogRead(self->RESET);
    *density = analogRead(self->DENSITY);

    // TODO: LEDs are read directly from function
    // scope variables, should be something different :(
    analogWrite(self->LEDS[0], *reset / 4);
    analogWrite(self->LEDS[1], *density / 4);
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
        
        // Write the Missed Opportunities
        if(i < NUM_CHANNELS - 1){
            digitalWrite(self->MISSED_OPPORTUNITIES[i], missed_opportunities[i]);
        }
    }

    digitalWrite(self->PULSE_OUT, *pulse_out);
}
