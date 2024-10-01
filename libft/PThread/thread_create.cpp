#include <pthread.h>

int pt_thread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg)
{
	return (pthread_create(thread, attr, start_routine, arg));
}

