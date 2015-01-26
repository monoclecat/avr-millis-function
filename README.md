# avr-millis-function
Just like the <code>millis()</code> function in Arduino, this function returns 
the time in milliseconds since the program started.

This function has only been tested on the atmega328p, but may work on many other AVRs as well.

Implementing this function is easy - take a look at the example:

1) First you must initiate the clock with <code>init_millis()</code>

2) After calling <code>init_millis()</code>, call <code>sei()</code> to enable global interrupts

3) Use <code>millis()</code> whenever you like to get the time in milliseconds since the program started

Complications that may arise:
A problem I faced was that I got this error messsage when compiling:

    /usr/local/CrossPack-AVR-20131216/avr/include/millis.c: In function 'millis':
    /usr/local/CrossPack-AVR-20131216/avr/include/millis.c:49:3: error: 'for' loop initial declarations are only allowed in C99 mode
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        ^
    /usr/local/CrossPack-AVR-20131216/avr/include/millis.c:49:3: note: use option -std=c99 or -std=gnu99 to compile your code
    make: *** [main.o] Error 1

The error is nicely explained [here](http://cboard.cprogramming.com/c-programming/162799-what-c99-mode.html) and can be fixed by 
adding <code>-std=c99</code> or <code>-std=gnu99</code> to the command <code>avr-gcc</code> when compiling your code.

For any questions write me an email at: contact@monoclecat.de
