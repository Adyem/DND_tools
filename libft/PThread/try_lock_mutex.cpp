#include "PThread.hpp"
#include "../Errno/errno.hpp"

thread_local int	ft_errno;

int pt_mutex::try_lock(int thread_id)
{
    this->set_error(ER_SUCCESS);
    if (__sync_bool_compare_and_swap(&this->_lock, false, true))
    {
        this->_thread_id = thread_id;
        return (0);
    }
    return (1);
}
