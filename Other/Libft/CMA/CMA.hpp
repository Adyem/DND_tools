#ifndef CMA_HPP
# define CMA_HPP

void	*cma_malloc(int size, bool critical);
void	cma_free(void* ptr);
void	cma_cleanup_non_critical_memory();
void	cma_cleanup_all_memory();
bool	cma_add_page(bool critical);
char	*cma_strdup(char *string, bool criticality);
void	*cma_calloc(int count, int size, bool criticality);

#endif
