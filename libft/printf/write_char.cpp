/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:05:28 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/24 13:48:28 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.hpp"
#include <stdio.h>

void	write_char(va_list args, t_format *f_info)
{
	int		c;
	char	zero;

	zero = 0;
	c = va_arg(args, int);
	if (c == 0)
	{
		write (1, &zero, 1);
		f_info->index++;
		f_info->return_value++;
		return ;
	}
	if (c)
	{
		write (1, &c, 1);
		f_info->return_value++;
	}
	f_info->index++;
	return ;
}

void	read_string(va_list args, t_format *f_info)
{
	char	*c;

	c = va_arg(args, char *);
	if (c == NULL)
	{
		write (1, "(null)", 6);
		f_info->return_value = f_info->return_value + 6;
		f_info->index++;
	}
	else
		write_string(c, f_info);
	return ;
}

void	write_string(char *string, t_format *f_info)
{
	int	i;

	i = 0;
	while (string[i])
	{
		write (1, &string[i], 1);
		f_info->return_value++;
		i++;
	}
	f_info->index++;
	return ;
}

void	write_percent(t_format *f_info)
{
	char	c;

	c = '%';
	write (1, &c, 1);
	f_info->index++;
	f_info->return_value++;
	return ;
}
