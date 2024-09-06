/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:41:28 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/24 14:11:05 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

int	ltoa_check_sign(long value)
{
	if (value < 0)
		return (1);
	else
		return (0);
}

int	ltoa_len(long value)
{
	int	len;

	len = 0;
	while (value)
	{
		value = value / 10;
		len++;
	}
	return (len);
}

void	convert_and_place_digits(char *str, long *value,
			int len, int is_negative)
{
	long	digit;

	while (len > is_negative)
	{
		len--;
		digit = *value % 10;
		if (digit < 0)
			str[len] = -digit + '0';
		else
			str[len] = digit + '0';
		*value /= 10;
	}
}

char	*ft_ltoa(long value)
{
	int		sign;
	int		len;
	char	*number_as_char;

	if (value == 0)
		return (ft_strdup("0"));
	sign = ltoa_check_sign(value);
	if (sign == 1)
		value = value * -1;
	len = ltoa_len(value);
	number_as_char = (char *)malloc(len + sign + 1);
	if (!number_as_char)
		return (NULL);
	if (sign == 1)
		number_as_char[0] = '-';
	number_as_char[len + sign] = '\0';
	convert_and_place_digits(number_as_char, &value, len, sign);
	return (number_as_char);
}
