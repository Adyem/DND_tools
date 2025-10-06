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

static void test_strtrim_prefix_handles_null_prefix()
{
    char *result;

    result = ft_strtrim_prefix("value", ft_nullptr);
    test_assert_true(result == ft_nullptr, "ft_strtrim_prefix should return null when prefix is null");
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

static void test_strtrim_prefix_handles_empty_prefix()
{
    const char  *source;
    const void  *source_ptr;
    char        *result;

    source = "value";
    source_ptr = static_cast<const void *>(source);
    result = ft_strtrim_prefix(source, "");
    test_assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null for empty prefix");
    test_assert_true(ft_strcmp(result, source) == 0, "ft_strtrim_prefix should return copy when prefix is empty");
    test_assert_true(static_cast<const void *>(result) != source_ptr, "ft_strtrim_prefix should allocate new string for empty prefix");
    cma_free(result);
    return ;
}

static void test_strtrim_prefix_only_removes_leading_match()
{
    const char  *source;
    const void  *source_ptr;
    char        *result;

    source = "value_prefix";
    source_ptr = static_cast<const void *>(source);
    result = ft_strtrim_prefix(source, "prefix");
    test_assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null when prefix occurs later in string");
    test_assert_true(ft_strcmp(result, source) == 0, "ft_strtrim_prefix should only trim prefix at the start of the string");
    test_assert_true(static_cast<const void *>(result) != source_ptr, "ft_strtrim_prefix should allocate a new copy when prefix does not match at start");
    cma_free(result);
    return ;
}

static void test_strtrim_prefix_with_longer_prefix_returns_copy()
{
    const char *source;
    char       *result;

    source = "short";
    result = ft_strtrim_prefix(source, "longer_prefix");
    test_assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null when prefix is longer than source");
    test_assert_true(ft_strcmp(result, source) == 0, "ft_strtrim_prefix should not change string when prefix is longer than source");
    cma_free(result);
    return ;
}

void run_string_prefix_tests()
{
    test_begin_suite("string_prefix_tests");
    test_strtrim_prefix_removes_prefix();
    test_strtrim_prefix_without_match_returns_copy();
    test_strtrim_prefix_handles_null_input();
    test_strtrim_prefix_handles_null_prefix();
    test_strtrim_prefix_returns_empty_string_for_full_match();
    test_strtrim_prefix_handles_empty_prefix();
    test_strtrim_prefix_only_removes_leading_match();
    test_strtrim_prefix_with_longer_prefix_returns_copy();
    test_end_suite_success();
    return ;
}
