/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:50:09 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/24 14:04:45 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

int	uitoa_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int value)
{
	char	*number_as_char;
	int		len;
	int		i;

	if (value == 0)
		return (ft_strdup("0"));
	len = uitoa_len(value);
	number_as_char = (char *)malloc(len + 1);
	if (!number_as_char)
		return (NULL);
	i = 0;
	while (value)
	{
		number_as_char[i] = value % 10 + '0';
		value = value / 10;
		i++;
	}
	number_as_char[i] = '\0';
	ft_reverse_string(number_as_char);
	return (number_as_char);
}
