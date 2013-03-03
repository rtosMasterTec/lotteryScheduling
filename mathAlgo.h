#include <stdio.h>
#include <math.h>

typedef struct threadData_s {
    int totalTerms;
    int currTerm;
    double currPiValue;
} threadData_t;

void calculatePI(threadData_t *t);