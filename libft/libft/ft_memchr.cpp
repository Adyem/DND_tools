/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:58:19 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/16 12:01:34 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	*ft_memchr(const void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	character;

	str = (unsigned char *)b;
	character = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*str == character)
			return (str);
		str++;
		i++;
	}
	return (nullptr);
}
