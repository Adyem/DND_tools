#include "errno.hpp"
#include <cerrno>
#include <cstring>

const char* ft_strerror(int error_code)
{
	if (error_code == ER_SUCCESS)
        return ("Operation successful");
	else if (error_code == PT_ERR_QUEUE_FULL)
        return ("Wait queue is full");
	else if (error_code == PT_ERR_MUTEX_NULLPTR)
        return ("Mutex pointer is null");
	else if (error_code == PT_ERR_MUTEX_OWNER)
        return ("Thread is not the owner of the mutex");
	else if (error_code == SHARED_PTR_NO_ERROR)
        return ("No error");
	else if (error_code == SHARED_PTR_NULL_PTR)
        return ("Null pointer dereference");
	else if (error_code == SHARED_PTR_OUT_OF_BOUNDS)
        return ("Array index out of bounds");
	else if (error_code == SHARED_PTR_ALLOCATION_FAILED)
        return ("Memory allocation failed");
	else if (error_code == MAP_NO_ERROR)
        return ("No error in Map");
	else if (error_code == MAP_ALLOCATION_FAILED)
        return ("Map memory allocation failed");
	else if (error_code == MAP_KEY_NOT_FOUND)
		return ("Map key not found");
	else if (error_code == EINVAL)
		return ("Invalid argument");
	else if (error_code > ERRNO_OFFSET)
	{
		const char *message = strerror(error_code - ERRNO_OFFSET);
		if (message)
			return (message);
		return ("Unrecognized error code");
	}
	else
        return ("Unrecognized error code");
}
