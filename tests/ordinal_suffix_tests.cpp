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
    suffix = ft_ordinal_suffix(21);
    test_assert_true(ft_strcmp(suffix, "nth") == 0, "ordinal suffix for numbers above table should be nth");
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

void run_ordinal_suffix_tests()
{
    test_ordinal_suffix_values();
    test_ordinal_suffix_handles_teens();
    return ;
}
