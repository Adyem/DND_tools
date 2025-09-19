#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"

static void test_strtrim_prefix_removes_prefix()
{
    char *result;

    result = ft_strtrim_prefix("prefix_value", "prefix_");
    test_assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null for valid prefix");
    test_assert_true(ft_strcmp(result, "value") == 0, "ft_strtrim_prefix did not remove prefix");
    cma_free(result);
    return ;
}

static void test_strtrim_prefix_without_match_returns_copy()
{
    char *result;

    result = ft_strtrim_prefix("value", "prefix_");
    test_assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null for missing prefix");
    test_assert_true(ft_strcmp(result, "value") == 0, "ft_strtrim_prefix changed string without prefix match");
    cma_free(result);
    return ;
}

static void test_strtrim_prefix_handles_null_input()
{
    char *result;

    result = ft_strtrim_prefix(ft_nullptr, "prefix_");
    test_assert_true(result == ft_nullptr, "ft_strtrim_prefix should return null when source is null");
    return ;
}

static void test_strtrim_prefix_returns_empty_string_for_full_match()
{
    char *result;

    result = ft_strtrim_prefix("prefix_", "prefix_");
    test_assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null for full match");
    test_assert_true(ft_strcmp(result, "") == 0, "ft_strtrim_prefix should return empty string when prefix consumes all characters");
    cma_free(result);
    return ;
}

void run_string_prefix_tests()
{
    test_strtrim_prefix_removes_prefix();
    test_strtrim_prefix_without_match_returns_copy();
    test_strtrim_prefix_handles_null_input();
    test_strtrim_prefix_returns_empty_string_for_full_match();
    return ;
}
