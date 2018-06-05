#ifndef _AFL_CALL_H
#define _AFL_CALL_H

#include <stdint.h>

/* aflCall.c */
int startForkserver(int ticks);
char *getWork(uint32_t *sizep);
int startWork(uint32_t start, uint32_t end);
int doneWork(int val);
#endif
