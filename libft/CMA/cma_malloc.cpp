#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"
#include "CMA_internal.hpp"
#include "../CPP_class/nullptr.hpp"

void* cma_malloc(int size)
{
    if (OFFSWITCH == 1)
        return (malloc(size));
    if (size <= 0)
        return (ft_nullptr);
    size_t	aligned_size = align8((size_t)size);
    Block	*block = find_free_block(aligned_size);
    if (!block)
    {
        Page* page = create_page(aligned_size);
        if (!page)
            return (ft_nullptr);
        block = page->blocks;
    }
    block = split_block(block, aligned_size);
    block->free = false;
    return ((char*)block + sizeof(Block));
}
