#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include <filesystem>
#include <fstream>
#include <string>

static void remove_data_directory()
{
    std::error_code error;

    std::filesystem::remove_all("data", error);
    return ;
}

static void ensure_data_directory()
{
    std::error_code error;

    std::filesystem::create_directories("data", error);
    test_assert_true(error.value() == 0, "failed to create data directory for test setup");
    return ;
}

static void create_data_file(const std::string &name)
{
    std::ofstream file_stream;

    ensure_data_directory();
    file_stream.open("data/" + name);
    test_assert_true(file_stream.is_open(), "failed to create data file for test setup");
    file_stream.close();
    return ;
}

static void test_initialize_variables_zeros_target_data()
{
    t_target_data    target_data;
    size_t           index;

    target_data.buff_info = reinterpret_cast<t_buff *>(0x1);
    index = 0;
    while (index < 20)
    {
        target_data.Pchar_name[index] = reinterpret_cast<char *>(0x1);
        index++;
    }
    ft_initialize_variables(&target_data);
    test_assert_true(target_data.buff_info == ft_nullptr,
        "ft_initialize_variables should reset buff_info to null");
    index = 0;
    while (index < 20)
    {
        test_assert_true(target_data.Pchar_name[index] == ft_nullptr,
            "ft_initialize_variables should clear Pchar_name entries");
        index++;
    }
    return ;
}

static void test_is_caster_name_present_detects_existing_entries()
{
    ft_set<ft_string>    caster_names;
    int                  result;

    caster_names.insert(ft_string("Alice"));
    test_assert_true(caster_names.get_error() == ER_SUCCESS,
        "ft_set should insert caster names without error");
    result = ft_is_caster_name_present(&caster_names, "Alice");
    test_assert_true(result == 1, "ft_is_caster_name_present should find existing names");
    result = ft_is_caster_name_present(&caster_names, "Bob");
    test_assert_true(result == 0, "ft_is_caster_name_present should return zero when name is absent");
    result = ft_is_caster_name_present(ft_nullptr, "Alice");
    test_assert_true(result == 0, "ft_is_caster_name_present should handle null set pointer");
    result = ft_is_caster_name_present(&caster_names, ft_nullptr);
    test_assert_true(result == 0, "ft_is_caster_name_present should handle null name pointer");
    return ;
}

static void test_is_caster_name_present_handles_multiple_entries()
{
    ft_set<ft_string>    caster_names;
    int                  result;

    caster_names.insert(ft_string("Bob"));
    test_assert_true(caster_names.get_error() == ER_SUCCESS,
        "ft_set should insert Bob without error");
    caster_names.insert(ft_string("Alice"));
    test_assert_true(caster_names.get_error() == ER_SUCCESS,
        "ft_set should insert Alice without error");
    result = ft_is_caster_name_present(&caster_names, "Alice");
    test_assert_true(result == 1,
        "ft_is_caster_name_present should detect Alice among multiple entries");
    result = ft_is_caster_name_present(&caster_names, "Bob");
    test_assert_true(result == 1,
        "ft_is_caster_name_present should detect Bob among multiple entries");
    result = ft_is_caster_name_present(&caster_names, "Charlie");
    test_assert_true(result == 0,
        "ft_is_caster_name_present should report zero when searching for absent names");
    return ;
}

static void test_check_player_entry_reports_existing_files()
{
    int result;

    remove_data_directory();
    create_data_file("existing_player");
    result = ft_check_player_entry("existing_player");
    test_assert_true(result == 1, "ft_check_player_entry should report existing files");
    remove_data_directory();
    return ;
}

static void test_check_player_entry_returns_zero_when_missing()
{
    int result;

    remove_data_directory();
    result = ft_check_player_entry("missing_player");
    test_assert_true(result == 0, "ft_check_player_entry should return zero when file is missing");
    return ;
}

static void test_get_pc_list_collects_player_files()
{
    ft_vector<ft_string>    player_list;
    size_t                  size;
    size_t                  index;
    int                     found_alice;
    int                     found_bob;

    remove_data_directory();
    create_data_file("PC--Alice");
    create_data_file("PC--Bob");
    create_data_file("NPC--Ignored");
    player_list = ft_get_pc_list();
    size = player_list.size();
    test_assert_true(size == 2, "ft_get_pc_list should return two player entries");
    index = 0;
    found_alice = 0;
    found_bob = 0;
    while (index < size)
    {
        if (player_list[index] == "Alice")
            found_alice = 1;
        if (player_list[index] == "Bob")
            found_bob = 1;
        index++;
    }
    test_assert_true(found_alice == 1, "ft_get_pc_list should include Alice");
    test_assert_true(found_bob == 1, "ft_get_pc_list should include Bob");
    remove_data_directory();
    return ;
}

static void test_get_pc_list_reports_when_directory_has_no_players()
{
    ft_vector<ft_string>    player_list;
    size_t                  size;
    const char              *capture_path;
    std::string             error_output;

    remove_data_directory();
    ensure_data_directory();
    capture_path = "tests_output/get_pc_list_empty.log";
    test_begin_error_capture(capture_path);
    player_list = ft_get_pc_list();
    test_end_error_capture();
    size = player_list.size();
    test_assert_true(size == 0, "ft_get_pc_list should return an empty list when no players exist");
    error_output = test_read_file_to_string(capture_path);
    test_assert_true(error_output == "Error: No player character found\n",
        "ft_get_pc_list should log an error when no player files are present");
    test_delete_file(capture_path);
    remove_data_directory();
    return ;
}

void    run_get_pc_list_tests()
{
    test_begin_suite("get_pc_list_tests");
    test_initialize_variables_zeros_target_data();
    test_is_caster_name_present_detects_existing_entries();
    test_is_caster_name_present_handles_multiple_entries();
    test_check_player_entry_reports_existing_files();
    test_check_player_entry_returns_zero_when_missing();
    test_get_pc_list_collects_player_files();
    test_get_pc_list_reports_when_directory_has_no_players();
    test_end_suite_success();
    return ;
}
