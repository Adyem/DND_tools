#include "libft.hpp"
#include "../CPP_class/nullptr.hpp"

void *ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char *dest_ptr = static_cast<unsigned char *>(destination);
	const unsigned char *src_ptr = static_cast<const unsigned char *>(source);
	size_t i;

	if (size == 0 || destination == source)
		return destination;
	if (!destination || !source)
		return (ft_nullptr);
	if (dest_ptr < src_ptr)
	{
		i = 0;
		while (i < size)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else
	{
		i = size;
		while (i > 0)
		{
			dest_ptr[i - 1] = src_ptr[i - 1];
			i--;
		}
	}
	return (destination);
}
