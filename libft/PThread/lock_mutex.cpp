#include "PThread.hpp"
#include <queue>
#include <atomic>
#include <unistd.h>

int pt_mutex_lock(t_mutex* mutex, int thread_id, int sleep_time, int max_sleep)
{
    while (true)
	{
        bool expected = false;
        if (mutex->wait_queue.empty() && mutex->lock.compare_exchange_strong(expected, true, std::memory_order_acquire)) {
            mutex->thread_id.store(thread_id, std::memory_order_release);
            return (0);
        }
        bool already_waiting = false;
        {
            std::queue<int> temp_queue = mutex->wait_queue;
            while (!temp_queue.empty())
			{
                if (temp_queue.front() == thread_id)
				{
                    already_waiting = true;
                    break ;
                }
                temp_queue.pop();
            }
        }
        if (!already_waiting)
            mutex->wait_queue.push(thread_id);
        usleep(sleep_time);
        sleep_time = std::min(sleep_time * 2, max_sleep);
        if (mutex->lock_released.load())
		{
            if (mutex->wait_queue.front() == thread_id)
			{
                mutex->wait_queue.pop();
                expected = false;
                if (mutex->lock.compare_exchange_strong(expected, true, std::memory_order_acquire)) {
                    mutex->thread_id.store(thread_id, std::memory_order_release);
                    return (0);
                }
            }
        }
    }
}
