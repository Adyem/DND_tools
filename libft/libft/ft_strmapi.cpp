/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:50:22 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/22 11:08:12 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*c;
	unsigned int	i;
	unsigned int	len_s;

	len_s = ft_strlen(s);
	c = (char *)malloc(len_s + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		c[i] = f(i, s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}
