/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_to_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:42:18 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/23 15:13:46 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	convert_to_hex_size_t(size_t buffer)
{
	char	hex_number;

	if (buffer <= 9)
		hex_number = buffer + '0';
	else
		hex_number = buffer - 10 + 'a';
	return (hex_number);
}

char	*ft_pointer_to_hex(size_t value)
{
	size_t	buffer_size;
	size_t	buffer;
	char	*hexstr;
	int		i;

	buffer_size = sizeof(size_t) * 2 + 1;
	hexstr = malloc(buffer_size + 3);
	i = 0;
	while (value)
	{
		buffer = value % 16;
		hexstr[i] = convert_to_hex_size_t(buffer);
		value = value / 16;
		i++;
	}
	hexstr[i++] = 'x';
	hexstr[i++] = '0';
	hexstr[i] = '\0';
	ft_reverse_string(hexstr);
	return (hexstr);
}
