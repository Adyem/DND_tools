#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include <cstdio>

int main()
{
    run_string_prefix_tests();
    run_ordinal_suffix_tests();
    run_roll_validation_tests();
    run_create_data_folder_tests();
    cma_cleanup();
    std::printf("All tests passed.\n");
    return (0);
}
