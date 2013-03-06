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

// threadData_t AThread;
//threadData_t BThread;
//threadData_t CThread;
//threadData_t DThread;
//threadData_t EThread;
threadData_t * threads_arr[5];

void init_threads();

int main( int argc, char **argv)
{
   // needed random calculation
   srand ( time(NULL) );
   readfile();
   init_threads();
   sData.threadID = 5;
   initscr();
   scheduler(0);

   readfile();
   
//   scheduler(0,&threads_arr);
  // printw("\rscheduler ok\n");

   refresh();
   getch();
   endwin();
   return 0;
}

