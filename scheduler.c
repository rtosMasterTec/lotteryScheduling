#include "scheduler.h"
#include <stdio.h>   /* required for file operations */
#include <time.h>
#include <stdbool.h>
#include "configLoad.h"

static volatile int dummy;
scheduler_t sData;
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
  

   ret = sigsetjmp(sData.env[idx], 1);
   // modify the stack to not interfere with current execution
   if( 5 != idx )
   {
      //sData.env[idx][JB_SP] = (struct __jmp_buf_tag) (&stack[idx][STACK_SIZE -1]);
   }
   return ret;
}

int lottery()
{
   // for now implementing round robin
   int winner=0;
   winner = sData.threadID+1;
   //winner =0;
   if( winner >=  MAX_THREADS )
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
      printf("task %d is done\n", sData.threadID);
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


