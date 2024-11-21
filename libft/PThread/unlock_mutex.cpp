#include "PThread.hpp"
#include "../Errno/errno.hpp"

thread_local int ft_errno;

int pt_mutex::unlock(int thread_id)
{
    this->set_error(ER_SUCCESS);
    if (this->_thread_id != thread_id)
    {
        this->set_error(PT_ERR_MUTEX_OWNER);
        return (-1);
    }
    this->_thread_id = -1;
    this->_lock = false;
    this->_lock_released = true;
    return (0); 
}
