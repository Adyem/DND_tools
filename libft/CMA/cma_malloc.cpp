#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include <pthread.h>
#include "CMA.hpp"
#include "CMA_internal.hpp"
#include "../PThread/mutex.hpp"
#include "../CPP_class/nullptr.hpp"

inline size_t align8(size_t size)
{
    return ((size + 7) & ~7);
}

void* cma_malloc(int size)
{
	if (OFFSWITCH == 1)
        return (malloc(size));
	if (size <= 0)
        return (ft_nullptr);
	g_malloc_mutex.lock(pthread_self());
    size_t	aligned_size = align8((size_t)size);
    Block	*block = find_free_block(aligned_size);
    if (!block)
    {
        Page* page = create_page(aligned_size);
        if (!page)
		{
			g_malloc_mutex.unlock(pthread_self());
            return (ft_nullptr);
		}
        block = page->blocks;
    }
    block = split_block(block, aligned_size);
    block->free = false;
	g_malloc_mutex.unlock(pthread_self());
    return ((char*)block + sizeof(Block));
}
