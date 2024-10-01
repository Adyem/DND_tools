/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:16:45 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/24 14:12:00 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.hpp"

void	read_void_pointer(va_list args, t_format *f_info)
{
	void	*pointer;
	size_t	pointer_as_nbr;
	char	*pointer_as_hex;

	pointer = va_arg(args, void *);
	if (!pointer)
	{
		write (1, "(nil)", 5);
		f_info->return_value = f_info->return_value + 5;
		f_info->index++;
		return ;
	}
	pointer_as_nbr = (size_t)pointer;
	pointer_as_hex = ft_pointer_to_hex(pointer_as_nbr);
	if (!pointer_as_hex)
		return ;
	write_string(pointer_as_hex, f_info);
	free (pointer_as_hex);
	return ;
}

void	read_hexadecimal(va_list args, t_format *f_info, int upper)
{
	unsigned int		number;
	char				*number_as_hex;

	number = va_arg(args, unsigned int);
	number_as_hex = ft_long_to_hex(number);
	if (!number_as_hex)
		return ;
	if (upper == 1)
		ft_string_to_upper(number_as_hex);
	write_string(number_as_hex, f_info);
	free (number_as_hex);
	return ;
}

void	read_integer(va_list args, t_format *f_info)
{
	int		number;
	char	*number_as_char;

	number = va_arg(args, int);
	number_as_char = ft_itoa(number);
	if (!number_as_char)
		return ;
	write_string(number_as_char, f_info);
	free (number_as_char);
	return ;
}

void	read_unsigned_decimal(va_list args, t_format *f_info)
{
	int				number;
	char			*number_as_char;

	number = va_arg(args, int);
	number_as_char = ft_uitoa(number);
	if (!number_as_char)
		return ;
	write_string(number_as_char, f_info);
	free (number_as_char);
	return ;
}

void	read_decimal(va_list args, t_format *f_info)
{
	long	number;
	char	*number_as_char;

	number = va_arg(args, int);
	number_as_char = ft_itoa(number);
	if (!number_as_char)
		return ;
	write_string(number_as_char, f_info);
	free(number_as_char);
	return ;
}
