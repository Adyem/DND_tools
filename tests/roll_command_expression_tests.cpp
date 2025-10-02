#include "test_support.hpp"
#include "test_groups.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"

static void test_command_roll_handles_parentheses_and_unary_minus()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1-(2d1-3)-(-4)");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should handle parentheses and unary minus");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for complex expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 6, "ft_command_roll should evaluate 1d1-(2d1-3)-(-4) to 6");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_handles_multiple_dice_segments()
{
    char *arguments[7];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1");
    arguments[2] = const_cast<char *>("+2d1");
    arguments[3] = const_cast<char *>("+3d1");
    arguments[4] = const_cast<char *>("-1d1");
    arguments[5] = const_cast<char *>("+4");
    arguments[6] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should evaluate expressions with multiple dice segments");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for multiple dice segments");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 9, "ft_command_roll should evaluate deterministic dice expression to 9");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_rejects_uppercase_dice_identifier()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1D1+2");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject uppercase dice identifiers");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for uppercase dice identifiers");
    return ;
}

static void test_command_roll_handles_leading_unary_minus_and_multiplication()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("0-1d1*3+4");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should evaluate expressions with leading subtraction");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for subtraction expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 1, "ft_command_roll should evaluate 0-1d1*3+4 to 1");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_supports_nested_parentheses_and_division()
{
    char *arguments[7];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("((1d1+2d1)");
    arguments[2] = const_cast<char *>("+");
    arguments[3] = const_cast<char *>("(3+4))");
    arguments[4] = const_cast<char *>("/1d1");
    arguments[5] = const_cast<char *>("-5");
    arguments[6] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should evaluate expressions with nested parentheses and division");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for nested parentheses expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 5, "ft_command_roll should evaluate ((1d1+2d1)+(3+4))/1d1-5 to 5");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_evaluates_operator_precedence()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1+2d1*3d1-4d1/1d1+5");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should respect operator precedence across dice expressions");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for precedence expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 8, "ft_command_roll should evaluate 1d1+2d1*3d1-4d1/1d1+5 to 8");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_handles_nested_negative_results()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("((1d1-5d1)+(2d1-10))-4");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should handle nested expressions producing negative results");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for nested negative expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == -16, "ft_command_roll should evaluate ((1d1-5d1)+(2d1-10))-4 to -16");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_evaluates_deeply_nested_mixed_operations()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("(((1d1+2d1)-(3d1-4))+((5+6d1)/1d1))-7");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should evaluate deeply nested expressions mixing all operators");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for deeply nested expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 8, "ft_command_roll should evaluate the nested mixed expression to 8");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_supports_leading_unary_parentheses_groups()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("-((1d1+2)-3d1)+(4d1-(5-6d1))");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should support leading unary minus applied to grouped expressions");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for leading unary parentheses groups");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 5, "ft_command_roll should evaluate -((1d1+2)-3d1)+(4d1-(5-6d1)) to 5");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_evaluates_large_dice_counts_and_mixed_groups()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("((10d1+20)-(5d1*2))+((3d1+4d1)/1d1)");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should evaluate expressions mixing large dice quantities and constants");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for large dice quantity expressions");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 27, "ft_command_roll should evaluate ((10d1+20)-(5d1*2))+((3d1+4d1)/1d1) to 27");
        cma_free(result);
    }
    return ;
}

void run_roll_command_expression_tests()
{
    test_command_roll_handles_parentheses_and_unary_minus();
    test_command_roll_handles_multiple_dice_segments();
    test_command_roll_rejects_uppercase_dice_identifier();
    test_command_roll_handles_leading_unary_minus_and_multiplication();
    test_command_roll_supports_nested_parentheses_and_division();
    test_command_roll_evaluates_operator_precedence();
    test_command_roll_handles_nested_negative_results();
    test_command_roll_evaluates_deeply_nested_mixed_operations();
    test_command_roll_supports_leading_unary_parentheses_groups();
    test_command_roll_evaluates_large_dice_counts_and_mixed_groups();
    return ;
}
