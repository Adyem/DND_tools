#ifndef ERRNO_HPP
# define ERRNO_HPP

enum PTErrorCode
{
    SUCCESS = 0,
    PT_ERR_QUEUE_FULL,
    PT_ERR_MUTEX_NULLPTR,
    PT_ERR_MUTEX_OWNER,
    SHARED_PTR_NO_ERROR,
    SHARED_PTR_NULL_PTR,
    SHARED_PTR_OUT_OF_BOUNDS,
    SHARED_PTR_ALLOCATION_FAILED,
    SHARED_PTR_INVALID_OPERATION,
    MAP_NO_ERROR,
    MAP_ALLOCATION_FAILED,
    MAP_KEY_NOT_FOUND,
};

const char* ft_strerror(int error_code);

extern thread_local int ft_errno;

#endif
