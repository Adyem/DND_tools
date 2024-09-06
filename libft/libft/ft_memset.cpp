/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:33 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/17 10:28:09 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	const char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);

	d = (char *)dst;       // Cast dst to char* once
	s = (const char *)src; // Cast src to const char* once

	i = 0;
	while (i < n)
	{
		d[i] = s[i]; // Now you can simply use d and s without casting inside the loop
		i++;
	}
	return (dst);
}
