/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:33 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/22 11:14:12 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (d == s)
		return (dst);
	if (s < d && d < s + len)
	{
		s += len;
		d += len;
		while (len--)
			*(--d) = *(--s);
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
