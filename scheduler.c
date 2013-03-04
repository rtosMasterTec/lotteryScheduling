#include "scheduler.h"


static scheduler_t sData;
static bool initDone ;
   
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
int saveState(unsigned idx)
{
   // giving thread idx and value to return
  
   return sigsetjmp(sData.env[idx], 0);
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
// placeholder
int  invalidateThread() 
{
   return 0;
}
void schedulerInit()
{
   unsigned thread;
   initDone = true;
   for( thread = 1; thread < MAX_THREADS ; thread ++ )
   {
      memcpy( &sData.env[thread], &sData.env[0], sizeof( sigjmp_buf ) ); 
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
   int ret;
   int allDone;
   for( counter = 0; counter < 10* MAX_THREADS; counter++)
   {
      printf("Getting the alarm for thread: %d\n", sData.threadID );
      // Save the state
      ret = saveState(sData.threadID);
      if( ret != 0 )
      {
         allDone = invalidateThread(sData.threadID);
         // enters if all the threads had completed their job
         if(allDone  == 1 )
         {
            return;
         }
      }
      if( !initDone )
      {
         schedulerInit();
      }
      sData.threadID = lottery();
      // Set timer
      preemtiveTime();
      // Catch the timer signal
      signal(SIGALRM, scheduler);
      printf("sigalm passed\n");
      // Restore the state
      restoreState(sData.threadID);
   }
}


