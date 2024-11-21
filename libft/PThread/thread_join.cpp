#include <cerrno>
#include <pthread.h>
#include "../Errno/errno.hpp"

int pt_thread_join(pthread_t thread, void **retval)
{
	int return_value = pthread_join(thread, retval);
	if (return_value != 0)
		ft_errno = errno + ERRNO_OFFSET;
	return (return_value);
}
