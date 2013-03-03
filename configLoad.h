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
} config_t;


