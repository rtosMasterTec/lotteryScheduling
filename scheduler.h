#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stdio.h>
#include <setjmp.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#include "def.h"
//#include "mathAlgo.h"
#define JB_SP 6

//
#define STACK_SIZE 1024

char stack [MAX_THREADS+1][STACK_SIZE];
typedef uint32_t address_t; // this is a machine address
// Struct to hold the scheduler information
typedef struct scheduler_s
{
   sigjmp_buf env[MAX_THREADS];
   unsigned threadID;
   bool taskInit[MAX_THREADS];
   char stack[MAX_THREADS][STACK_SIZE];
   struct itimerval timer;
} scheduler_t;
extern scheduler_t sData;

// public Functions

void schedulerInit();
void scheduler(int val);

#endif // __SCHEDULER_H__
