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

typedef unsigned int uint32_t;

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

Page* page_list = nullptr;

inline size_t align8(size_t size)
{
    return ((size + 7) & ~7);
}

void* cma_malloc(size_t size, bool critical)
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
            if (block->free && block->size >= size)
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
            PROTECT_METADATA(block->prev, sizeof(Block));
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
            PROTECT_METADATA(block->next, sizeof(Block));
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
        PROTECT_METADATA(page, sizeof(Page));
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
                PROTECT_METADATA(page, sizeof(Page));
        }
        else
            PROTECT_METADATA(page, sizeof(Page));
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
