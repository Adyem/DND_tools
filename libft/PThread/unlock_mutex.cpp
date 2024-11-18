#include "PThread.hpp"

thread_local const char *pt_errno_msg;

int pt_mutex_unlock(t_mutex *mutex, int thread_id)
{
    pt_errno_msg = nullptr;

    if (!mutex)
    {
        pt_errno_msg = "pt_mutex_unlock: The provided mutex pointer is null.";
        return (-1);
    }
    if (mutex->thread_id != thread_id)
    {
        pt_errno_msg = "pt_mutex_unlock: Thread does not own the lock.";
        return (-1);
    }
    mutex->thread_id = -1;
    mutex->lock = false;
    mutex->lock_released = true;
    return (0); 
}
