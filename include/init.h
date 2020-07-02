#include <Arduino.h>

#define ANALOG_IN A5
#define DIGITAL_OUT 9
#define LED_PIN 13

/**
* NOTE: The input voltage should go through some sort of
* calibration process where a number that's not arbitrary 
* should be the real marker of threshold. 
*/
#define INPUT_THRESHOLD 300

typedef struct opportunity
{
    uint8_t cv_in;
    // NOTE: Currently CV only oscillates between
    // HIGH and LOW digital output values. It might be
    // better to also use voltage values for the output
    bool cv_out;
} opportunity_t;

opportunity *OP_init(void);
void *OP_free(void);

void OP_read(opportunity *opt, uint8_t cv_in);
void OP_process(opportunity *opt);