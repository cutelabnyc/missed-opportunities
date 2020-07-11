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

GPIO_t *GPIO_init(void)
{
    GPIO_t self = {
        {A5, A4, A3, A2}, // Analog Ins
        {3, 9, 10, 11},   // Digital Outs
        {13, 0, 0, 0}     // LED Outs
    };

    for (int i = 0; i < NUM_CHANNELS; i++)
    {
        pinMode(self.IN[i], INPUT);
        pinMode(self.OUT[i], OUTPUT);
        pinMode(self.LED[i], OUTPUT);
    }

    return &self;
}