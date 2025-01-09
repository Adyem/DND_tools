#include "CMA.hpp"
#include "CMA_internal.hpp"
#include "../CPP_class/nullptr.hpp"
#include <cstdlib>
#include <sys/mman.h>

extern Page *page_list;

void cma_cleanup()
{
	if (OFFSWITCH)
		return ;
    Page* current_page = page_list;
    while (current_page)
    {
        Page* next_page = current_page->next;
        if (current_page->start)
        {
            munmap(current_page->start, current_page->size);
        }
        free(current_page);
        current_page = next_page;
    }
    page_list = ft_nullptr;
	return ;
}
