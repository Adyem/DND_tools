#ifndef CMA_HPP
# define CMA_HPP

#include <cstdint>
#include <cstddef>
#include <valgrind/memcheck.h>

#define PAGE_SIZE 65536
#define BYPASS_ALLOC DEBUG
#define MAGIC_NUMBER 0xDEADBEEF

#define OFFSWITCH 1

#ifndef DEBUG
# define DEBUG 0
#endif

#define PROTECT_METADATA(ptr, size) VALGRIND_MAKE_MEM_NOACCESS(ptr, size)
#define UNPROTECT_METADATA(ptr, size) VALGRIND_MAKE_MEM_DEFINED(ptr, size)

struct Block
{
    uint32_t	magic;
    size_t		size;
    bool		free;
    bool		critical;
    Block		*next;
    Block		*prev;
};

struct Page
{
    void	*start;
    size_t	size;
    Page	*next;
    Page	*prev;
    Block	*blocks;
    bool	critical;
};

extern Page *page_list;

void	*cma_malloc(int size, bool critical);
void	cma_free(void* ptr);
void	cma_cleanup_non_critical_memory();
void	cma_cleanup_all_memory();
bool	cma_add_page(bool critical);
char	*cma_strdup(const char *string, bool criticality);
void	*cma_calloc(int count, int size, bool criticality);
void	*cma_realloc(void* ptr, size_t new_size, bool critical);
char	**cma_split(char const *s, char c, bool critical);
char	*cma_itoa(int n, bool critical);
char	*cma_strjoin(char const *string_1, char const *string_2, bool critical);
void	cma_free_double(char **content);

size_t	align8(size_t size);

#endif
