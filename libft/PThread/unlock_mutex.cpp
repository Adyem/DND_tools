#include "PThread.hpp"
#include <atomic>
#include <unistd.h>

#include <stdexcept>

thread_local const char *pt_errno_msg;

int pt_mutex_unlock(t_mutex *mutex, int thread_id)
{
    pt_errno_msg = nullptr;
    try
    {
        if (!mutex)
            throw (std::runtime_error("pt_mutex_unlock: The provided mutex pointer is null."));
        if (mutex->thread_id.load(std::memory_order_acquire) != thread_id)
            throw (std::runtime_error("pt_mutex_unlock: Thread does not own the lock."));
        mutex->thread_id.store(-1, std::memory_order_release);
        mutex->lock.store(false, std::memory_order_release);
        mutex->lock_released.store(true);
        return (0);
    }
    catch (const std::exception &error)
    {
        pt_errno_msg = error.what();
        return (-1);
    }
}
