#include "queue_processing.h"

double get_time(const double left_limit, const double right_limit)
{
    double rnd = (double)rand() / (double)RAND_MAX;

    return (right_limit - left_limit) * rnd + left_limit;
}

void queue_simulation_work(queue_t *queue,
                           int is_queue_list, double t1_start, double t1_end, double t2_start, double t2_end, int repeats)
{
    int rc;
    int in_tasks = 0;
    int out_tasks = 0;
    int failed_tasks = 0;
    int calls = 0;
    double service_time = 0;
    double hold_time = 0;

    double time_in = get_time(t1_start, t1_end);
    double time_out = -1;

    task_t task_todo;

    int reused_memory = 0;
    int new_memory = 0;
    int which;

    int overall_len = 0;

    while (out_tasks < 1000)
    {
        if (time_out < 0 || time_in < time_out)
        {
            if (time_out < 0)
            {
                hold_time += time_in;
            }

            service_time += time_in;
            time_out -= time_in;
            time_in = get_time(t1_start, t1_end);

            task_t task = {.count = 0,
                           .time_out = get_time(t2_start, t2_end)};

            rc = queue_push(queue, is_queue_list, task);

            if (rc != EXIT_SUCCESS)
            {
                // printf("ERROR: somthing went wrong when el push (err code: %d)\n", rc);
                failed_tasks++;
            }
            else
            {
                if (is_queue_list)
                {
                    which = check_if_mem_reused(&queue->list);
                    if (which)
                    {
                        reused_memory++;
                    }
                    else
                    {
                        new_memory++;
                    }
                }

                in_tasks++;
            }

            if (time_out < 0 && queue_len(queue, is_queue_list))
            {
                queue_pop(queue, is_queue_list, &task_todo);
                time_out = task_todo.time_out;
            }
        }
        else
        {
            time_in -= time_out;
            service_time += time_out;
            time_out = 0;

            task_todo.count++;
            calls++;

            if (task_todo.count < repeats)
            {
                task_todo.time_out = get_time(t2_start, t2_end);

                rc = queue_push(queue, is_queue_list, task_todo);

                if (rc != EXIT_SUCCESS)
                {
                    // printf("ERROR: somthing went wrong when el push (err code: %d)\n", rc);
                    failed_tasks++;
                }
                else
                {
                    if (is_queue_list)
                    {
                        which = check_if_mem_reused(&queue->list);
                        if (which)
                        {
                            reused_memory++;
                        }
                        else
                        {
                            new_memory++;
                        }
                    }
                }
            }
            else
            {
                overall_len += queue_len(queue, is_queue_list);
                out_tasks++;
                if (out_tasks % 100 == 0)
                {
                    printf("\n----------\n"
                           "Processed %d tasks.\n"
                           "Queue len: %zu\n"
                           "Average queue len: %.2lf\n"
                           "----------\n",
                           out_tasks, queue_len(queue, is_queue_list), (double)overall_len / out_tasks);
                }
            }

            if (queue_len(queue, is_queue_list) == 0)
            {
                time_out = -1;
            }
            else
            {
                queue_pop(queue, is_queue_list, &task_todo);
                time_out = task_todo.time_out;
            }
        }
    }

    double expected_time;
    if ((t1_start + t1_end) / 2 * NEED_TOTAL_OUT_COUNT > (t2_start + t2_end) / 2 * repeats * NEED_TOTAL_OUT_COUNT)
    {
        expected_time = (t1_start + t1_end) / 2 * NEED_TOTAL_OUT_COUNT;
    }
    else
    {
        expected_time = calls * (t2_start + t2_end) / 2;
    }
    double delta = fabs(service_time - expected_time) / expected_time * 100;

    printf("Machine working time: %.2lf (Expected working time: %.2lf, inaccuracy: %.2lf%%)\n"
           "Number of tasks entered: %d\n"
           "Number of tasks submitted: %d\n"
           "Number of failed tasks: %d\n"
           "The number of machine triggers: %d\n"
           "Machine downtime: %.2lf\n",
           service_time, expected_time, delta,
           in_tasks, out_tasks, failed_tasks, calls, hold_time);

    if (is_queue_list)
        printf("The number of addresses taken from used memory: %d\n"
               "The number of addresses taken from new memory: %d\n",
               reused_memory, new_memory);
}
