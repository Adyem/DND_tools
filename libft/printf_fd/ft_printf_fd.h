/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:40 by bvangene          #+#    #+#             */
/*   Updated: 2024/03/01 13:35:55 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_format_fd
{
	int	fd;
	int	index;
	int	return_value;
}	t_format_fd;

int		ft_printf_fd(int fd, const char *format, ...);
void	check_format_fd(const char *format, va_list args, t_format_fd *f_info);
void	write_char_fd(va_list args, t_format_fd *f_info);
void	read_string_fd(va_list args, t_format_fd *f_info);
void	read_void_pointer_fd(va_list args, t_format_fd *f_info);
void	read_hexadecimal_fd(va_list args, t_format_fd *f_info, int upper);
void	read_unsigned_decimal_fd(va_list args, t_format_fd *f_info);
void	read_integer_fd(va_list args, t_format_fd *f_info);
void	write_percent_fd(t_format_fd *f_info);
void	read_decimal_fd(va_list args, t_format_fd *f_info);
void	write_string_fd(char *string, t_format_fd *f_info);

#endif
