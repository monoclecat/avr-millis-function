/* 
The millis() function known from Arduino
Calling millis() will return the milliseconds since the program started

Tested on atmega328p

Using content from http://www.adnbr.co.uk/articles/counting-milliseconds
Author: Monoclecat, https://github.com/monoclecat/avr-millis-function

REMEMBER: Add sei(); after init_millis() to enable global interrupts!
 */

#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>



volatile unsigned long timer1_millis; 
//NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1). It will roll over to 0 after reaching its maximum value.

ISR(TIMER1_COMPA_vect)
{
  timer1_millis++;  
}

void init_millis(unsigned long f_cpu)
{
  unsigned long ctc_match_overflow;
  
  ctc_match_overflow = ((f_cpu / 1000) / 8); //when timer1 is this value, 1ms has passed
    
  // (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
  TCCR1B |= (1 << WGM12) | (1 << CS11);
  
  // high byte first, then low byte
  OCR1AH = (ctc_match_overflow >> 8);
  OCR1AL = ctc_match_overflow;
 
  // Enable the compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
 
  //REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}

unsigned long millis ()
{
  unsigned long millis_return;
 
  // Ensure this cannot be disrupted
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    millis_return = timer1_millis;
  }
  return millis_return;
} 