#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <new>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"

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
