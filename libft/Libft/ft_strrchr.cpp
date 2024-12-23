#include "libft.hpp"
#include "../CPP_class/nullptr.hpp"

char	*ft_strrchr(const char *string, int char_to_find)
{
	int		string_length;

	string_length = ft_strlen(string);
	while (string_length > 0)
	{
		if (string[string_length] == (char)char_to_find)
			return ((char *)string + string_length);
		string_length--;
	}
	if (string[string_length] == (char)char_to_find)
		return ((char *)string + string_length);
	return (ft_nullptr);
}
