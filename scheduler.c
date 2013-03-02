#include <stdio.h>
#include <setjmp.h>
#include "def.h"

static sigjmp_buf env[MAX_THREADS];


void restoreState(char idx)
{
   siglongjmp(env[idx], 1);
   return;
}
void saveState(char idx)
{
   // giving thread idx and value to return
   sigsetjmp(env[idx], 0);
   return;
}

int lottery()
{
   int winner=0;
   // calculate a winner
   return winner;
}
/***************************************************
 *
 * Lottery Scheduler
 *
 ***************************************************/
int scheduler()
{
   // Save the state
   saveState(threadID);
   threadID = lottery();
   // Restore the state
   restoreState(threadID);
}


