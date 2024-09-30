#ifndef CMA_HPP
# define CMA_HPP

#include <cstdint>
#include <cstddef>

#ifndef PAGE_SIZE
# define PAGE_SIZE 65536
#endif

#ifndef BYPASS_ALLOC
# define BYPASS_ALLOC DEBUG
#endif

#ifndef MAGIC_NUMBER
# define MAGIC_NUMBER 0xDEADBEEF
#endif

#ifndef DEBUG
# define DEBUG 0
#endif

#if DEBUG == 1
#include <valgrind/memcheck.h>
#define PROTECT_METADATA(ptr, size) VALGRIND_MAKE_MEM_NOACCESS(ptr, size)
#define UNPROTECT_METADATA(ptr, size) VALGRIND_MAKE_MEM_DEFINED(ptr, size)
#else
#define PROTECT_METADATA(ptr, size)
#define UNPROTECT_METADATA(ptr, size)
#endif

struct Block
{
    uint32_t magic;
    size_t size;
    bool free;
    bool critical;
    Block* next;
    Block* prev;
};

struct Page
{
    void* start;
    size_t size;
    Page* next;
    Page* prev;
    Block* blocks;
    bool critical;
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
char	*ft_strjoin(char const *string_1, char const *string_2, bool critical);

//utils
size_t	align8(size_t size);

#endif
