#include "libft.hpp"

char	*ft_strnstr(const char *haystack, const char *needle, size_t Length)
{
	size_t	haystackIndex = 0;
	size_t	matchIndex;
	size_t	needleLength = ft_strlen(needle);
	char	*haystackPointer = (char *)haystack;

	if (needleLength == 0 || haystack == needle)
		return (haystackPointer);
	while (haystackPointer[haystackIndex] != '\0' && haystackIndex < Length)
	{
		matchIndex = 0;
		while (haystackPointer[haystackIndex + matchIndex] != '\0'
			&& needle[matchIndex] != '\0'
			&& haystackPointer[haystackIndex + matchIndex] == needle[matchIndex]
			&& haystackIndex + matchIndex < Length)
		{
			matchIndex++;
		}
		if (matchIndex == needleLength)
			return (haystackPointer + haystackIndex);

		haystackIndex++;
	}
	return (0);
}
