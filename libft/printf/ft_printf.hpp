/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:40 by bvangene          #+#    #+#             */
/*   Updated: 2023/11/23 15:18:37 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.hpp"
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_format
{
	int	index;
	int	return_value;
}	t_format;

int		ft_printf(const char *format, ...);
void	check_format(const char *format, va_list args, t_format *f_info);
void	write_char(va_list args, t_format *f_info);
void	read_string(va_list args, t_format *f_info);
void	read_void_pointer(va_list args, t_format *f_info);
void	read_hexadecimal(va_list args, t_format *f_info, int upper);
void	read_unsigned_decimal(va_list args, t_format *f_info);
void	read_integer(va_list args, t_format *f_info);
void	write_percent(t_format *f_info);
void	read_decimal(va_list args, t_format *f_info);
void	write_string(char *string, t_format *f_info);

#endif
