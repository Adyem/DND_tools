#include <pthread.h>

int pt_thread_join(pthread_t thread, void **retval)
{
	return (pthread_join(thread, retval));
}
