#include <stdio.h>
#include <setjmp.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

#include "def.h"
//#include "mathAlgo.h"

//
#define STACK_SIZE 1024

typedef uint32_t address_t; // this is a machine address
// Struct to hold the scheduler information
typedef struct scheduler_s
{
   sigjmp_buf env[MAX_THREADS];
   unsigned threadID;
   char stack[MAX_THREADS][STACK_SIZE];
   struct itimerval timer;
} scheduler_t;

// public Functions

void schedulerInit();
void scheduler();
