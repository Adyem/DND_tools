#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Libft/libft.hpp"

static void remove_data_path()
{
    test_remove_directory("data");
    test_remove_path("data");
    return ;
}

static void test_ft_clean_preserves_player_directory()
{
    int exists_result;

    remove_data_path();
    test_create_directory("data/PC--Example");
    test_assert_true(ft_errno == ER_SUCCESS, "failed to create player directory for test");
    test_create_directory("data/temp_dir");
    test_assert_true(ft_errno == ER_SUCCESS, "failed to create temporary directory for test");
    g_dnd_test = true;
    ft_clean();
    g_dnd_test = false;
    exists_result = test_path_exists("data/PC--Example");
    test_assert_true(exists_result == 1, "ft_clean should preserve PC-- directories");
    exists_result = test_path_exists("data/temp_dir");
    test_assert_true(exists_result == 0, "ft_clean should remove non-protected directories");
    remove_data_path();
    test_create_directory("data");
    test_assert_true(ft_errno == ER_SUCCESS, "failed to restore data directory after test");
    return ;
}

void run_clean_tests()
{
    test_begin_suite("clean_tests");
    test_ft_clean_preserves_player_directory();
    test_end_suite_success();
    return ;
}

