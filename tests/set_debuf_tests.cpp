#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include <string>

static void test_check_stat_parses_positive_values()
{
    t_char  character = {};
    int     result;

    character.name = "Test Character";
    result = ft_check_stat(&character, "27", 0);
    test_assert_true(result == 27, "ft_check_stat should parse positive integers");
    return ;
}

static void test_check_stat_honors_index_offset()
{
    t_char      character = {};
    const char  *stat;
    int         result;

    character.name = "Indexed";
    stat = "hp=12";
    result = ft_check_stat(&character, stat, 3);
    test_assert_true(result == 12, "ft_check_stat should honor index offset when parsing");
    return ;
}

static void test_check_stat_reports_invalid_strings()
{
    t_char  character = {};
    int     result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    character.name = "Invalid";
    file_path = "tests_output/set_debuf_check_stat_invalid.log";
    test_begin_error_capture(file_path);
    result = ft_check_stat(&character, "not_a_number", 0);
    test_end_error_capture();
    test_assert_true(result == -99999, "ft_check_stat should report invalid strings with sentinel value");
    error_output = test_read_file_to_string(file_path);
    expected_message = "2-Something is wrong with the save file from Invalid at the line: not_a_number\n";
    test_assert_true(error_output == expected_message,
        "ft_check_stat should log error details for invalid stat strings");
    test_delete_file(file_path);
    return ;
}

static void test_set_debuf_blinded_accepts_valid_duration()
{
    t_char          character = {};
    const char      *input[4];

    character.name = "Duration";
    character.debufs.blinded.duration = 0;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "15";
    input[3] = ft_nullptr;
    ft_set_debuf_blinded(&character, input);
    test_assert_true(character.debufs.blinded.duration == 15, "ft_set_debuf_blinded should apply valid duration values");
    return ;
}

static void test_set_debuf_blinded_rejects_negative_duration()
{
    t_char          character = {};
    const char      *input[4];
    const char      *file_path;
    std::string     error_output;
    const char      *expected_message;

    character.name = "Negative";
    character.debufs.blinded.duration = 7;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "-3";
    input[3] = ft_nullptr;
    file_path = "tests_output/set_debuf_blinded_negative.log";
    test_begin_error_capture(file_path);
    ft_set_debuf_blinded(&character, input);
    test_end_error_capture();
    test_assert_true(character.debufs.blinded.duration == 7, "ft_set_debuf_blinded should reject negative durations");
    error_output = test_read_file_to_string(file_path);
    expected_message = "230-Error blinded value out of bounds or not found\n";
    test_assert_true(error_output == expected_message,
        "ft_set_debuf_blinded should log range errors when rejecting negative durations");
    test_delete_file(file_path);
    return ;
}

static void test_set_debuf_blinded_rejects_excessive_duration()
{
    t_char          character = {};
    const char      *input[4];
    const char      *file_path;
    std::string     error_output;
    const char      *expected_message;

    character.name = "Excess";
    character.debufs.blinded.duration = 9;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "51";
    input[3] = ft_nullptr;
    file_path = "tests_output/set_debuf_blinded_excessive.log";
    test_begin_error_capture(file_path);
    ft_set_debuf_blinded(&character, input);
    test_end_error_capture();
    test_assert_true(character.debufs.blinded.duration == 9, "ft_set_debuf_blinded should reject durations above fifty");
    error_output = test_read_file_to_string(file_path);
    expected_message = "230-Error blinded value out of bounds or not found\n";
    test_assert_true(error_output == expected_message,
        "ft_set_debuf_blinded should log out-of-range errors for durations above fifty");
    test_delete_file(file_path);
    return ;
}

static void test_set_debuf_blinded_rejects_non_numeric_input()
{
    t_char          character = {};
    const char      *input[4];
    const char      *file_path;
    std::string     error_output;
    const char      *expected_message;

    character.name = "NonNumeric";
    character.debufs.blinded.duration = 11;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "duration";
    input[3] = ft_nullptr;
    file_path = "tests_output/set_debuf_blinded_non_numeric.log";
    test_begin_error_capture(file_path);
    ft_set_debuf_blinded(&character, input);
    test_end_error_capture();
    test_assert_true(character.debufs.blinded.duration == 11, "ft_set_debuf_blinded should ignore non numeric input");
    error_output = test_read_file_to_string(file_path);
    expected_message = "2-Something is wrong with the save file from NonNumeric at the line: duration\n"
        "230-Error blinded value out of bounds or not found\n";
    test_assert_true(error_output == expected_message,
        "ft_set_debuf_blinded should log validation errors when input is not numeric");
    test_delete_file(file_path);
    return ;
}

void    run_set_debuf_tests()
{
    test_begin_suite("set_debuf_tests");
    test_check_stat_parses_positive_values();
    test_check_stat_honors_index_offset();
    test_check_stat_reports_invalid_strings();
    test_set_debuf_blinded_accepts_valid_duration();
    test_set_debuf_blinded_rejects_negative_duration();
    test_set_debuf_blinded_rejects_excessive_duration();
    test_set_debuf_blinded_rejects_non_numeric_input();
    test_end_suite_success();
    return ;
}
