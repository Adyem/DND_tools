#ifndef MUTEX_HPP
# define MUTEX_HPP

#include "PThread.hpp"

class pt_mutex
{
	private:
		volatile bool	_lock;
		volatile int	_thread_id;
		int				_wait_queue[MAX_QUEUE];
		int				_wait_queue_start;
		int				_wait_queue_end;
		int				_error;
		volatile bool	_lock_released;

		void		set_error(int error);

		pt_mutex(const pt_mutex&) = delete;
		pt_mutex& operator=(const pt_mutex&) = delete;
    	pt_mutex(pt_mutex&&) = delete;
    	pt_mutex& operator=(pt_mutex&&) = delete;

	public:
		pt_mutex();
		~pt_mutex();

		const volatile bool	&lockState() const;

		int			lock(int thread_id);
		int			unlock(int thread_id);
		int			try_lock(int thread_id);
};

#endif
