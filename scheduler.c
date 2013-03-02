#include <stdio.h>
#include <setjmp.h>
#include "def.h"

static sigjmp_buf env[MAX_THREADS];


int restoreState(char idx)
{
   siglongjmp(env[idx], 1);
}
int saveState(char idx)
{
   // giving thread idx and value to return
   sigsetjmp(env[idx], 0);
}
/***************************************************
 *
 * Lottery Scheduler
 *
 ***************************************************/
int scheduler()
{
   // Save the state
   saveState();
   // Restore the state
   restoreState();
}


