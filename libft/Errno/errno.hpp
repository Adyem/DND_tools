#ifndef ERRNO_HPP
# define ERRNO_HPP

enum PTErrorCode {
    SUCCESS = 0,
    PT_ERR_QUEUE_FULL,
	PT_ERR_MUTEX_NULLPTR,
	PT_ERR_MUTEX_OWNER,
};

const char* ft_strerror(int error_code);

extern thread_local int ft_errno;

#endif
