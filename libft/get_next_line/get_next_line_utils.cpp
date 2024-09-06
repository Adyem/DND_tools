/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:27:36 by bvangene          #+#    #+#             */
/*   Updated: 2023/12/10 19:25:30 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.hpp"

static char	*allocate_new_string(char *string_1, char *string_2)
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
		return (NULL);
	return (new_str);
}

char	*ft_strjoin_gnl(char *string_1, char *string_2)
{
	char	*result;
	char	*original_string;
	int		i;

	if (!string_1 && !string_2)
		return (NULL);
	original_string = string_1;
	result = allocate_new_string(string_1, string_2);
	if (!result)
		return (NULL);
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
