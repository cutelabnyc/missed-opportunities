#include <Arduino.h>

#define ANALOG_IN A3   // ANALOG A5, A4, A3, A2
#define DIGITAL_OUT 10 // DIGITAL 3, 9, 10, 11
#define LED_PIN 13

typedef struct opportunity
{
    uint16_t cv_in;
    uint16_t cv_out;

    bool isGated;
} opportunity_t;

opportunity *OP_init(void);
void *OP_free(void);

void OP_read(opportunity *self, uint16_t cv_in);
void OP_process(opportunity *self);