#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <new>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"

Page *page_list = nullptr;

size_t align8(size_t size)
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
    size_t remaining_size = alloc_size - sizeof(Page) - sizeof(Block) - size;
    if (remaining_size >= sizeof(Block) + 8)
    {
        Block* free_block = (Block*)((char*)first_block + sizeof(Block) + size);
        UNPROTECT_METADATA(free_block, sizeof(Block));
        free_block->magic = MAGIC_NUMBER;
        free_block->size = remaining_size;
        free_block->free = true;
        free_block->critical = critical;
        free_block->next = nullptr;
        free_block->prev = first_block;
        first_block->next = free_block;
        PROTECT_METADATA(free_block, sizeof(Block));
    }
    else
        first_block->size += remaining_size;
    new_page->blocks = first_block;
    PROTECT_METADATA(first_block, sizeof(Block));
    PROTECT_METADATA(new_page, sizeof(Page));
    void* user_ptr = (char*)first_block + sizeof(Block);
    return (user_ptr);
}
