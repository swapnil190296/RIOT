/*
 * AFL hypercalls
 *
 * Compile with -DTEST to take inputs from stdin without using hypercalls.
 */
#include "afl_call.h"

extern int noHyperCall;

// On arm32, sizeof(uint32_t) == 4
#define SZ 1024 // TODO may be too large for iot OS
static uint32_t bufsz = SZ; 
static char buf[SZ];

// defined in asm.s
uint32_t aflCall(uint32_t a0, uint32_t a1, uint32_t a2);


int startForkserver(int ticks) {
// @param ticks: either enable or disable the CPUs timer in each forked child
    if(noHyperCall)
        return 0;
    return aflCall(1, ticks, 0);
}

char *getWork(uint32_t *sizep) {
/*
    if(noHyperCall)
        // can get input from serial on real dev
        *sizep = read(0, buf, bufsz);
    else
*/
        *sizep = aflCall(2, (uint32_t)buf, bufsz);
    return buf;
}

/* buf should point to uint32_t[2] */
int startWork(uint32_t start, uint32_t end) {
    if(noHyperCall)
        return 0;
    return aflCall(3, start, end);
}

int doneWork(int val) {
    if(noHyperCall)
        return 0;
    return aflCall(4, (uint32_t)val, 0);
}
