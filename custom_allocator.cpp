#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <iostream>

#define ALLOC_PAGE(size) malloc(size)
#define FREE_PAGE(ptr) free(ptr)
#define PAGE_SIZE 65536

#ifndef BYPASS_ALLOC
#define BYPASS_ALLOC DEBUG
#endif

#if BYPASS_ALLOC == 1

void* ft_malloc(size_t size, bool critical)
{
    (void)critical;
    return malloc(size);
}

void ft_free(void* ptr)
{
    free(ptr);
	return ;
}

void ft_cleanup_non_critical_memory()
{
	return ;
}

bool ft_ensure_memory_available(const size_t* sizes, size_t count, bool critical)
{
    (void)sizes;
    (void)count;
    (void)critical;
    return (true);
}

void ft_cleanup_all_memory()
{
	return ;
}

#else

#define MAGIC_NUMBER 0xDEADBEEF

struct Block
{
    uint32_t magic;
    size_t size;
    bool free;
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

void* ft_malloc(size_t size, bool critical)
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
                    new_block->next = block->next;
                    new_block->prev = block;
                    if (block->next)
                        block->next->prev = new_block;
                    block->next = new_block;
                    block->size = size;
                }
                block->free = false;
                return (void*)((char*)block + sizeof(Block));
            }
            block = block->next;
        }
        page = page->next;
    }
    size_t alloc_size = PAGE_SIZE;
    if (size + sizeof(Block) + sizeof(Page) > PAGE_SIZE)
        alloc_size = size + sizeof(Block) + sizeof(Page);
    void* page_memory = ALLOC_PAGE(alloc_size);
	if (!page_memory)
        return (nullptr);
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
    first_block->next = nullptr;
    first_block->prev = nullptr;
    new_page->blocks = first_block;
    return ((void*)((char*)first_block + sizeof(Block)));
}

void ft_free(void* ptr)
{
    if (!ptr)
        return ;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
	{
		std::cerr << "1-Invalid free detected at " << ptr << std::endl;
        abort();
    }
	if (block->free == true)
	{
		std::cerr << "2-Double free detected at " << ptr << std::endl;
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
            break ;
        page = page->next;
    }
    if (!page)
	{
		std::cerr << "3-Invalid free detected at " << ptr << std::endl;
        abort();
    }
    Block* blk = page->blocks;
    bool all_free = true;
    while (blk)
	{
        if (!blk->free)
		{
            all_free = false;
            break ;
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
        FREE_PAGE(page->start);
    }
	return ;
}

void ft_cleanup_non_critical_memory()
{
    Page* page = page_list;
    while (page)
	{
        Page* next_page = page->next;
        if (!page->critical)
		{
            Block* blk = page->blocks;
            bool all_free = true;
            while (blk) {
                if (!blk->free)
				{
                    all_free = false;
                    break ;
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
                FREE_PAGE(page->start);
            }
        }
        page = next_page;
    }
	return ;
}

bool ft_ensure_memory_available(const size_t* sizes, size_t count, bool critical)
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
        return (true);
	else
	{
        size_t alloc_size = PAGE_SIZE;
        while (total_free < total_needed) {
            void* page_memory = ALLOC_PAGE(alloc_size);
            if (!page_memory)
                return (false);
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
            first_block->next = nullptr;
            first_block->prev = nullptr;
            new_page->blocks = first_block;
            total_free += first_block->size + sizeof(Block);
        }
        return (true);
    }
}

void ft_cleanup_all_memory()
{
    Page* page = page_list;
    while (page)
	{
        Page* next_page = page->next;
        FREE_PAGE(page->start);
        page = next_page;
    }
    page_list = nullptr;
	return ;
}

bool ft_add_page(bool critical)
{
    size_t alloc_size = PAGE_SIZE;
    void* page_memory = ALLOC_PAGE(alloc_size);
    if (!page_memory)
        return (false);
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
    first_block->next = nullptr;
    first_block->prev = nullptr;
    new_page->blocks = first_block;
    return (true);
}

#endif
