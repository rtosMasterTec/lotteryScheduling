#include "scheduler.h"

static volatile int dummy;


static scheduler_t sData;
static bool initDone ;
   
void algo()
{
   unsigned i;
   for(i = 0; i<10; i++ )
   {
      printf("Current thread is: %d, data: %d\n", sData.threadID, i);
      // wait until task slice ends
      dummy = 1 ;
      while(dummy ); 
   }
      
}


void restoreState(unsigned idx)
{
    siglongjmp(sData.env[idx], 1);
    return;
}
int saveState(unsigned idx)
{
   // giving thread idx and value to return
  
   return sigsetjmp(sData.env[idx], 1);
}

int lottery()
{
   // for now implementing round robin
   int winner=0;
   winner = sData.threadID+1;
   if( winner >=  MAX_THREADS )
      winner = 0;
   // calculate a winner
   return winner;
}
void preemtiveTime()
{
//   unsigned quantum;
//   quantum = 100;
//   ualarm(quantum);

   //getitimer(ITIMER_VIRTUAL,&sData.timer);
   sData.timer.it_value.tv_sec = 0;
   sData.timer.it_value.tv_usec = 100000;
   sData.timer.it_interval.tv_sec = 0;
   sData.timer.it_interval.tv_usec = 100000;
   setitimer(ITIMER_VIRTUAL, &sData.timer, 0);
   return;
}
// placeholder
int  invalidateThread() 
{
   return 0;
}
void schedulerInit()
{
   unsigned thread;
   initDone = true;
   for( thread = 0; thread < MAX_THREADS ; thread ++ )
   {
      sData.taskInit[thread] = false;
   }
   // init the timer with 0
   sData.timer.it_interval.tv_sec = 2;
   sData.timer.it_interval.tv_usec = 0;
   sData.timer.it_value.tv_sec = 2; // quantum value
   sData.timer.it_value.tv_usec=0;
}
/***************************************************
 *
 * Lottery Scheduler
 *
 ***************************************************/
void scheduler(int val)
{
   int ret;
   int allDone;
   printf("Getting the alarm for thread: %d\n", sData.threadID );
   // Save the state
   ret = saveState(sData.threadID);
   if( ret != 0 )
   {
      printf("restoring state %d\n", sData.threadID);
      // return to resume execution
      // in the thread
      return;
   }
   dummy = 0;
   if( !initDone )
   {
      printf("entering init\n");
      schedulerInit();
   }
   sData.threadID = lottery();
   // Catch the timer signal
   signal(SIGVTALRM, scheduler);
   // Set timer
   preemtiveTime();
   printf("sigalm passed\n");
   if( !sData.taskInit[sData.threadID] )
   {
      sData.taskInit[sData.threadID] = true;
      // when reaching this part the task finished execution
      // call function for first time
      algo();
      allDone = invalidateThread(sData.threadID);
      // enters if all the threads had completed their job
      if(allDone  == 1 )
      {
         return;
      }
   }
   else
   {
      // Restore the state
      restoreState(sData.threadID);
   }
   return;
}


