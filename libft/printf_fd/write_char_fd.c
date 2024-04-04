/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:05:28 by bvangene          #+#    #+#             */
/*   Updated: 2024/03/01 13:36:53 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	write_char_fd(va_list args, t_format_fd *f_info)
{
	int		c;
	char	zero;

	zero = 0;
	c = va_arg(args, int);
	if (c == 0)
	{
		write (f_info->fd, &zero, 1);
		f_info->index++;
		f_info->return_value++;
		return ;
	}
	if (c)
	{
		write (f_info->fd, &c, 1);
		f_info->return_value++;
	}
	f_info->index++;
	return ;
}

void	read_string_fd(va_list args, t_format_fd *f_info)
{
	char	*c;

	c = va_arg(args, char *);
	if (c == NULL)
	{
		write (f_info->fd, "(null)", 6);
		f_info->return_value = f_info->return_value + 6;
		f_info->index++;
	}
	else
		write_string_fd(c, f_info);
	return ;
}

void	write_string_fd(char *string, t_format_fd *f_info)
{
	int	i;

	i = 0;
	while (string[i])
	{
		write (f_info->fd, &string[i], 1);
		f_info->return_value++;
		i++;
	}
	f_info->index++;
	return ;
}

void	write_percent_fd(t_format_fd *f_info)
{
	char	c;

	c = '%';
	write (f_info->fd, &c, 1);
	f_info->index++;
	f_info->return_value++;
	return ;
}
