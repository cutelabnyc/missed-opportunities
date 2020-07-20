#ifndef COUNTER_H
#define COUNTER_H

#include <stdint.h>

#ifdef __cplusplus  
extern "C" { 
#endif 
    
typedef struct {
    uint16_t _max;
    uint16_t _count;
} t_counter;

void counter_init(t_counter *self, uint16_t count_max);
void counter_process(t_counter *self, uint16_t *in, uint16_t *out);

#ifdef __cplusplus 
} 
#endif 

#endif // COUNTER_H

