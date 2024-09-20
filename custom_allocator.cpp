#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <iostream>
#include "dnd_tools.hpp"

#define PAGE_SIZE 65536

#ifndef BYPASS_ALLOC
#define BYPASS_ALLOC DEBUG
#endif

#define MAGIC_NUMBER 0xDEADBEEF

struct Block
{
    uint32_t magic;
    size_t size;
    bool free;
    bool critical;
    Block* next;
    Block* prev;
};

#if BYPASS_ALLOC == 1

Block* block_list = nullptr;

inline size_t align8(size_t size)
{
    return ((size + 7) & ~7);
}

void* cma_malloc(size_t size, bool critical)
{
    size = align8(size);

    // Allocate memory for Block and data together
    size_t total_size = sizeof(Block) + size;
    Block* block = (Block*)::operator new(total_size);
    if (!block)
        return nullptr;
    block->magic = MAGIC_NUMBER;
    block->size = size;
    block->free = false;
    block->critical = critical;
    block->prev = nullptr;
    block->next = block_list;
    if (block_list)
        block_list->prev = block;
    block_list = block;
    return (void*)((char*)block + sizeof(Block));
}

void cma_free(void* ptr)
{
    if (!ptr)
        return;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
    {
        std::cerr << "Invalid free detected at " << ptr << std::endl;
        abort();
    }
    if (block->free)
    {
        std::cerr << "Double free detected at " << ptr << std::endl;
        abort();
    }
    block->free = true;
    // Blocks are cleaned up in cma_cleanup_non_critical_memory or cma_cleanup_all_memory
}

void cma_cleanup_non_critical_memory()
{
    Block* block = block_list;
    while (block)
    {
        Block* next_block = block->next;
        if (!block->critical && block->free)
        {
            // Remove block from block_list
            if (block->prev)
                block->prev->next = block->next;
            else
                block_list = block->next;
            if (block->next)
                block->next->prev = block->prev;

            // Free the block
            ::operator delete(block);
        }
        block = next_block;
    }
}

bool cma_ensure_memory_available(const size_t* sizes, size_t count, bool critical)
{
    for (size_t i = 0; i < count; ++i)
    {
        size_t size = align8(sizes[i]);
        size_t total_size = sizeof(Block) + size;
        Block* block = (Block*)::operator new(total_size, std::nothrow);
        if (!block)
            return false;
        ::operator delete(block);
    }
    return true;
}

void cma_cleanup_all_memory()
{
    Block* block = block_list;
    while (block)
    {
        Block* next_block = block->next;
        ::operator delete(block);
        block = next_block;
    }
    block_list = nullptr;
}

bool cma_add_page(bool critical)
{
    // Not applicable when BYPASS_ALLOC is set
    return true;
}

#else

struct Page
{
    void* start;
    size_t size;
    Page* next;
    Page* prev;
    Block* blocks;
    bool critical;
};

Page* page_list = nullptr;

inline size_t align8(size_t size)
{
    return ((size + 7) & ~7);
}

void* cma_malloc(size_t size, bool critical)
{
    size = align8(size);

    Page* page = page_list;
    while (page)
    {
        if (page->critical != critical)
        {
            page = page->next;
            continue;
        }
        Block* block = page->blocks;
        while (block)
        {
            if (block->free && block->size >= size)
            {
                if (block->size >= size + sizeof(Block) + 8)
                {
                    Block* new_block = (Block*)((char*)block + sizeof(Block) + size);
                    new_block->magic = MAGIC_NUMBER;
                    new_block->size = block->size - size - sizeof(Block);
                    new_block->free = true;
                    new_block->critical = page->critical;
                    new_block->next = block->next;
                    new_block->prev = block;
                    if (block->next)
                        block->next->prev = new_block;
                    block->next = new_block;
                    block->size = size;
                }
                block->free = false;
                block->critical = page->critical;
                return (void*)((char*)block + sizeof(Block));
            }
            block = block->next;
        }
        page = page->next;
    }
    size_t alloc_size = PAGE_SIZE;
    if (size + sizeof(Block) + sizeof(Page) > PAGE_SIZE)
        alloc_size = size + sizeof(Block) + sizeof(Page);
    void* page_memory = ::operator new(alloc_size);
    if (!page_memory)
        return nullptr;
    memset(page_memory, 0, alloc_size);
    Page* new_page = (Page*)page_memory;
    new_page->start = page_memory;
    new_page->size = alloc_size;
    new_page->critical = critical;
    new_page->next = page_list;
    if (page_list)
        page_list->prev = new_page;
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
    return (void*)((char*)first_block + sizeof(Block));
}

void cma_free(void* ptr)
{
    if (!ptr)
        return;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
    {
        std::cerr << "Invalid free detected at " << ptr << std::endl;
        abort();
    }
    if (block->free)
    {
        std::cerr << "Double free detected at " << ptr << std::endl;
        abort();
    }
    block->free = true;
    if (block->prev && block->prev->free)
    {
        block->prev->size += sizeof(Block) + block->size;
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
        block = block->prev;
    }
    if (block->next && block->next->free)
    {
        block->size += sizeof(Block) + block->next->size;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }
    Page* page = page_list;
    while (page)
    {
        if ((char*)block >= (char*)page->start && (char*)block < (char*)page->start + page->size)
            break;
        page = page->next;
    }
    if (!page)
    {
        std::cerr << "Invalid free detected at " << ptr << std::endl;
        abort();
    }
    Block* blk = page->blocks;
    bool all_free = true;
    while (blk)
    {
        if (!blk->free)
        {
            all_free = false;
            break;
        }
        blk = blk->next;
    }
    if (all_free)
    {
        if (page->prev)
            page->prev->next = page->next;
        else
            page_list = page->next;
        if (page->next)
            page->next->prev = page->prev;
        ::operator delete(page->start);
    }
}

void cma_cleanup_non_critical_memory()
{
    Page* page = page_list;
    while (page)
    {
        Page* next_page = page->next;
        if (!page->critical)
        {
            Block* blk = page->blocks;
            bool all_free = true;
            while (blk)
            {
                if (!blk->free)
                {
                    all_free = false;
                    break;
                }
                blk = blk->next;
            }
            if (all_free)
            {
                if (page->prev)
                    page->prev->next = page->next;
                else
                    page_list = page->next;
                if (page->next)
                    page->next->prev = page->prev;
                ::operator delete(page->start);
            }
        }
        page = next_page;
    }
}

bool cma_ensure_memory_available(const size_t* sizes, size_t count, bool critical)
{
    size_t total_needed = 0;
    for (size_t i = 0; i < count; ++i)
        total_needed += align8(sizes[i]) + sizeof(Block);
    size_t total_free = 0;
    Page* page = page_list;
    while (page)
    {
        if (page->critical == critical)
        {
            Block* block = page->blocks;
            while (block)
            {
                if (block->free)
                    total_free += block->size + sizeof(Block);
                block = block->next;
            }
        }
        page = page->next;
    }
    if (total_free >= total_needed)
        return true;
    else
    {
        size_t alloc_size = PAGE_SIZE;
        while (total_free < total_needed)
        {
            void* page_memory = new(std::nothrow) char[alloc_size];
            if (!page_memory)
                return false;
            Page* new_page = (Page*)page_memory;
            new_page->start = page_memory;
            new_page->size = alloc_size;
            new_page->next = page_list;
            if (page_list)
                page_list->prev = new_page;
            new_page->prev = nullptr;
            new_page->critical = critical;
            page_list = new_page;
            Block* first_block = (Block*)((char*)page_memory + sizeof(Page));
            first_block->magic = MAGIC_NUMBER;
            first_block->size = alloc_size - sizeof(Page) - sizeof(Block);
            first_block->free = true;
            first_block->critical = critical;
            first_block->next = nullptr;
            first_block->prev = nullptr;
            new_page->blocks = first_block;
            total_free += first_block->size + sizeof(Block);
        }
        return true;
    }
}

void cma_cleanup_all_memory()
{
    Page* page = page_list;
    while (page)
    {
        Page* next_page = page->next;
        ::operator delete(page->start);
        page = next_page;
    }
    page_list = nullptr;
}

bool cma_add_page(bool critical)
{
    size_t alloc_size = PAGE_SIZE;
    void* page_memory = new(std::nothrow) char[alloc_size];
    if (!page_memory)
        return false;
    Page* new_page = (Page*)page_memory;
    new_page->start = page_memory;
    new_page->size = alloc_size;
    new_page->critical = critical;
    new_page->next = page_list;
    if (page_list)
        page_list->prev = new_page;
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
    return true;
}

#endif
