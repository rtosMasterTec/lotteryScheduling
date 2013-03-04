#ifndef PRINT2SCREEN_H_
#define PRINT2SCREEN_H_

#include <stdio.h>
#include <unistd.h>
#include "mathAlgo.h"

void print2screen(
	threadData_t *ta,
	threadData_t *tb,
	threadData_t *tc,
	threadData_t *td,
	threadData_t *te,
	int active_thread_n
);

#endif
