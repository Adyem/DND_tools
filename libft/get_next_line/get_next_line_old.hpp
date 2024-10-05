#ifndef GET_NEXT_LINE_OLD_H
# define GET_NEXT_LINE_OLD_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	*ft_strjoin_gnl_old(char *string_1, char *string_2);
char	*leftovers_old(char *readed_string);
char	*malloc_gnl_old(char *readed_string, size_t i);
char	*fetch_line_old(char *readed_string);
char	*get_next_line_old(int fd);
char	**read_file_old(int fd);

#endif
