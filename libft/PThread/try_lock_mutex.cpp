#include "PThread.hpp"

thread_local const char *pt_errno_msg;

int pt_mutex_try_lock(t_mutex *mutex, int thread_id)
{
    pt_errno_msg = nullptr;

    if (!mutex)
    {
        pt_errno_msg = "pt_mutex_try_lock: The provided mutex pointer is null.";
        return (-2);
    }
    if (__sync_bool_compare_and_swap(&mutex->lock, false, true))
    {
        mutex->thread_id = thread_id;
        return (0);
    }

    return (1);
}
