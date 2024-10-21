#include "../Libft/libft.hpp"
#include "../CMA/CMA.hpp"
#include "get_next_line.hpp"

static char	*allocate_new_string(char *string_1, char *string_2, bool critical)
{
	int		total_len;
	char	*new_str;

	total_len = 0;
	if (string_1)
		total_len += ft_strlen(string_1);
	if (string_2)
		total_len += ft_strlen(string_2);
	new_str = (char *)cma_malloc(total_len + 1, critical);
	if (!new_str)
		return (nullptr);
	return (new_str);
}

char *ft_strjoin_gnl(char *string_1, char *string_2, bool critical)
{
    char *result;
    char *original_string;
    int i;
    char *temp1 = string_1;
    char *temp2 = string_2;

    if (!string_1 && !string_2)
        return (nullptr);
    original_string = string_1;
    result = allocate_new_string(string_1, string_2, critical);
    if (!result)
        return (nullptr);
    i = 0;
    if (temp1)
        while (*temp1)
            result[i++] = *temp1++;
    if (temp2)
        while (*temp2)
            result[i++] = *temp2++;
    result[i] = '\0';
    cma_free(original_string);
    return (result);
}
