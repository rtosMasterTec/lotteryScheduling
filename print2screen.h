#ifndef __PRINT2SCREEN_H__
#define __PRINT2SCREEN_H__

#include <stdio.h>
#include <unistd.h>
#include "mathAlgo.h"
#include "curses.h"

void print2screen(
	threadData_t *ta,
	threadData_t *tb,
	threadData_t *tc,
	threadData_t *td,
	threadData_t *te,
	int active_thread_n
);

#endif // __PRINT2SCREEN_H__
