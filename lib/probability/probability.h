/**
 * probability.h —— (Max Ardito, 07/17/20)
 * 
 * Probability density for each I/O channel
 */

#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <stdint.h>
#include <stdbool.h>

/**
 * probability_t: Struct containing CV prossing variables
 * and unique [probability_t] data for each I/O channel
 * 
 * TODO: Add and describe parameters
 */
typedef struct probability
{
    bool rando;
} probability_t;

#endif /* PROBABILITY_H */