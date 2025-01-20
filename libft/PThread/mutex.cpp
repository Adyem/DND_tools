#include "PThread.hpp"
#include "mutex.hpp"
#include "../Errno/errno.hpp"

pt_mutex::pt_mutex()
{
	int index = 0;

	this->_lock = false;
	this->_thread_id = 0;
	while (index < MAX_QUEUE)
	{
		this->_wait_queue[index] = 0;
		index++;
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

const volatile bool	&pt_mutex::lockState() const
{
    return (this->_lock);
}
