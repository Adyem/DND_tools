#include <atomic>
#include "PThread.hpp"

int	pt_mutex_try_lock(t_mutex *mutex, int thread_id)
{
	bool	expected;

	expected = false;
	if (mutex->lock.compare_exchange_strong(expected, true, std::memory_order_acquire))
	{
		mutex->thread_id.store(thread_id, std::memory_order_release);
		return (0);
	}
	return (1);
}
