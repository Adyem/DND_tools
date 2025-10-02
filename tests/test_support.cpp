#include "test_support.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../dnd_tools.hpp"
#include <cstdio>
#include <cstdlib>

bool g_dnd_test = false;

void test_assert_true(int condition, const char *message)
{
    if (!condition)
    {
        std::fprintf(stderr, "Test failed: %s\n", message);
        cma_cleanup();
        std::exit(1);
    }
    return ;
}
