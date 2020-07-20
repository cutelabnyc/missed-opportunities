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
 * probability_t: Contains individual probability gates
 * and densities
 * 
 * TODO: Add and describe parameters
 */
typedef struct probability
{
    bool gate;
    uint8_t density;
} probability_t;

/**
 * Initializes a probability struct using a custom
 * probability density (between 0 - 100)
 * 
 * TODO: Add and describe parameters
 */
void PROB_init(probability_t *self, uint8_t density);

/**
 * Tear down resources associated with 'probability' struct
 * 
 * TODO: Add and describe parameters
 */
void PROB_destroy(probability_t *self);

/**
 * Process function for probability
 * 
 * TODO: Add and describe parameters
 */
bool PROB_process(probability_t *self);

#endif /* PROBABILITY_H */