#include "libft.hpp"
#include <cstdlib>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (nullptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
