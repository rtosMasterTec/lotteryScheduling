#include "scheduler.h"
#include <stdio.h>   /* required for file operations */
#include <time.h>
#include <stdbool.h>
#include "configLoad.h"
#include "print2screen.h"
#include "mathAlgo.h"

static volatile int dummy;
scheduler_t sData;
static bool initDone ;
void init_threads();
threadData_t Athread;
threadData_t Bthread;
threadData_t Cthread;
threadData_t Dthread;
threadData_t Ethread;



void init_threads(){

   // set threads to active
   config.threadbuffer[0] = true;
   config.threadbuffer[1] = true;
   config.threadbuffer[2] = true;
   config.threadbuffer[3] = true;
   config.threadbuffer[4] = true;

   // put threads into array
/*   threads_arr[0] = &Athread;
   threads_arr[1] = &Bthread;
   threads_arr[2] = &Cthread;
   threads_arr[3] = &Dthread;
   threads_arr[4] = &Ethread;*/

   // Load workload units into global structures
   Athread.totalTerms = 50*config.workLoad[0];
   Athread.currPiValue = 0;
   printf("ATotalTerms %d\n", Athread.totalTerms);
   Bthread.totalTerms = 50*config.workLoad[1];
   Bthread.currPiValue = 0;
   printf("BTotalTerms %d\n", Bthread.totalTerms);
   Cthread.totalTerms = 50*config.workLoad[2];
   Cthread.currPiValue = 0;
   printf("CTotalTerms %d\n", Cthread.totalTerms);
   Dthread.totalTerms = 50*config.workLoad[3];
   Dthread.currPiValue = 0;
   printf("DTotalTerms %d\n", Dthread.totalTerms);
   Ethread.totalTerms = 50*config.workLoad[4];
   Ethread.currPiValue = 0;
   printf("ETotalTerms %d\n", Ethread.totalTerms);
}
   
void algo()
{
   double percentage;
   threadData_t currentThread;	

   // read percentage from file
   if(config.preemptive == 0) {

      percentage = config.quantum;
   } else
   {
      // Means its preemptive
      percentage = 100;
   }
   
   if(sData.threadID == 0) { currentThread = Athread; }
   if(sData.threadID == 1) { currentThread = Bthread; }
   if(sData.threadID == 2) { currentThread = Cthread; }
   if(sData.threadID == 3) { currentThread = Dthread; }
   if(sData.threadID == 4) { currentThread = Ethread; }

   calculatePI(&currentThread , percentage);

// TODO ERASE THE FOLLOWING LINES FOR PRODUCTION CODE
/*   unsigned i;
   for(i = 0; i<10; i++ )
   {
      printf("Current thread is: %d, data: %d\n", sData.threadID, i);
      // wait until task slice ends
      dummy = 1 ;
      while(dummy ); 
   }*/
      
}


void restoreState(unsigned idx)
{
   int retval = 1;
   if(5 == idx)
   {
      retval = 5;

   }
   siglongjmp(sData.env[idx], retval);
   return;
}
int saveState(unsigned idx)
{
   // giving thread idx and value to return
   int ret;
   void * ptr;
  

   ret = sigsetjmp(sData.env[idx], 1);
   // modify the stack to not interfere with current execution
   if( 0 != ret && 5 != idx )
   {
      //ptr = (&sData.env[idx]+JB_SP );
      //*ptr = (uint32_t ) (&stack[idx][STACK_SIZE -1]);
   }
   return ret;
}

int lottery()
{
   // for now implementing round robin
   int winner=0;
   winner = sData.threadID+1;
   winner =0;
   if( winner >= MAX_THREADS    )
      winner = 0;
   // calculate a winner
   return winner;
}

//unsigned lottery (void) 
//{
//
//    unsigned totalactivos = 0;
//    unsigned winthread = 0;
//    unsigned winner = 0;
//
//    /* En caso ningun thread este activo */
//    if (!config.threadbuffer[0] && !config.threadbuffer[1] && !config.threadbuffer[2] && !config.threadbuffer[3] && !config.threadbuffer[4]) {
//        winthread = 0;
//        winner = 0;
//        return winthread;
//    }
//
//    /* Determina el total de tiquetes que seran evaluados para obtener el ganador */
//    if (config.threadbuffer[0]) totalactivos = config.tickets[0];
//    if (config.threadbuffer[1]) totalactivos = (totalactivos + config.tickets[1]);
//    if (config.threadbuffer[2]) totalactivos = (totalactivos + config.tickets[2]);
//    if (config.threadbuffer[3]) totalactivos = (totalactivos + config.tickets[3]);
//    if (config.threadbuffer[4]) totalactivos = (totalactivos + config.tickets[4]);
//
//    /* Realiza la rifa y se obtiene de manera aleatoria el boleto ganador */
//    do {
//        winner = rand() % totalactivos;
//    } while (winner == 0);
//
//    /* Determina segun el boleto cual es el thread ganador */
//    /* Casos en q puede ganar thread 1 */
//    if (config.threadbuffer[0] && winner <= config.tickets[0]) {
//        winthread = 1;
//        return winthread;
//    }
//
//    /* Casos en q puede ganar thread 2 */
//
//    if (config.threadbuffer[0] && config.threadbuffer[1] && winner <= (config.tickets[1]+config.tickets[0])) {
//        winthread = 2;
//        return winthread;
//    }
//    if (!config.threadbuffer[0] && config.threadbuffer[1] && winner <= config.tickets[1]) {
//        winthread = 2;
//        return winthread;
//    }
//
//    /* Casos en q puede ganar thread 3 */
//
//    if (config.threadbuffer[0]) {
//        if (config.threadbuffer[1]) {
//            if (config.threadbuffer[2] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[2])) {
//                winthread = 3;
//                return winthread;
//            }
//        }
//        if (!config.threadbuffer[1]) {
//            if (config.threadbuffer[2] && winner <= (config.tickets[0]+config.tickets[2])) {
//                winthread = 3;
//                return winthread;
//            }
//        }
//    }
//    if (!config.threadbuffer[0]) {
//        if (config.threadbuffer[1]) {
//            if (config.threadbuffer[2] && winner <= (config.tickets[1]+config.tickets[2])) {
//                winthread = 3;
//                return winthread;
//            }
//        }
//        if (!config.threadbuffer[1]) {
//            if (config.threadbuffer[2] && winner <= config.tickets[2]) {
//                winthread = 3;
//                return winthread;
//            }
//        }
//    }
//
//    /* Casos en q puede ganar thread 4 */
//
//    if (config.threadbuffer[0]) {
//        if (config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[2]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//        }
//        if (!config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[0]+config.tickets[2]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[0]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//        }
//    }
//    if (!config.threadbuffer[0]) {
//        if (config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[1]+config.tickets[2]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[1]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//        }
//        if (!config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= (config.tickets[2]+config.tickets[3])) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3] && winner <= config.tickets[3]) {
//                    winthread = 4;
//                    return winthread;
//                }
//            }
//        }
//    }
//
//    /* Casos en q puede ganar thread 5 */
//
//    if (config.threadbuffer[0]) {
//        if (config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[2]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[2]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[1]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//        }
//        if (!config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[2]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[2]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[0]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//        }
//    }
//    if (!config.threadbuffer[0]) {
//        if (config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[1]+config.tickets[2]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[1]+config.tickets[2]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[1]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[1]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//        }
//        if (!config.threadbuffer[1]) {
//            if (config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[2]+config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[2]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//            if (!config.threadbuffer[2]) {
//                if (config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= (config.tickets[3]+config.tickets[4])) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//                if (!config.threadbuffer[3]) {
//                    if (config.threadbuffer[4] && winner <= config.tickets[4]) {
//                        winthread = 5;
//                        return winthread;
//                    }
//                }
//            }
//        }
//    }
//
//    return winthread;
//}

void preemtiveTime()
{
//   unsigned quantum;
//    quantum = config.quantum;
//   ualarm(quantum);

   //getitimer(ITIMER_VIRTUAL,&sData.timer);
   printf("setting the timer\n");
   sData.timer.it_value.tv_sec = 0;
   sData.timer.it_value.tv_usec = 100000;
   sData.timer.it_interval.tv_sec = 0;
   sData.timer.it_interval.tv_usec = 100000;
   setitimer(ITIMER_VIRTUAL, &sData.timer, 0);
   return;
}
// placeholder
bool invalidateThread (unsigned ID) 
{
    bool Done = false;

    if (ID == 1) config.threadbuffer[0] = false;
    if (ID == 2) config.threadbuffer[1] = false;
    if (ID == 3) config.threadbuffer[2] = false;
    if (ID == 4) config.threadbuffer[3] = false;
    if (ID == 5) config.threadbuffer[4] = false;

    Done = !(config.threadbuffer[0] | config.threadbuffer[1] | config.threadbuffer[2] | config.threadbuffer[3] | config.threadbuffer[4]);

    return Done;
}

void schedulerInit()
{
   unsigned thread;
   initDone = true;
   for( thread = 0; thread < MAX_THREADS ; thread ++ )
   {
      sData.taskInit[thread] = false;
   }
   init_threads();

}
/***************************************************
 *
 * Lottery Scheduler
 *
 ***************************************************/
void scheduler(int v)
{
   int ret;
   bool allDone = false;
   printf("Getting the alarm for thread: %d\n", sData.threadID );
   // Save the state
   ret = saveState(sData.threadID);
   if( 1 == ret  )
   {
      printf("restoring state %d\n", sData.threadID);
      // return to resume execution
      // in the thread
      return;
   }
   if( 5 == ret )
   {
      // the case to return from the scheduler to the main
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
      printf("initializing thread: %d\n", sData.threadID);
      sData.taskInit[sData.threadID] = true;
      // when reaching this part the task finished execution
      // call function for first time
      algo();
initscr();
      print2screen(&Athread,&Bthread,&Cthread,&Dthread,&Ethread,sData.threadID);
      printf("\ntask %d is done\n", sData.threadID);
      allDone = invalidateThread(sData.threadID);
      // enters if all the threads had completed their job
      allDone = 1;// tmp measure
      //change the stack ptr to the old position
      restoreState(6);
      if(allDone)
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




