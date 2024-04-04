/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:50:21 by bvangene          #+#    #+#             */
/*   Updated: 2023/12/11 11:50:25 by bvangene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	*ft_strjoin_gnl(char *string_1, char *string_2);
char	*leftovers(char *readed_string);
char	*malloc_gnl(char *readed_string, size_t i);
char	*fetch_line(char *readed_string);
char	*get_next_line(int fd);
char	**read_file(int fd);

#endif
