#include "scheduler.h"


static scheduler_t sData;
   
void algo()
{
   unsigned i;
   for( i = sData.threadID ; i<10 ; i++)
   {
      printf("Current thread is: %d, data: %d\n", sData.threadID, i);
      sleep(1);
   }
}


void restoreState(unsigned idx)
{
   siglongjmp(sData.env[idx], 1);
   return;
}
void saveState(unsigned idx)
{
   // giving thread idx and value to return
   sigsetjmp(sData.env[idx], 0);
   return;
}

int lottery()
{
   // for now implementing round robin
   int winner=sData.threadID+1;
   if( sData.threadID >5 )
      winner = 0;
   // calculate a winner
   return winner;
}
void preemtiveTime()
{
   setitimer(ITIMER_VIRTUAL, &sData.timer, 0);
   return;
}
void schedulerInit()
{
   unsigned sp, pc;
   unsigned thread;
   for( thread = 0 ; thread < MAX_THREADS ; thread++ )
   {
      sp = (address_t) sData.stack[thread] + STACK_SIZE - sizeof(address_t);
      pc = ( unsigned ) &algo;
      // Saving a generic environment
      sigsetjmp(sData.env[thread],1);
      // Modify the Env to have the stack assigned to each thread
      (sData.env[thread]->__jmpbuf)[JB_SP] = sp;
      // Modify the PC to the start of the function to run in the thread
      (sData.env[thread]->__jmpbuf)[JB_PC] = pc;
   // have a clean mask for the thread
   sigemptyset(&sData.env[thread]->__saved_mask);
   }

   // init the timer with 0
   sData.timer.it_interval.tv_sec = 0;
   sData.timer.it_interval.tv_usec = 0;
   sData.timer.it_value.tv_sec = 2; // quantum value
   sData.timer.it_value.tv_usec=0;
}
/***************************************************
 *
 * Lottery Scheduler
 *
 ***************************************************/
void scheduler()
{
   static unsigned counter;
   for( counter = 0; counter < 10* MAX_THREADS; counter++)
   {
      printf("Getting the alarm for thread: %d\n", sData.threadID );
      // Save the state
      saveState(sData.threadID);
      sData.threadID = lottery();
      // Set timer
      preemtiveTime();
      // Catch the timer signal
      signal(SIGALRM, scheduler);
      // Restore the state
      restoreState(sData.threadID);
   }
}


