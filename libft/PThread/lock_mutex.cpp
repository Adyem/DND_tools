#include "PThread.hpp"
#include "../Errno/errno.hpp"
#include <unistd.h>
#include <algorithm>

thread_local int ft_errno;

int pt_mutex_lock(t_mutex* mutex, int thread_id)
{
    ft_errno = SUCCESS;
    int sleep_time = SLEEP_TIME;
    const int max_sleep = MAX_SLEEP;

    while (true)
    {
        if (mutex->wait_queue_start == mutex->wait_queue_end &&
            mutex->lock == false)
        {
            if (__sync_bool_compare_and_swap(&mutex->lock, false, true))
            {
                mutex->thread_id = thread_id;
                return (SUCCESS);
            }
        }
        bool already_waiting = false;
        int start = mutex->wait_queue_start;
        int end = mutex->wait_queue_end;
        while (start != end)
        {
            if (mutex->wait_queue[start] == thread_id)
            {
                already_waiting = true;
                break ;
            }
            start = (start + 1) % 128;
        }
        if (!already_waiting)
        {
            int next_end = (mutex->wait_queue_end + 1) % 128;
            if (next_end == mutex->wait_queue_start)
            {
                ft_errno = PT_ERR_QUEUE_FULL;
                return (-1);
            }
            mutex->wait_queue[mutex->wait_queue_end] = thread_id;
            mutex->wait_queue_end = next_end;
        }
        usleep(sleep_time);
        sleep_time = std::min(sleep_time * 2, max_sleep);
        if (mutex->lock_released)
        {
            if (mutex->wait_queue[mutex->wait_queue_start] == thread_id)
            {
                int next_start = (mutex->wait_queue_start + 1) % 128;
                mutex->wait_queue_start = next_start;
                if (__sync_bool_compare_and_swap(&mutex->lock, false, true))
                {
                    mutex->thread_id = thread_id;
                    return (SUCCESS);
                }
            }
        }
    }
    return (SUCCESS);
}
