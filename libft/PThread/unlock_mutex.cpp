#include "PThread.hpp"
#include "../Errno/errno.hpp"

thread_local int ft_errno;

int pt_mutex_unlock(t_mutex *mutex, int thread_id)
{
    ft_errno = ER_SUCCESS;
    if (!mutex)
    {
        ft_errno = PT_ERR_MUTEX_NULLPTR;
        return (-1);
    }
    if (mutex->thread_id != thread_id)
    {
        ft_errno = PT_ERR_MUTEX_OWNER;
        return (-1);
    }
    mutex->thread_id = -1;
    mutex->lock = false;
    mutex->lock_released = true;
    return (0); 
}
