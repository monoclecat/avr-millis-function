#ifndef _MILLIS_H_
#define _MILLIS_H_

volatile unsigned long timer1_millis;
//NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1). It will roll over to 0 after reaching its maximum value.

ISR(TIMER1_COMPA_vect);
void init_millis(unsigned long f_cpu);
unsigned long millis (void);

#endif
