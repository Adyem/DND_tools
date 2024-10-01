/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:50:09 by bvangene          #+#    #+#             */
/*   Updated: 2023/10/22 11:06:40 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

int	itoa_len(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*fill_digits(char *c, unsigned int num, int start_index)
{
	while (start_index >= 0)
	{
		c[start_index] = (num % 10) + '0';
		num /= 10;
		start_index--;
	}
	return (c);
}

char	*convert_int(int n, int is_negative)
{
	int				i;
	char			*c;
	unsigned int	num;

	i = itoa_len(n);
	c = (char *)malloc(i + 1 + is_negative);
	if (!c)
		return (nullptr);
	if (n < 0)
		num = -n;
	else
		num = n;
	c[i + is_negative] = '\0';
	if (is_negative == 0)
		c = fill_digits(c, num, i - 1);
	else
		c = fill_digits(c, num, i);
	if (is_negative == 1)
		c[0] = '-';
	return (c);
}

char	*ft_itoa(int n)
{
	int	is_negative;

	if (n > 0)
		is_negative = 0;
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	else
		is_negative = 1;
	return (convert_int(n, is_negative));
}
