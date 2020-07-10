/**
 * opportunity.h —— (Max Ardito, 07/09/20)
 * 
 * Class representing the entire Missed Opportunity 
 * module's functionality. Instantiated globally in 
 * [/src/main.cpp], initialized, and then used for 
 * CV processing in the main loop.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * opportunity_t:
 * 
 * Main struct for the module. 
 * TODO: Add and describe parameters
 */
typedef struct opportunity
{
    uint16_t cv_in;
    uint16_t cv_out;
} opportunity_t;

/*==========================================*/

/**
 * opportunity_t* OP_init(void)
 * 
 * TODO: Add and describe parameters
 */
opportunity_t *OP_init(void);

/**
 * void *OP_free(void);
 * 
 * TODO: Add and describe parameters
 */
void *OP_free(void);

/**
 * void OP_setPins();
 * 
 * TODO: Add and describe parameters
 */
void OP_setPins();

/*==========================================*/

/**
 * void OP_read(opportunity_t *self);
 * 
 * TODO: Add and describe parameters
 */
void OP_read(opportunity_t *self);

/**
 * void OP_process(opportunity_t *self);
 * 
 * TODO: Add and describe parameters
 */
void OP_process(opportunity_t *self);

/**
 * void OP_write(opportunity_t *self);
 * 
 * TODO: Add and describe parameters
 */
void OP_write(opportunity_t *self);
