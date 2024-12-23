#include "libft.hpp"

size_t	ft_strlcpy(char *destination, const char *source, size_t bufferSize)
{
	size_t	sourceLength = 0;

	if (bufferSize == 0)
	{
		while (source[sourceLength] != '\0')
			sourceLength++;
		return (sourceLength);
	}
	while (sourceLength < bufferSize - 1 && source[sourceLength] != '\0')
	{
		destination[sourceLength] = source[sourceLength];
		sourceLength++;
	}
	if (sourceLength < bufferSize)
		destination[sourceLength] = '\0';
	while (source[sourceLength] != '\0')
		sourceLength++;
	return (sourceLength);
}
