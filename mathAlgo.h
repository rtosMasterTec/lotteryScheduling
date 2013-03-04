#ifndef __MATHALGO_H__
#define __MATHALGO_H__

#include <stdio.h>
#include <math.h>

typedef struct threadData_s {
    int totalTerms;
    int currTerm;
    double currPiValue;
} threadData_t;

void calculatePI(threadData_t *t);

#endif // __MATHALGO_H__
