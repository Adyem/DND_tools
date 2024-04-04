/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:41:37 by bvangene          #+#    #+#             */
/*   Updated: 2024/03/01 13:36:26 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	check_format_fd(const char *format, va_list args, t_format_fd *f_info)
{
	if (format[f_info->index + 1] == 'c')
		write_char_fd(args, f_info);
	else if (format[f_info->index + 1] == 's')
		read_string_fd(args, f_info);
	else if (format[f_info->index + 1] == 'p')
		read_void_pointer_fd(args, f_info);
	else if (format[f_info->index + 1] == 'd')
		read_decimal_fd(args, f_info);
	else if (format[f_info->index + 1] == 'i')
		read_integer_fd(args, f_info);
	else if (format[f_info->index + 1] == 'u')
		read_unsigned_decimal_fd(args, f_info);
	else if (format[f_info->index + 1] == 'x')
		read_hexadecimal_fd(args, f_info, 0);
	else if (format[f_info->index + 1] == 'X')
		read_hexadecimal_fd(args, f_info, 1);
	else
		write_percent_fd(f_info);
	return ;
}

static void	ft_init_struct(t_format_fd *f_info, int fd)
{
	f_info->return_value = 0;
	f_info->index = 0;
	f_info->fd = fd;
	return ;
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int			return_v;
	va_list		args;
	t_format_fd	*f_info;

	va_start(args, format);
	f_info = malloc(sizeof(t_format_fd));
	if (!f_info || fd < 0)
		return (-1);
	ft_init_struct(f_info, fd);
	while (format[f_info->index])
	{
		if ((int) format[f_info->index] == '%')
			check_format_fd(format, args, f_info);
		else
		{
			write (f_info->fd, &format[f_info->index], 1);
			f_info->return_value++;
		}
		f_info->index++;
	}
	va_end(args);
	return_v = f_info->return_value;
	return (free(f_info), return_v);
}
