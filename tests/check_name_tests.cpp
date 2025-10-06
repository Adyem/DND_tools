#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include <filesystem>
#include <system_error>
#include <fstream>
#include <cstdio>
#include <string>

static void reset_data_directory()
{
    std::error_code remove_error;
    std::error_code create_error;

    std::filesystem::remove_all("data", remove_error);
    if (remove_error.value() != 0)
        std::remove("data");
    std::filesystem::create_directory("data", create_error);
    test_assert_true(create_error.value() == 0,
        "failed to create data directory for check_name tests");
    return ;
}

static void create_test_file(const char *path)
{
    std::ofstream stream;

    stream.open(path);
    test_assert_true(stream.is_open() == true, "failed to create test save file");
    stream << "{}";
    stream.close();
    return ;
}

static void test_check_name_handles_pc_prefix_variants()
{
    int result;

    reset_data_directory();
    create_test_file("data/PC--Guardian");
    create_test_file("data/data--notes");

    result = ft_check_player_character("PC--Guardian");
    test_assert_true(result == 0,
        "ft_check_player_character should match exact prefixed name");
    result = ft_check_player_character("Guardian");
    test_assert_true(result == 0,
        "ft_check_player_character should match player without prefix");
    result = ft_check_player_character("data--notes");
    test_assert_true(result == 1,
        "ft_check_player_character should ignore data-- entries");

    result = ft_set_stats_check_name("PC--Guardian");
    test_assert_true(result == 0,
        "ft_set_stats_check_name should match prefixed player name");
    result = ft_set_stats_check_name("Guardian");
    test_assert_true(result == 0,
        "ft_set_stats_check_name should match player without prefix");

    reset_data_directory();
    return ;
}

static void test_set_stats_check_name_rejects_null_name()
{
    int         result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    reset_data_directory();
    file_path = "tests_output/check_name_null_name.log";
    test_begin_error_capture(file_path);
    result = ft_set_stats_check_name(NULL);
    test_end_error_capture();
    test_assert_true(result == -1, "ft_set_stats_check_name should return -1 when name is null");
    error_output = test_read_file_to_string(file_path);
    expected_message = "259-Error: Name does not exist\n";
    test_assert_true(error_output == expected_message,
        "ft_set_stats_check_name should log null name error message");
    test_delete_file(file_path);
    reset_data_directory();
    return ;
}

static void test_set_stats_check_name_reports_missing_target()
{
    int         result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    reset_data_directory();
    file_path = "tests_output/check_name_missing_target.log";
    test_begin_error_capture(file_path);
    result = ft_set_stats_check_name("Unknown");
    test_end_error_capture();
    test_assert_true(result == 1, "ft_set_stats_check_name should return 1 when target does not exist");
    error_output = test_read_file_to_string(file_path);
    expected_message = "258-Error: Target does not exist\n";
    test_assert_true(error_output == expected_message,
        "ft_set_stats_check_name should log missing target error message");
    test_delete_file(file_path);
    reset_data_directory();
    return ;
}

void run_check_name_tests()
{
    test_begin_suite("check_name_tests");
    test_check_name_handles_pc_prefix_variants();
    test_set_stats_check_name_rejects_null_name();
    test_set_stats_check_name_reports_missing_target();
    test_end_suite_success();
    return ;
}
