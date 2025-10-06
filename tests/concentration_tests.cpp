#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../character.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include <filesystem>
#include <fstream>
#include <system_error>
#include <string>

static t_char g_stub_target;

static void reset_stub_target()
{
    g_stub_target = {};
    g_stub_target.name = "npc-target";
    g_stub_target.save_file = const_cast<char *>("data/npc-target");
    g_stub_target.version_number = 1;
    return ;
}

static t_char *load_stub_target(int index, const char **input, t_name *name, int exception)
{
    (void)index;
    (void)input;
    (void)name;
    (void)exception;
    return (&g_stub_target);
}

static void create_data_entry(const char *path)
{
    std::filesystem::create_directories("data");
    std::ofstream file(path);
    test_assert_true(file.good(), "Failed to create data entry for test");
    file.close();
    return ;
}

static void remove_data_entries()
{
    std::error_code remove_error;

    std::filesystem::remove_all("data", remove_error);
    return ;
}

static void test_validate_fetch_allows_npc_target()
{
    t_char      info = {};
    t_name      entry;
    int         error_code;
    t_char      *result;

    create_data_entry("data/npc-target");
    reset_stub_target();
    entry.name = const_cast<char *>("npc-target");
    entry.function = &load_stub_target;
    entry.next = ft_nullptr;
    info.struct_name = &entry;
    error_code = -1;
    result = ft_validate_and_fetch_target(const_cast<char *>("npc-target"), &info, &error_code);
    test_assert_true(result == &g_stub_target,
        "ft_validate_and_fetch_target should load NPC information when target exists");
    test_assert_true(error_code == 0,
        "ft_validate_and_fetch_target should report success for valid NPC target");
    remove_data_entries();
    return ;
}

static void test_validate_fetch_skips_player_character()
{
    t_char      info = {};
    t_name      entry;
    int         error_code;
    t_char      *result;
    const char  *file_path;
    std::string output;

    create_data_entry("data/pc--guardian");
    reset_stub_target();
    entry.name = const_cast<char *>("pc--guardian");
    entry.function = &load_stub_target;
    entry.next = ft_nullptr;
    info.struct_name = &entry;
    error_code = -1;
    file_path = "tests_output/concentration_skip_player.log";
    test_begin_output_capture(file_path);
    result = ft_validate_and_fetch_target(const_cast<char *>("pc--guardian"), &info, &error_code);
    test_end_output_capture();
    test_assert_true(result == ft_nullptr,
        "ft_validate_and_fetch_target should not load protected player characters");
    test_assert_true(error_code == 0,
        "ft_validate_and_fetch_target should not report an error for protected player characters");
    output = test_read_file_to_string(file_path);
    test_assert_true(output.empty(),
        "ft_validate_and_fetch_target should remain silent when skipping player characters");
    test_delete_file(file_path);
    remove_data_entries();
    return ;
}

static void test_validate_fetch_reports_missing_target()
{
    t_char      info = {};
    t_name      entry;
    int         error_code;
    t_char      *result;
    const char  *output_path;
    const char  *error_path;
    std::string output_log;
    std::string error_log;
    const char  *expected_message;

    std::filesystem::create_directories("data");
    reset_stub_target();
    entry.name = const_cast<char *>("npc-target");
    entry.function = &load_stub_target;
    entry.next = ft_nullptr;
    info.struct_name = &entry;
    error_code = -1;
    output_path = "tests_output/concentration_missing_target_output.log";
    error_path = "tests_output/concentration_missing_target_error.log";
    expected_message = "258-Error: Target does not exist";
    test_begin_output_capture(output_path);
    test_begin_error_capture(error_path);
    result = ft_validate_and_fetch_target(const_cast<char *>("unknown"), &info, &error_code);
    test_end_output_capture();
    test_end_error_capture();
    test_assert_true(result == ft_nullptr,
        "ft_validate_and_fetch_target should fail for missing targets");
    test_assert_true(error_code == 1,
        "ft_validate_and_fetch_target should propagate missing target error code");
    output_log = test_read_file_to_string(output_path);
    error_log = test_read_file_to_string(error_path);
    test_assert_true(!error_log.empty(),
        "ft_validate_and_fetch_target should report missing target errors");
    test_assert_true(!output_log.empty(),
        "ft_validate_and_fetch_target should describe missing target lookup");
    test_assert_true(error_log == expected_message
            || error_log == std::string(expected_message) + "\n",
        "ft_validate_and_fetch_target should log the missing target error code");
    test_assert_true(output_log == "111-Error: target does not exist"
            || output_log == "111-Error: target does not exist\n",
        "ft_validate_and_fetch_target should log the detailed missing target message");
    test_delete_file(output_path);
    test_delete_file(error_path);
    remove_data_entries();
    return ;
}

void run_concentration_tests()
{
    test_begin_suite("concentration_tests");
    test_validate_fetch_allows_npc_target();
    test_validate_fetch_skips_player_character();
    test_validate_fetch_reports_missing_target();
    test_end_suite_success();
    return ;
}
