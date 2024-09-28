#include "PThread.hpp"
#include <atomic>
#include <unistd.h>

int		pt_mutex_unlock(t_mutex *mutex, int thread_id)
{
	if (mutex->thread_id.load(std::memory_order_acquire) != thread_id)
		return (-1);
	mutex->thread_id.store(-1, std::memory_order_release);
	mutex->lock.store(false, std::memory_order_release);
	mutex->lock_released.store(true);
	return (0);
}
