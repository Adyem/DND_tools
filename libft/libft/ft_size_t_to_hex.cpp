/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_t_to_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:42:18 by bvangene          #+#    #+#             */
/*   Updated: 2023/12/14 13:59:06 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

char	ft_convert_to_hex_size_t(size_t buffer)
{
	char	hex_number;

	if (buffer <= 9)
		hex_number = buffer + '0';
	else
		hex_number = buffer - 10 + 'a';
	return (hex_number);
}

char	*ft_size_t_to_hex(size_t value)
{
	size_t	buffer_size;
	size_t	buffer;
	char	*hexstr;
	int		i;

	buffer_size = sizeof(size_t) * 2 + 1;
	hexstr = (char *)malloc(buffer_size);
	if (!hexstr)
		return (NULL);
	i = 0;
	while (value)
	{
		buffer = value % 16;
		hexstr[i] = ft_convert_to_hex_size_t(buffer);
		value = value / 16;
		i++;
	}
	hexstr[i] = '\0';
	ft_reverse_string(hexstr);
	return (hexstr);
}
