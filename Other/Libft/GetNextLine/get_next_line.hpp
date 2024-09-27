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

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	*ft_strjoin_gnl(char *string_1, char *string_2, bool critical);
char	*get_next_line(int fd, bool crticail);

#endif
