#include <cerrno>
#include <pthread.h>
#include "../Errno/errno.hpp"

int pt_thread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg)
{
	int return_value = pthread_create(thread, attr, start_routine, arg);
	if (return_value != 0)
		ft_errno = errno + ERRNO_OFFSET;
	return (return_value);
}
