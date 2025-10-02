#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Errno/errno.hpp"
#include "../libft/File/file_utils.hpp"
#include "../libft/File/open_dir.hpp"
#include "../libft/System_utils/system_utils.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include <filesystem>
#include <system_error>
#include <cstdio>
#include <fcntl.h>

static void remove_data_path()
{
    std::error_code remove_error;

    std::filesystem::remove_all("data", remove_error);
    if (remove_error.value() != 0)
        std::remove("data");
    return ;
}

static void test_create_data_dir_creates_directory_when_missing()
{
    int result;

    remove_data_path();
    result = ft_create_data_dir();
    test_assert_true(result == 0, "ft_create_data_dir should create missing data directory");
    test_assert_true(file_dir_exists("data") == 1, "ft_create_data_dir did not create the data directory");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_create_data_dir should set errno to success after creating directory");
    remove_data_path();
    return ;
}

static void test_create_data_dir_handles_existing_directory()
{
    int result;

    remove_data_path();
    test_assert_true(file_create_directory("data", 0700) == 0, "failed to create directory for setup");
    result = ft_create_data_dir();
    test_assert_true(result == 0, "ft_create_data_dir should succeed when directory already exists");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_create_data_dir should leave errno as success when directory exists");
    remove_data_path();
    return ;
}

static void test_create_data_dir_reports_file_collision()
{
    su_file *file_handle;
    int result;

    remove_data_path();
    file_handle = su_fopen("data", O_CREAT | O_RDWR, 0600);
    test_assert_true(file_handle != ft_nullptr, "failed to create file for collision test");
    if (file_handle != ft_nullptr)
        test_assert_true(su_fclose(file_handle) == 0, "failed to close collision file");
    result = ft_create_data_dir();
    test_assert_true(result == 1, "ft_create_data_dir should fail when path is a file");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_create_data_dir should not modify errno for collision case");
    test_assert_true(file_exists("data") == 1, "collision file should remain after failure");
    test_assert_true(file_delete("data") == 0, "failed to delete collision file");
    return ;
}

void run_create_data_folder_tests()
{
    test_create_data_dir_creates_directory_when_missing();
    test_create_data_dir_handles_existing_directory();
    test_create_data_dir_reports_file_collision();
    remove_data_path();
    return ;
}
