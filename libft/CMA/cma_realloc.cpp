#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <csignal>
#include "CMA.hpp"
#include "CMA_internal.hpp"
#include "../CPP_class/nullptr.hpp"

void* cma_realloc(void* ptr, size_t new_size)
{
    if (DEBUG == 1 || OFFSWITCH == 1)
    {
        void* new_ptr = malloc(new_size);
        if (ptr && new_ptr)
        {
            Block* old_block = (Block*)((char*)ptr - sizeof(Block));
            size_t copy_size = old_block->size < new_size ? old_block->size : new_size;
            memcpy(new_ptr, ptr, copy_size);
        }
        free(ptr);
        return new_ptr;
    }
    if (!ptr)
        return cma_malloc(new_size);
    if (new_size == 0)
    {
        cma_free(ptr);
        return ft_nullptr;
    }
    void* new_ptr = cma_malloc(new_size);
    if (!new_ptr)
    {
        cma_free(ptr);
        return ft_nullptr;
    }
    Block* old_block = (Block*)((char*)ptr - sizeof(Block));
    if (old_block->magic != MAGIC_NUMBER)
        return ft_nullptr;
    size_t copy_size = old_block->size < new_size ? old_block->size : new_size;
    memcpy(new_ptr, ptr, copy_size);
    cma_free(ptr);
    return new_ptr;
}
