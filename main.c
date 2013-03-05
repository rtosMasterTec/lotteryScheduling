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

void init_threads();

int main( int argc, char **argv)
{
   printf("Hello world!\n");

   srand ( time(NULL) );

   readfile();

config.threadbuffer[0] = true;
config.threadbuffer[1] = true;
config.threadbuffer[2] = true;
config.threadbuffer[3] = true;
config.threadbuffer[4] = true;

   scheduler();

	init_threads();
initscr();
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
	calculatePI(currentThread);
	print2screen(&AThread,&BThread,&CThread,&DThread,&EThread,i);
	i = i +1;
sleep(1);
}
    refresh();
    getch();
    endwin();
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
