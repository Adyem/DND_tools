#ifndef PTHREAD_HPP
# define PTHREAD_HPP

#define SLEEP_TIME 100
#define MAX_SLEEP 10000

extern thread_local const char *pt_errno_msg;

typedef struct t_mutex
{
	volatile bool lock;
	volatile int thread_id;
	int wait_queue[128];
	int wait_queue_start;
	int wait_queue_end;
	volatile bool lock_released;
} s_mutex;

int		pt_mutex_lock(t_mutex *mutex, int thread_id);
int		pt_mutex_unlock(t_mutex *mutex, int thread_id);
int		pt_mutex_try_lock(t_mutex *mutex, int thread_id);

#endif
