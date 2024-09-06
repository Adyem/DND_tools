/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:50:42 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/22 10:57:13 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	len_s;

	len_s = ft_strlen(s);
	i = 0;
	while (i < len_s)
	{
		f(i, &s[i]);
		i++;
	}
}
