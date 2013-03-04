#include <stdio.h>
#include <setjmp.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

#include "def.h"
//#include "mathAlgo.h"

// sigjmp definitions for initialization
#define JB_SP 6
#define JB_PC 7

//
#define STACK_SIZE 1000
typedef unsigned long address_t; // this is a machine address
// Struct to hold the scheduler information
typedef struct scheduler_s
{
   sigjmp_buf env[MAX_THREADS];
   unsigned threadID;
   char stack[MAX_THREADS][STACK_SIZE];
   struct itimerval timer;
} scheduler_t;
