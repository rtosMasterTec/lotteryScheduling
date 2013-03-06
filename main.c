#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "scheduler.h"
#include "threads.h"
#include "configLoad.h"
#include "mathAlgo.h"
#include "print2screen.h"
#include <time.h>


threadData_t AThread;
threadData_t BThread;
threadData_t CThread;
threadData_t DThread;
threadData_t EThread;
threadData_t * threads_arr[5];
double percentage;

void init_threads();

int main( int argc, char **argv)
{
   printf("Hello world!\n");

   srand ( time(NULL) );

      readfile();
   // read percentage from file
   if(config.preemptive == 0) {

      percentage = config.quantum;
   } else
   {
      // Means its preemptive
      percentage = 100;
   }
   // set threads to active
   config.threadbuffer[0] = true;
   config.threadbuffer[1] = true;
   config.threadbuffer[2] = true;
   config.threadbuffer[3] = true;
   config.threadbuffer[4] = true;

threads_arr[0] = &AThread;
threads_arr[1] = &BThread;
threads_arr[2] = &CThread;
threads_arr[3] = &DThread;
threads_arr[4] = &EThread;

   initscr();
   init_threads();
   scheduler(0,&threads_arr);
   printw("\rscheduler ok\n");

/*
   threadData_t *currentThread;
   int i=0;
   while(i < 5){
      system("clear");
      switch(i) {
         case 0 : currentThread = &AThread; break;
         case 1 : currentThread = &BThread; break;
         case 2 : currentThread = &CThread; break;
         case 3 : currentThread = &DThread; break;
         case 4 : currentThread = &EThread; break;
         default : currentThread = &EThread; break;
      }
      calculatePI(currentThread,percentage);
      print2screen(&AThread,&BThread,&CThread,&DThread,&EThread,i);
      i = i +1;
      sleep(1);
   }
*/
   refresh();
   getch();
   endwin();
   return 0;
}

void init_threads(){

   AThread.totalTerms = 50*config.workLoad[0];
   AThread.currPiValue = 0;

   BThread.totalTerms = 50*config.workLoad[1];
   BThread.currPiValue = 0;

   CThread.totalTerms = 50*config.workLoad[2];
   CThread.currPiValue = 0;

   DThread.totalTerms = 50*config.workLoad[3];
   DThread.currPiValue = 0;

   EThread.totalTerms = 50*config.workLoad[4];
   EThread.currPiValue = 0;
}
