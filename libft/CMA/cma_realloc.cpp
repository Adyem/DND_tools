#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <csignal>
#include "CMA.hpp"
#include "../Printf/ft_printf.hpp"

void* cma_realloc(void* ptr, size_t new_size, bool critical)
{
    if (ptr == nullptr)
        return cma_malloc(new_size, critical);
    if (new_size == 0)
    {
        cma_free(ptr);
        return nullptr;
    }
    size_t aligned_new_size = align8(new_size);
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    UNPROTECT_METADATA(block, sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
    {
		ft_printf_fd(2, "Invalid realloc detected at %p\n", ptr);
        raise(SIGSEGV);
    }
    if (aligned_new_size <= block->size)
    {
        if (block->size >= aligned_new_size + sizeof(Block) + 8)
        {
            Block* new_block = (Block*)((char*)block + sizeof(Block) + aligned_new_size);
            UNPROTECT_METADATA(new_block, sizeof(Block));
            new_block->magic = MAGIC_NUMBER;
            new_block->size = block->size - aligned_new_size - sizeof(Block);
            new_block->free = true;
            new_block->critical = block->critical;
            new_block->next = block->next;
            new_block->prev = block;
            if (block->next)
            {
                UNPROTECT_METADATA(block->next, sizeof(Block));
                block->next->prev = new_block;
                PROTECT_METADATA(block->next, sizeof(Block));
            }
            block->next = new_block;
            block->size = aligned_new_size;
            PROTECT_METADATA(new_block, sizeof(Block));
        }
        PROTECT_METADATA(block, sizeof(Block));
        return ptr;
    }
    else
    {
        size_t total_size = block->size;
        Block* curr_block = block;
        bool can_expand = false;
        while (curr_block->next)
        {
            Block* next_block = curr_block->next;
            UNPROTECT_METADATA(next_block, sizeof(Block));
            if (next_block->free && next_block->critical == block->critical)
            {
                total_size += sizeof(Block) + next_block->size;
                if (total_size >= aligned_new_size)
                {
                    curr_block->next = next_block->next;
                    if (next_block->next)
                    {
                        UNPROTECT_METADATA(next_block->next, sizeof(Block));
                        next_block->next->prev = curr_block;
                        PROTECT_METADATA(next_block->next, sizeof(Block));
                    }
                    PROTECT_METADATA(next_block, sizeof(Block));
                    can_expand = true;
                    break;
                }
                else
                {
                    curr_block = next_block;
                    PROTECT_METADATA(next_block, sizeof(Block));
                }
            }
            else
            {
                PROTECT_METADATA(next_block, sizeof(Block));
                break;
            }
        }

        if (can_expand)
        {
            block->size = total_size;
            if (block->size >= aligned_new_size + sizeof(Block) + 8)
            {
                Block* new_block = (Block*)((char*)block + sizeof(Block) + aligned_new_size);
                UNPROTECT_METADATA(new_block, sizeof(Block));
                new_block->magic = MAGIC_NUMBER;
                new_block->size = block->size - aligned_new_size - sizeof(Block);
                new_block->free = true;
                new_block->critical = block->critical;
                new_block->next = block->next;
                new_block->prev = block;
                if (block->next)
                {
                    UNPROTECT_METADATA(block->next, sizeof(Block));
                    block->next->prev = new_block;
                    PROTECT_METADATA(block->next, sizeof(Block));
                }
                block->next = new_block;
                block->size = aligned_new_size;
                PROTECT_METADATA(new_block, sizeof(Block));
            }
            PROTECT_METADATA(block, sizeof(Block));
            return ptr;
        }
        else
        {
            void* new_ptr = cma_malloc(new_size, critical);
            if (!new_ptr)
            {
                PROTECT_METADATA(block, sizeof(Block));
                return nullptr; // Allocation failed
            }
            size_t copy_size = block->size;
            memcpy(new_ptr, ptr, copy_size);
            cma_free(ptr);
            PROTECT_METADATA(block, sizeof(Block));
            return new_ptr;
        }
    }
}
