#include "errno.hpp"

const char* ft_strerror(int error_code)
{
	if (error_code == SUCCESS)
        return ("Operation successful");
	else if (error_code == PT_ERR_QUEUE_FULL)
        return ("Wait queue is full");
	else if (error_code == PT_ERR_MUTEX_NULLPTR)
		return ("Mutex pointer is null");
	else if (error_code == PT_ERR_MUTEX_OWNER)
		return ("Thread is not the owner of the mutex");
	else
        return ("Unrecognized error code");
}
