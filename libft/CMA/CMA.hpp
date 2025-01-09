#ifndef CMA_HPP
# define CMA_HPP

#include <cstddef>
#include <valgrind/memcheck.h>

void	*cma_malloc(int size);
void	cma_free(void* ptr);
char	*cma_strdup(const char *string);
void	*cma_calloc(int count, int size);
void	*cma_realloc(void* ptr, size_t new_size);
char	**cma_split(char const *s, char c);
char	*cma_itoa(int n);
char	*cma_strjoin(char const *string_1, char const *string_2);
void	cma_free_double(char **content);
void	cma_cleanup();

#endif
