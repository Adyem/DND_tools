#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Libft/libft.hpp"
#include "../libft/CPP_class/class_ofstream.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void reset_data_directory()
{
    test_remove_directory("data");
    test_remove_path("data");
    test_create_directory("data");
    test_assert_true(ft_errno == ER_SUCCESS,
        "failed to create data directory for check_name tests");
    return ;
}

static void create_test_file(const char *path)
{
    ft_ofstream stream;

    test_assert_true(stream.open(path) == 0, "failed to create test save file");
    test_assert_true(stream.write("{}") == 2, "failed to write test save data");
    stream.close();
    test_assert_true(stream.get_error() == ER_SUCCESS,
        "failed to close test save file");
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
    ft_string   error_output;
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

static void test_check_name_handles_case_insensitive_prefixes()
{
    int result;

    reset_data_directory();
    create_test_file("data/pc--Ranger");
    create_test_file("data/DATA--Archive");

    result = ft_set_stats_check_name("Ranger");
    test_assert_true(result == 0,
        "ft_set_stats_check_name should match player names with lowercase pc prefix");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_set_stats_check_name should set ft_errno to ER_SUCCESS on success");

    result = ft_check_player_character("Ranger");
    test_assert_true(result == 0,
        "ft_check_player_character should match player names with lowercase pc prefix");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_check_player_character should set ft_errno to ER_SUCCESS on success");

    result = ft_set_stats_check_name("Archive");
    test_assert_true(result == 1,
        "ft_set_stats_check_name should ignore names with the data prefix regardless of case");

    result = ft_check_player_character("Archive");
    test_assert_true(result == 1,
        "ft_check_player_character should ignore names that do not use the pc prefix");

    reset_data_directory();
    return ;
}

static void test_set_stats_check_name_reports_missing_target()
{
    int         result;
    const char  *file_path;
    ft_string   error_output;
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
    test_check_name_handles_case_insensitive_prefixes();
    test_set_stats_check_name_reports_missing_target();
    test_end_suite_success();
    return ;
}
