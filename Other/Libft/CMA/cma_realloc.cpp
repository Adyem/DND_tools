#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <sys/mman.h>
#include <csignal>
#include "CMA.hpp"

void* cma_realloc(void* ptr, size_t new_size, bool critical)
{
    if (ptr == nullptr)
    {
        // Equivalent to malloc if ptr is nullptr
        return cma_malloc(new_size, critical);
    }
    if (new_size == 0)
    {
        // Equivalent to free if new_size is zero
        cma_free(ptr);
        return nullptr;
    }

    size_t aligned_new_size = align8(new_size);

    // Retrieve the metadata block associated with ptr
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    UNPROTECT_METADATA(block, sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
    {
        std::cerr << "Invalid realloc detected at " << ptr << std::endl;
        raise(SIGSEGV);
    }

    // If the new size is less than or equal to the current size, we may shrink the block
    if (aligned_new_size <= block->size)
    {
        // Optionally split the block if the leftover space is enough for a new block
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
        // Try to expand the block in place by checking adjacent free blocks
        size_t total_size = block->size;
        Block* curr_block = block;
        bool can_expand = false;

        // Loop through next adjacent free blocks
        while (curr_block->next)
        {
            Block* next_block = curr_block->next;
            UNPROTECT_METADATA(next_block, sizeof(Block));
            if (next_block->free && next_block->critical == block->critical)
            {
                total_size += sizeof(Block) + next_block->size;
                if (total_size >= aligned_new_size)
                {
                    // Merge the blocks
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
            // Adjust the size of the block
            block->size = total_size;

            // Optionally split the block if there's excess space
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
            // Cannot expand in place, allocate a new block
            void* new_ptr = cma_malloc(new_size, critical);
            if (!new_ptr)
            {
                PROTECT_METADATA(block, sizeof(Block));
                return nullptr; // Allocation failed
            }
            // Copy data from old block to new block
            size_t copy_size = block->size;
            memcpy(new_ptr, ptr, copy_size);
            cma_free(ptr);
            PROTECT_METADATA(block, sizeof(Block));
            return new_ptr;
        }
    }
}
