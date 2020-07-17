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
 * prob_value_t: Flags for each probability density
 * 
 * TODO: Add and describe parameters
 */
typedef enum
{
    p_50,
    p_25,
    p_15,
    p_5
} prob_value_t;

/**
 * probability_t: Contains individual probability gates
 * and densities
 * 
 * TODO: Add and describe parameters
 */
typedef struct probability
{
    bool gate;
    prob_value_t prob_value;
} probability_t;

/**
 * Initializes a probability struct using one of
 * the prob_value_t flags
 * 
 * TODO: Add and describe parameters
 */
void PROB_init(probability_t *self, prob_value_t prob_value);

/**
 * Process function for probability
 * 
 * TODO: Add and describe parameters
 */
bool PROB_process(probability_t *self);

#endif /* PROBABILITY_H */