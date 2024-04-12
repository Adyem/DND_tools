/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvangene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:50:21 by bvangene          #+#    #+#             */
/*   Updated: 2024/04/12 22:59:09 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
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
