#include "PThread.hpp"
#include "mutex.hpp"
#include "../Errno/errno.hpp"

pt_mutex::pt_mutex()
{
	int i = 0;

	this->_lock = false;
	this->_thread_id = 0;
	while (i < MAX_QUEUE)
	{
		this->_wait_queue[i] = 0;
		i++;
	}
	this->_wait_queue_start = 0;
	this->_wait_queue_end = 0;
	this->_lock_released = false;
	return ;
}

pt_mutex::~pt_mutex()
{
	return ;
}

void	pt_mutex::set_error(int	error)
{
	this->_error = error;
	ft_errno = error;
	return ;
}
