/**
 * gpio.h —— (Max Ardito, 07/10/20)
 * 
 * Structure for pins used in the ATMEGA328
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
    pin_t LED[NUM_CHANNELS];
} GPIO_t;

/**
 * Returns the global pin IO struct
 */
GPIO_t GPIO_init(void)
{
    GPIO_t self = {
        {A2, A3, A4, A5}, // Analog Ins
        {2, 3, 4, 5},     // Digital Outs
        {13, 0, 0, 0}     // LED Outs
    };

    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        pinMode(self.IN[i], INPUT);
        pinMode(self.OUT[i], OUTPUT);
        pinMode(self.LED[i], OUTPUT);
    }

    return self;
}

/**
 * Reads incoming data from all inputs
 */
uint16_t GPIO_read(GPIO_t *self)
{
    uint16_t values[NUM_CHANNELS];
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        values[i] = analogRead(self->IN[i]);
    }
    return *values;
}

/**
 * Writes data to all outputs
 */
void GPIO_write(GPIO_t *self, uint16_t *out)
{
    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        digitalWrite(self->OUT[i], out[i]);
    }
}