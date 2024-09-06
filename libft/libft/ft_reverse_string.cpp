/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:41:55 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/23 12:43:25 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

void	ft_reverse_string(char *c)
{
	char	buffer;
	int		i;
	int		j;

	j = ft_strlen(c) - 1;
	i = 0;
	while (j > i)
	{
		buffer = c[i];
		c[i] = c[j];
		c[j] = buffer;
		j--;
		i++;
	}
}
