#include "libft.hpp"

size_t	ft_strlcat(char *destination, const char *source, size_t bufferSize)
{
	size_t	destLength = 0;
	size_t	sourceIndex = 0;

	while (destination[destLength] && destLength < bufferSize)
		destLength++;
	while (source[sourceIndex] && (destLength + sourceIndex + 1) < bufferSize)
	{
		destination[destLength + sourceIndex] = source[sourceIndex];
		sourceIndex++;
	}
	if (destLength < bufferSize)
		destination[destLength + sourceIndex] = '\0';
	return (destLength + ft_strlen(source));
}
