#include "PThread.hpp"
#include <queue>
#include <atomic>
#include <unistd.h>

thread_local const char *pt_errno_msg;

int pt_mutex_lock(t_mutex* mutex, int thread_id, int sleep_time, int max_sleep)
{
	pt_errno_msg = nullptr;
    while (true)
    {
        bool expected = false;
        try
		{
            if (mutex->wait_queue.empty() &&
                mutex->lock.compare_exchange_strong(expected, true, std::memory_order_acquire))
			{
                mutex->thread_id.store(thread_id, std::memory_order_release);
                return (0);
            }
        }
		catch (const std::exception& error)
		{
			pt_errno_msg = error.what();
            return (-1);
        }
        bool already_waiting = false;
        try
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
		catch (const std::exception& error)
		{
			pt_errno_msg = error.what();
            return (-1);
        }
        try
		{
            if (!already_waiting)
                mutex->wait_queue.push(thread_id);
        }
		catch (const std::exception& error)
		{
			pt_errno_msg = error.what();
            return (-1);
        }
        usleep(sleep_time);
        sleep_time = std::min(sleep_time * 2, max_sleep);
		try
		{
            if (mutex->lock_released.load())
            {
                if (!mutex->wait_queue.empty() && mutex->wait_queue.front() == thread_id)
                {
                    mutex->wait_queue.pop();
                    expected = false;
                    if (mutex->lock.compare_exchange_strong(expected, true, std::memory_order_acquire))
					{
                        mutex->thread_id.store(thread_id, std::memory_order_release);
                        return (0);
                    }
                }
            }
        }
		catch (const std::exception& error)
		{
			pt_errno_msg = error.what();
            return (-1);
        }
    }
	return (0);
}

