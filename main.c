#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "scheduler.h"
#include "threads.h"
#include "configLoad.h"
#include "mathAlgo.h"
#include "print2screen.h"

threadData_t AThread;
threadData_t BThread;
threadData_t CThread;
threadData_t DThread;
threadData_t EThread;

void init_threads();

int main( int argc, char **argv)
{
   printf("Hello world!\n");

   scheduler(0);

   return 0;
}

void init_threads(){
   AThread.totalTerms = 20;
   AThread.currPiValue = 0;
   
   BThread.totalTerms = 2000;
   BThread.currPiValue = 0;


   CThread.totalTerms = 500;
   CThread.currPiValue = 0;

   DThread.totalTerms = 1000;
   DThread.currPiValue = 0;

   EThread.totalTerms = 100;
   EThread.currPiValue = 0;
}
