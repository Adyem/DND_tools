#include <atomic>
#include <stdexcept>
#include "PThread.hpp"

thread_local const char *pt_errno_msg;

int pt_mutex_try_lock(t_mutex *mutex, int thread_id)
{
	pt_errno_msg = nullptr;
    try
    {
        if (!mutex)
            throw (std::runtime_error("pt_mutex_try_lock: The provided mutex pointer is null."));
        bool expected = false;
        if (mutex->lock.compare_exchange_strong(expected, true, std::memory_order_acquire))
        {
            mutex->thread_id.store(thread_id, std::memory_order_release);
            return (0);
        }
        return (1);
    }
    catch (const std::exception &error)
    {
		pt_errno_msg = error.what();
        return (-2);
    }
}
