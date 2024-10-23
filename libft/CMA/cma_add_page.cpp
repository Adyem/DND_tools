#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"

bool cma_add_page(bool critical)
{
	if (DEBUG == 1 || OFFSWITCH == 1)
		return (false);
    size_t alloc_size = PAGE_SIZE;
    void* page_memory = malloc(alloc_size);
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
