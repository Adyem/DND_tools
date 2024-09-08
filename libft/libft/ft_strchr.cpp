/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:07:10 by bvangene          #+#    #+#             */
/*   Updated: 2024/03/08 14:12:37 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

char	*ft_strchr(const char *s, int i)
{
	char	c;

	if (!s)
		return (nullptr);
	c = (char)i;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (nullptr);
}
