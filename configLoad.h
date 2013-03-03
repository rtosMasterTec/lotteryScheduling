#include <stdbool.h>
#include "def.h"

typedef struct config_s
{
   bool preemtive;
   unsigned tickets[MAX_THREADS];
   unsigned workLoad[MAX_THREADS];
   unsigned quantum;
} config_t;


