#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include <cstdio>
#include <cstdlib>

static void assert_true(int condition, const char *message)
{
    if (!condition)
    {
        std::fprintf(stderr, "Test failed: %s\n", message);
        cma_cleanup();
        std::exit(1);
    }
    return ;
}

static void test_strtrim_prefix_removes_prefix()
{
    char *result;

    result = ft_strtrim_prefix("prefix_value", "prefix_");
    assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null for valid prefix");
    assert_true(ft_strcmp(result, "value") == 0, "ft_strtrim_prefix did not remove prefix");
    cma_free(result);
    return ;
}

static void test_strtrim_prefix_without_match_returns_copy()
{
    char *result;

    result = ft_strtrim_prefix("value", "prefix_");
    assert_true(result != ft_nullptr, "ft_strtrim_prefix returned null for missing prefix");
    assert_true(ft_strcmp(result, "value") == 0, "ft_strtrim_prefix changed string without prefix match");
    cma_free(result);
    return ;
}

static void test_strtrim_prefix_handles_null_input()
{
    char *result;

    result = ft_strtrim_prefix(ft_nullptr, "prefix_");
    assert_true(result == ft_nullptr, "ft_strtrim_prefix should return null when source is null");
    return ;
}

static void test_ordinal_suffix_values()
{
    const char *suffix;

    suffix = ft_ordinal_suffix(1);
    assert_true(ft_strcmp(suffix, "first") == 0, "ordinal suffix for 1 should be first");
    suffix = ft_ordinal_suffix(2);
    assert_true(ft_strcmp(suffix, "second") == 0, "ordinal suffix for 2 should be second");
    suffix = ft_ordinal_suffix(3);
    assert_true(ft_strcmp(suffix, "third") == 0, "ordinal suffix for 3 should be third");
    suffix = ft_ordinal_suffix(21);
    assert_true(ft_strcmp(suffix, "nth") == 0, "ordinal suffix for numbers above table should be nth");
    return ;
}

static void test_command_roll_validate_accepts_valid_expression()
{
    char expression[] = "2d6+3";
    int result;

    result = ft_command_roll_validate(expression);
    assert_true(result == 0, "ft_command_roll_validate rejected a valid roll expression");
    return ;
}

static void test_command_roll_validate_rejects_mismatched_parenthesis()
{
    char expression[] = "2d6+3)";
    int result;

    result = ft_command_roll_validate(expression);
    assert_true(result != 0, "ft_command_roll_validate accepted an invalid roll expression");
    return ;
}

int main()
{
    test_strtrim_prefix_removes_prefix();
    test_strtrim_prefix_without_match_returns_copy();
    test_strtrim_prefix_handles_null_input();
    test_ordinal_suffix_values();
    test_command_roll_validate_accepts_valid_expression();
    test_command_roll_validate_rejects_mismatched_parenthesis();
    cma_cleanup();
    std::printf("All tests passed.\n");
    return (0);
}
