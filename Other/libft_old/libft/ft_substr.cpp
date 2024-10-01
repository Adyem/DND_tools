/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:45:14 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/19 13:49:35 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*r;
	size_t			actual_len;

	if (!s)
		return (nullptr);
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup(""));
	if (i - start > len)
		actual_len = len;
	else
		actual_len = i - start;
	r = (char *)malloc (actual_len + 1);
	if (!r)
		return (nullptr);
	i = 0;
	while (i < actual_len)
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
