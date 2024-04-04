/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:41:01 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/24 11:50:19 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	convert_to_hex_long(size_t buffer)
{
	char	hex_number;

	if (buffer <= 9)
		hex_number = buffer + '0';
	else
		hex_number = buffer - 10 + 'a';
	return (hex_number);
}

char	*ft_long_to_hex(long value)
{
	long				buffer_size;
	long				buffer;
	char				*hexstr;
	unsigned long		number;
	int					i;

	number = (unsigned long)value;
	if (value == 0)
		return (ft_strdup("0"));
	buffer_size = sizeof(long) * 2 + 1;
	hexstr = (char *)ft_calloc(buffer_size + 1, sizeof(char));
	i = 0;
	while (number)
	{
		buffer = number % 16;
		hexstr[i] = convert_to_hex_long(buffer);
		number = number / 16;
		i++;
	}
	hexstr[i] = '\0';
	ft_reverse_string(hexstr);
	return (hexstr);
}
