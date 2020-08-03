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
} GPIO_t;

/**
 * Returns the global pin IO struct
 */
GPIO_t GPIO_init(void)
{
	GPIO_t self = {
		{A2, A3, A4, A5}, // CV Ins
		{2, 3, 4, 5},	  // CV Outs
		A1,				  // Reset In
		A0,				  // Density In
		6				  // Pulse out
	};

	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		pinMode(self.IN[i], INPUT);
		pinMode(self.OUT[i], OUTPUT);
	}

	pinMode(self.RESET, INPUT);
	pinMode(self.DENSITY, INPUT);
	pinMode(self.PULSE_OUT, OUTPUT);

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
}

/**
 * Writes data to all outputs
 */
void GPIO_write(GPIO_t *self, uint16_t *out, uint16_t *pulse_out)
{
	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		digitalWrite(self->OUT[i], out[i]);
	}

	digitalWrite(self->PULSE_OUT, *pulse_out);
}
