/*#include <bool.h>*/
#include "def.h"

typedef struct config_s
{
   unsigned preemptive;
   unsigned tickets[MAX_THREADS];
   unsigned workLoad[MAX_THREADS];
   unsigned quantum;
   unsigned totaltickets;
   unsigned totalwork;
} config_t;


