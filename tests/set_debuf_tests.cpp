#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"

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

    character.name = "Invalid";
    result = ft_check_stat(&character, "not_a_number", 0);
    test_assert_true(result == -99999, "ft_check_stat should report invalid strings with sentinel value");
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

    character.name = "Negative";
    character.debufs.blinded.duration = 7;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "-3";
    input[3] = ft_nullptr;
    ft_set_debuf_blinded(&character, input);
    test_assert_true(character.debufs.blinded.duration == 7, "ft_set_debuf_blinded should reject negative durations");
    return ;
}

static void test_set_debuf_blinded_rejects_excessive_duration()
{
    t_char          character = {};
    const char      *input[4];

    character.name = "Excess";
    character.debufs.blinded.duration = 9;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "51";
    input[3] = ft_nullptr;
    ft_set_debuf_blinded(&character, input);
    test_assert_true(character.debufs.blinded.duration == 9, "ft_set_debuf_blinded should reject durations above fifty");
    return ;
}

static void test_set_debuf_blinded_rejects_non_numeric_input()
{
    t_char          character = {};
    const char      *input[4];

    character.name = "NonNumeric";
    character.debufs.blinded.duration = 11;
    input[0] = "set";
    input[1] = "debuf";
    input[2] = "duration";
    input[3] = ft_nullptr;
    ft_set_debuf_blinded(&character, input);
    test_assert_true(character.debufs.blinded.duration == 11, "ft_set_debuf_blinded should ignore non numeric input");
    return ;
}

void    run_set_debuf_tests()
{
    test_check_stat_parses_positive_values();
    test_check_stat_honors_index_offset();
    test_check_stat_reports_invalid_strings();
    test_set_debuf_blinded_accepts_valid_duration();
    test_set_debuf_blinded_rejects_negative_duration();
    test_set_debuf_blinded_rejects_excessive_duration();
    test_set_debuf_blinded_rejects_non_numeric_input();
    return ;
}
