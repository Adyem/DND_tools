#include "PThread.hpp"
#include "../Errno/errno.hpp"

thread_local int	ft_errno;

int pt_mutex_try_lock(t_mutex *mutex, int thread_id)
{
    ft_errno = ER_SUCCESS;

    if (!mutex)
    {
        ft_errno = PT_ERR_MUTEX_NULLPTR;
        return (-2);
    }
    if (__sync_bool_compare_and_swap(&mutex->lock, false, true))
    {
        mutex->thread_id = thread_id;
        return (0);
    }
    return (1);
}
