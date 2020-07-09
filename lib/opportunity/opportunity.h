#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct opportunity
{
    uint16_t cv_in;
    uint16_t cv_out;

    bool isGated;
    bool zeroCrossing;
} opportunity_t;

opportunity_t *OP_init(void);
void *OP_free(void);

void OP_setPins();

void OP_read(opportunity_t *self);
void OP_process(opportunity_t *self);
void OP_write(opportunity_t *self);
