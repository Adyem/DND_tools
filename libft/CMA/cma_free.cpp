#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"
#include "../Printf/printf.hpp"

void print_block_info(Block* block)
{
    if (!block)
    {
        pf_printf_fd(2, "Block pointer is NULL.\n");
        return ;
    }
    const char* free_status;
    if (block->free)
        free_status = "Yes";
    else
        free_status = "No";
    const char* critical_status;
    if (block->critical)
        critical_status = "Yes";
    else
        critical_status = "No";
    pf_printf_fd(2, "---- Block Information ----\n");
    pf_printf_fd(2, "Address of Block: %p\n", (void*)block);
    pf_printf_fd(2, "Magic Number: 0x%X\n", block->magic);
    pf_printf_fd(2, "Size: %zu bytes\n", block->size);
    pf_printf_fd(2, "Free: %s\n", free_status);
    pf_printf_fd(2, "Critical: %s\n", critical_status);
    pf_printf_fd(2, "Next Block: %p\n", (void*)block->next);
    pf_printf_fd(2, "Previous Block: %p\n", (void*)block->prev);
    pf_printf_fd(2, "---------------------------\n");
	return ;
}

void cma_free(void* ptr)
{
    if (DEBUG == 1 || OFFSWITCH == 1)
    {
        free(ptr);
        return ;
    }

    if (!ptr)
        return ;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    UNPROTECT_METADATA(block, sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
    {
        pf_printf_fd(2, "Invalid free detected at %p\n", ptr);
        print_block_info(block);
        raise(SIGSEGV);
    }
    if (block->free)
    {
        pf_printf_fd(2, "Double free detected at %p\n", ptr);
        print_block_info(block);
        raise(SIGSEGV);
    }
    block->free = true;
    while (block->next)
    {
        UNPROTECT_METADATA(block->next, sizeof(Block));
        if (!block->next->free)
        {
            PROTECT_METADATA(block->next, sizeof(Block));
            break ;
        }
        block->size += sizeof(Block) + block->next->size;
        memset(block->next, 0, sizeof(Block));
        Block* mergedNext = block->next->next;
        if (mergedNext)
        {
            UNPROTECT_METADATA(mergedNext, sizeof(Block));
            mergedNext->prev = block;
            PROTECT_METADATA(mergedNext, sizeof(Block));
        }
        block->next = mergedNext;
        PROTECT_METADATA(block, sizeof(Block));
        UNPROTECT_METADATA(block, sizeof(Block));
    }
    PROTECT_METADATA(block, sizeof(Block));
    Page* page = page_list;
    while (page)
    {
        UNPROTECT_METADATA(page, sizeof(Page));
        if ((char*)block >= (char*)page->start && 
            (char*)block <  (char*)page->start + page->size)
            break ;
        Page* next_page = page->next;
        PROTECT_METADATA(page, sizeof(Page));
        page = next_page;
    }
    if (!page)
    {
        pf_printf_fd(2, "Invalid free detected at %p (page not found)\n", ptr);
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
            break ;
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
        free(page->start);
        memset(page, 0, sizeof(Page));
    }
    else
        PROTECT_METADATA(page, sizeof(Page));
    return ;
}
