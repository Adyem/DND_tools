#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 512

#include "../CPP_class/file.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

char	*ft_strjoin_gnl(char *string_1, char *string_2);
char	*get_next_line(ft_file &file);
char	**ft_read_file_lines(ft_file &file);
char	**ft_open_and_read_file(const char *file_name);

#endif
