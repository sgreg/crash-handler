#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "crash.h"

void foo(uint8_t value);

int
main(void)
{
    uint8_t val;

    // set random number generator's seed to the current timestamp
    srand(time(NULL));

    // loop forever and pass random values [0-255] to foo()
    while (1) {
        val = rand() & 0xff;
        foo(val);
    }

    return 0;
}

void foo(uint8_t value) {
    // check given random value is max 100 and print it
    if (value <= 100) {
        printf("all good, val = %d\n", value);
    } else {
        // call the crash handler otherwise
        crash("check for value failed: %d", value);
    }
}

