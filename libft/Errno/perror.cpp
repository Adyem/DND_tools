#include "errno.hpp"
#include "../Printf/printf.hpp"

void	ft_perror(const char *error_msg)
{
	if (!error_msg)
		pf_printf_fd(2, "%s", ft_strerror(ft_errno));
	else
		pf_printf_fd(2, "%s: %s", error_msg, ft_strerror(ft_errno));
	return ;
}
