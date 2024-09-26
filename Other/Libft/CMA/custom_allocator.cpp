#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <new>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"

Page *page_list = nullptr;

static inline size_t align8(size_t size)
{
    return ((size + 7) & ~7);
}

void	*cma_malloc(int size, bool critical)
{
    size = align8(size);

    if (size == 0)
        return (nullptr);
    Page* page = page_list;
    while (page)
    {
        UNPROTECT_METADATA(page, sizeof(Page));
        if (page->critical != critical)
        {
            PROTECT_METADATA(page, sizeof(Page));
            page = page->next;
            continue;
        }
        Block* block = page->blocks;
        while (block)
        {
            UNPROTECT_METADATA(block, sizeof(Block));
            if (block->free && block->size >= static_cast<size_t>(size))
			{
                if (block->size >= size + sizeof(Block) + 8)
                {
                    Block* new_block = (Block*)((char*)block + sizeof(Block) + size);
                    UNPROTECT_METADATA(new_block, sizeof(Block));
                    new_block->magic = MAGIC_NUMBER;
                    new_block->size = block->size - size - sizeof(Block);
                    new_block->free = true;
                    new_block->critical = page->critical;
                    new_block->next = block->next;
                    new_block->prev = block;
                    if (block->next)
                    {
                        UNPROTECT_METADATA(block->next, sizeof(Block));
                        block->next->prev = new_block;
                        PROTECT_METADATA(block->next, sizeof(Block));
                    }
                    block->next = new_block;
                    block->size = size;
                    PROTECT_METADATA(new_block, sizeof(Block));
                }
                block->free = false;
                block->critical = page->critical;
                PROTECT_METADATA(block, sizeof(Block));
                PROTECT_METADATA(page, sizeof(Page));
                void *user_ptr = (char *)block + sizeof(Block);
                return (user_ptr);
            }
            Block* next_block = block->next;
            PROTECT_METADATA(block, sizeof(Block));
            block = next_block;
        }
        Page* next_page = page->next;
        PROTECT_METADATA(page, sizeof(Page));
        page = next_page;
    }
    size_t alloc_size = PAGE_SIZE;
    if (size + sizeof(Block) + sizeof(Page) > PAGE_SIZE)
        alloc_size = size + sizeof(Block) + sizeof(Page);
    void* page_memory = ::operator new(alloc_size);
    if (!page_memory)
        return (nullptr);
    memset(page_memory, 0, alloc_size);
    Page* new_page = (Page*)page_memory;
    new_page->start = page_memory;
    new_page->size = alloc_size;
    new_page->critical = critical;
    new_page->next = page_list;
    if (page_list)
    {
        UNPROTECT_METADATA(page_list, sizeof(Page));
        page_list->prev = new_page;
        PROTECT_METADATA(page_list, sizeof(Page));
    }
    new_page->prev = nullptr;
    page_list = new_page;
    Block* first_block = (Block*)((char*)page_memory + sizeof(Page));
    first_block->magic = MAGIC_NUMBER;
    first_block->size = alloc_size - sizeof(Page) - sizeof(Block);
    first_block->free = false;
    first_block->critical = critical;
    first_block->next = nullptr;
    first_block->prev = nullptr;
    new_page->blocks = first_block;
    PROTECT_METADATA(first_block, sizeof(Block));
    PROTECT_METADATA(new_page, sizeof(Page));
    void* user_ptr = (char*)first_block + sizeof(Block);
    return (user_ptr);
}

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

void cma_free(void* ptr)
{
    if (!ptr)
        return;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    UNPROTECT_METADATA(block, sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
    {
        std::cerr << "Invalid free detected at " << ptr << std::endl;
        raise(SIGSEGV);
    }
    if (block->free)
    {
        std::cerr << "Double free detected at " << ptr << std::endl;
        raise(SIGSEGV);
    }
    block->free = true;
	if (block->prev)
	{
        UNPROTECT_METADATA(block->prev, sizeof(Block));
		if (block->prev->free)
		{
			block->prev->size += sizeof(Block) + block->size;
			block->prev->next = block->next;
			if (block->next)
			{
                UNPROTECT_METADATA(block->next, sizeof(Block));
                block->next->prev = block->prev;
                PROTECT_METADATA(block->next, sizeof(Block));
			}
			PROTECT_METADATA(block, sizeof(Block));
			block = block->prev;
		}
		else
		{
			PROTECT_METADATA(block->prev, sizeof(Block));
		}
	}
	if (block->next)
	{
        UNPROTECT_METADATA(block->next, sizeof(Block));
		if (block->next->free)
        {
			block->size += sizeof(Block) + block->next->size;
			block->next = block->next->next;
			if (block->next)
			{
                UNPROTECT_METADATA(block->next, sizeof(Block));
                block->next->prev = block;
                PROTECT_METADATA(block->next, sizeof(Block));
			}
		}
		else
		{
			PROTECT_METADATA(block->next, sizeof(Block));
		}
	}
	PROTECT_METADATA(block, sizeof(Block));
	Page* page = page_list;
	while (page)
    {
        UNPROTECT_METADATA(page, sizeof(Page));
        if ((char*)block >= (char*)page->start && (char*)block < (char*)page->start + page->size)
            break;
        Page* next_page = page->next;
        PROTECT_METADATA(page, sizeof(Page));
        page = next_page;
    }
    if (!page)
    {
        std::cerr << "Invalid free detected at " << ptr << std::endl;
        raise(SIGSEGV);
    }
    Block* blk = page->blocks;
    bool all_free = true;
    while (blk)
    {
        UNPROTECT_METADATA(blk, sizeof(Block));
        if (!blk->free)
        {
            all_free = false;
            PROTECT_METADATA(blk, sizeof(Block));
            break;
        }
        Block* next_blk = blk->next;
        PROTECT_METADATA(blk, sizeof(Block));
        blk = next_blk;
	}
	if (all_free)
	{
        if (page->prev)
        {
            UNPROTECT_METADATA(page->prev, sizeof(Page));
            page->prev->next = page->next;
            PROTECT_METADATA(page->prev, sizeof(Page));
        }
        else
            page_list = page->next;
        if (page->next)
        {
            UNPROTECT_METADATA(page->next, sizeof(Page));
            page->next->prev = page->prev;
            PROTECT_METADATA(page->next, sizeof(Page));
        }
        UNPROTECT_METADATA(page->start, page->size);
        ::operator delete(page->start);
    }
	else
	{
        PROTECT_METADATA(page, sizeof(Page));
	}
	return ;
}

void cma_cleanup_non_critical_memory()
{
    Page* page = page_list;
    while (page)
    {
        UNPROTECT_METADATA(page, sizeof(Page));
        Page* next_page = page->next;
        if (!page->critical)
        {
            Block* blk = page->blocks;
            bool all_free = true;
            while (blk)
            {
                UNPROTECT_METADATA(blk, sizeof(Block));
                if (!blk->free)
                {
                    all_free = false;
                    PROTECT_METADATA(blk, sizeof(Block));
                    break;
                }
                Block* next_blk = blk->next;
                PROTECT_METADATA(blk, sizeof(Block));
                blk = next_blk;
            }
            if (all_free)
            {
                if (page->prev)
                {
                    UNPROTECT_METADATA(page->prev, sizeof(Page));
                    page->prev->next = page->next;
                    PROTECT_METADATA(page->prev, sizeof(Page));
                }
                else
				{
                    page_list = page->next;
				}
                if (page->next)
                {
                    UNPROTECT_METADATA(page->next, sizeof(Page));
                    page->next->prev = page->prev;
                    PROTECT_METADATA(page->next, sizeof(Page));
                }
                UNPROTECT_METADATA(page->start, page->size);
                ::operator delete(page->start);
            }
            else
			{
                PROTECT_METADATA(page, sizeof(Page));
			}
        }
        else
		{
            PROTECT_METADATA(page, sizeof(Page));
		}
        page = next_page;
    }
	return ;
}

void cma_cleanup_all_memory()
{
    Page* page = page_list;
    while (page)
    {
        UNPROTECT_METADATA(page, sizeof(Page));
        Page* next_page = page->next;
        UNPROTECT_METADATA(page->start, page->size);
        ::operator delete(page->start);
        page = next_page;
    }
    page_list = (nullptr);
	return ;
}

bool cma_add_page(bool critical)
{
    size_t alloc_size = PAGE_SIZE;
    void* page_memory = ::operator new(alloc_size, std::nothrow);
    if (!page_memory)
        return (false);
    Page* new_page = (Page*)page_memory;
    new_page->start = page_memory;
    new_page->size = alloc_size;
    new_page->critical = critical;
    new_page->next = page_list;
    if (page_list)
    {
        UNPROTECT_METADATA(page_list, sizeof(Page));
        page_list->prev = new_page;
        PROTECT_METADATA(page_list, sizeof(Page));
    }
    new_page->prev = nullptr;
    page_list = new_page;
    Block* first_block = (Block*)((char*)page_memory + sizeof(Page));
    first_block->magic = MAGIC_NUMBER;
    first_block->size = alloc_size - sizeof(Page) - sizeof(Block);
    first_block->free = true;
    first_block->critical = critical;
    first_block->next = nullptr;
    first_block->prev = nullptr;
    new_page->blocks = first_block;
    PROTECT_METADATA(first_block, sizeof(Block));
    PROTECT_METADATA(new_page, sizeof(Page));
    return (true);
}
