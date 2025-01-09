#include "CMA.hpp"
#include "../Libft/libft.hpp"
#include "../CPP_class/nullptr.hpp"

static char	*allocate_new_string(const char *string_1, const char *string_2)
{
	int		total_len;
	char	*new_str;

	total_len = 0;
	if (string_1)
		total_len += ft_strlen(string_1);
	if (string_2)
		total_len += ft_strlen(string_2);
	new_str = (char *)cma_malloc(total_len + 1);
	if (!new_str)
		return (ft_nullptr);
	return (new_str);
}

char	*cma_strjoin(char const *string_1, char const *string_2)
{
	char	*result;
	int		i;

	if (!string_1 && !string_2)
		return (ft_nullptr);
	result = allocate_new_string(string_1, string_2);
	if (!result)
		return (ft_nullptr);
	i = 0;
	if (string_1)
		while (string_1[0])
			result[i++] = *string_1++;
	if (string_2)
		while (string_2[0])
			result[i++] = *string_2++;
	result[i] = '\0';
	return (result);
}
