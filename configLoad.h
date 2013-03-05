#include <stdio.h>   /* required for file operations */
#include <stdlib.h>
#include <stdbool.h>
#include "def.h"

typedef struct config_s
{
   bool preemptive;
   unsigned tickets[MAX_THREADS];
   unsigned workLoad[MAX_THREADS];
   unsigned quantum;
   unsigned totaltickets;
   unsigned totalwork;
   unsigned threadbuffer[MAX_THREADS];
} config_t;

extern config_t config;


