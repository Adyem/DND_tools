#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"

static void test_ordinal_suffix_values()
{
    const char *suffix;

    suffix = ft_ordinal_suffix(1);
    test_assert_true(ft_strcmp(suffix, "first") == 0, "ordinal suffix for 1 should be first");
    suffix = ft_ordinal_suffix(2);
    test_assert_true(ft_strcmp(suffix, "second") == 0, "ordinal suffix for 2 should be second");
    suffix = ft_ordinal_suffix(3);
    test_assert_true(ft_strcmp(suffix, "third") == 0, "ordinal suffix for 3 should be third");
    suffix = ft_ordinal_suffix(20);
    test_assert_true(ft_strcmp(suffix, "twentieth") == 0, "ordinal suffix for 20 should be twentieth");
    suffix = ft_ordinal_suffix(21);
    test_assert_true(ft_strcmp(suffix, "nth") == 0, "ordinal suffix for numbers above table should be nth");
    return ;
}

static void test_ordinal_suffix_table_matches_expected()
{
    const char  *expected_suffixes[20] = {
        "first", "second", "third", "fourth", "fifth",
        "sixth", "seventh", "eighth", "ninth", "tenth",
        "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth",
        "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth"
    };
    int         index;

    index = 0;
    while (index < 20)
    {
        const char *suffix;

        suffix = ft_ordinal_suffix(index + 1);
        test_assert_true(ft_strcmp(suffix, expected_suffixes[index]) == 0, "ordinal suffix table entry mismatch");
        index++;
    }
    return ;
}

static void test_ordinal_suffix_handles_teens()
{
    const char *suffix;

    suffix = ft_ordinal_suffix(11);
    test_assert_true(ft_strcmp(suffix, "eleventh") == 0, "ordinal suffix for 11 should be eleventh");
    suffix = ft_ordinal_suffix(12);
    test_assert_true(ft_strcmp(suffix, "twelfth") == 0, "ordinal suffix for 12 should be twelfth");
    suffix = ft_ordinal_suffix(13);
    test_assert_true(ft_strcmp(suffix, "thirteenth") == 0, "ordinal suffix for 13 should be thirteenth");
    return ;
}

static void test_ordinal_suffix_handles_non_positive_numbers()
{
    const char *suffix;

    suffix = ft_ordinal_suffix(0);
    test_assert_true(ft_strcmp(suffix, "nth") == 0, "ordinal suffix for 0 should be nth");
    suffix = ft_ordinal_suffix(-5);
    test_assert_true(ft_strcmp(suffix, "nth") == 0, "ordinal suffix for negative numbers should be nth");
    return ;
}

void run_ordinal_suffix_tests()
{
    test_ordinal_suffix_values();
    test_ordinal_suffix_table_matches_expected();
    test_ordinal_suffix_handles_teens();
    test_ordinal_suffix_handles_non_positive_numbers();
    return ;
}
