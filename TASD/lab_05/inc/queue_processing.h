#ifndef QUEUE_PROCESSING_H
#define QUEUE_PROCESSING_H

#include "defines.h"
#include "useful_funcs.h"
#include "queue.h"

void queue_simulation_work(queue_t *queue, int is_queue_list, double t1_start, double t1_end, double t2_start, double t2_end, int repeats);

#endif
