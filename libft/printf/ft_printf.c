/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:41:37 by bvangene          #+#    #+#             */
/*   Updated: 2024/04/22 17:39:51 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_format(const char *format, va_list args, t_format *f_info)
{
	if (format[f_info->index + 1] == 'c')
		write_char(args, f_info);
	else if (format[f_info->index + 1] == 's')
		read_string(args, f_info);
	else if (format[f_info->index + 1] == 'p')
		read_void_pointer(args, f_info);
	else if (format[f_info->index + 1] == 'd')
		read_decimal(args, f_info);
	else if (format[f_info->index + 1] == 'i')
		read_integer(args, f_info);
	else if (format[f_info->index + 1] == 'u')
		read_unsigned_decimal(args, f_info);
	else if (format[f_info->index + 1] == 'x')
		read_hexadecimal(args, f_info, 0);
	else if (format[f_info->index + 1] == 'X')
		read_hexadecimal(args, f_info, 1);
	else
		write_percent(f_info);
	return ;
}

int	ft_printf(const char *format, ...)
{
	int			return_v;
	va_list		args;
	t_format	*f_info;

	va_start(args, format);
	f_info = (t_format *)malloc(sizeof(t_format));
	if (!f_info)
		return (-1);
	f_info->return_value = 0;
	f_info->index = 0;
	while (format && format[f_info->index])
	{
		if ((int) format[f_info->index] == '%')
			check_format(format, args, f_info);
		else
		{
			write (1, &format[f_info->index], 1);
			f_info->return_value++;
		}
		f_info->index++;
	}
	va_end(args);
	return_v = f_info->return_value;
	free (f_info);
	return (return_v);
}
