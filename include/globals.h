/**
 * globals.h —— (Max Ardito, 07/10/20)
 * 
 * Project globals, mostly pre-processor stuff
 */
#include <stdio.h>
#include <time.h>

#define NUM_CHANNELS (uint8_t)4
#define V_MAX (uint16_t)1023
#define HYSTERESIS (uint8_t)3

// Used for the I/O buffers in main.cpp
typedef uint16_t buffer_t;