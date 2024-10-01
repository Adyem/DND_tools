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
