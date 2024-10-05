#include "get_next_line_old.hpp"
#include "../Libft/libft.hpp"

static char	*allocate_new_string_old(char *string_1, char *string_2)
{
	int		total_len;
	char	*new_str;

	total_len = 0;
	if (string_1)
		total_len += ft_strlen(string_1);
	if (string_2)
		total_len += ft_strlen(string_2);
	new_str = (char *)malloc(total_len + 1);
	if (!new_str)
		return (nullptr);
	return (new_str);
}

char	*ft_strjoin_gnl_old(char *string_1, char *string_2)
{
	char	*result;
	char	*original_string;
	int		i;

	if (!string_1 && !string_2)
		return (nullptr);
	original_string = string_1;
	result = allocate_new_string_old(string_1, string_2);
	if (!result)
		return (nullptr);
	i = 0;
	if (string_1)
		while (*string_1)
			result[i++] = *string_1++;
	if (string_2)
		while (*string_2)
			result[i++] = *string_2++;
	result[i] = '\0';
	free (original_string);
	return (result);
}
