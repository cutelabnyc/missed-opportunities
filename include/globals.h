/**
 * globals.h —— (Max Ardito, 07/10/20)
 *
 * Project globals, mostly pre-processor stuff
 */
#include <stdio.h>
#include <time.h>

#define NUM_CHANNELS 4
#define NUM_LEDS 2
#define V_MAX ((uint16_t)1023)
#define HYSTERESIS ((uint8_t)3)
#define V_CUTOFF ((uint16_t)700)

 // Used for the I/O buffers in main.cpp
typedef uint16_t buffer_t;
