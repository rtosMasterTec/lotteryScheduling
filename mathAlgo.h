#ifndef __MATHALGO_H__
#define __MATHALGO_H__

#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>
//#include "scheduler.h" 

typedef struct threadData_s {
    int totalTerms;
    int currTerm;
    double currPiValue;
} threadData_t;



void calculatePI(threadData_t *t, double percentage);

#endif // __MATHALGO_H__
