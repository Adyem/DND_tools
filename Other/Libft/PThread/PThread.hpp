#ifndef PTHREAD_HPP
# define PTHREAD_HPP

#include <atomic>
#include <queue>

#define SLEEP_TIME 100

typedef struct t_mutex
{
    std::atomic<bool>	lock = {false};
    std::atomic<int>	thread_id = {-1};
    std::queue<int>		wait_queue;
	std::atomic<bool>	lock_released = {false};
} s_mutex;

int		pt_mutex_lock(t_mutex *mutex, int thread_id);
int		pt_mutex_unlock(t_mutex *mutex, int thread_id);
int		pt_mutex_try_lock(t_mutex *mutex, int thread_id);

#endif
