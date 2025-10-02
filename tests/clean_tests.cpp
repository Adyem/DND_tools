#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include <filesystem>
#include <system_error>
#include <cstdio>

static void remove_data_path()
{
    std::error_code remove_error;

    std::filesystem::remove_all("data", remove_error);
    if (remove_error.value() != 0)
        std::remove("data");
    return ;
}

static void test_ft_clean_preserves_player_directory()
{
    std::error_code error;
    bool            exists_result;

    remove_data_path();
    std::filesystem::create_directories("data/PC--Example", error);
    test_assert_true(error.value() == 0, "failed to create player directory for test");
    error.clear();
    std::filesystem::create_directory("data/temp_dir", error);
    test_assert_true(error.value() == 0, "failed to create temporary directory for test");
    g_dnd_test = true;
    ft_clean();
    g_dnd_test = false;
    error.clear();
    exists_result = std::filesystem::exists("data/PC--Example", error);
    test_assert_true(error.value() == 0, "failed to check player directory existence");
    test_assert_true(exists_result == true, "ft_clean should preserve PC-- directories");
    error.clear();
    exists_result = std::filesystem::exists("data/temp_dir", error);
    test_assert_true(error.value() == 0, "failed to check temporary directory existence");
    test_assert_true(exists_result == false, "ft_clean should remove non-protected directories");
    remove_data_path();
    error.clear();
    std::filesystem::create_directory("data", error);
    test_assert_true(error.value() == 0, "failed to restore data directory after test");
    return ;
}

void run_clean_tests()
{
    test_ft_clean_preserves_player_directory();
    return ;
}

