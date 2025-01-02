#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"

void cma_cleanup_non_critical_memory()
{
	if (DEBUG == 1 || OFFSWITCH == 1)
		return ;
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
                free(page->start);
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
