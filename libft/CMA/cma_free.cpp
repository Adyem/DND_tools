#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <sys/mman.h>
#include <valgrind/memcheck.h>
#include <csignal>
#include "CMA.hpp"
#include "CMA_internal.hpp"
#include "../Printf/printf.hpp"

void cma_free(void* ptr)
{
    if (OFFSWITCH == 1)
    {
        free(ptr);
        return ;
    }
    if (!ptr)
        return ;
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    if (block->magic != MAGIC_NUMBER)
	{
		pf_printf_fd(2, "Invalid block detected in cma_free. \n");
		print_block_info(block);
        raise(SIGSEGV);
	}
    block->free = true;
    merge_block(block);
	return ;
}
