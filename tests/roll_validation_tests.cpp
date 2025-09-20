#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"

static void test_command_roll_validate_accepts_valid_expression()
{
    char expression[] = "2d6+3";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result == 0, "ft_command_roll_validate rejected a valid roll expression");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll_validate should set errno to success on valid expression");
    return ;
}

static void test_command_roll_validate_rejects_mismatched_parenthesis()
{
    char expression[] = "2d6+3)";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result != 0, "ft_command_roll_validate accepted an invalid roll expression");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL on invalid input");
    return ;
}

static void test_command_roll_validate_accepts_complex_expression()
{
    char expression[] = "(1d4+2)*(3d6-1)/2";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result == 0, "ft_command_roll_validate rejected a complex roll expression");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll_validate should set errno to success for complex expression");
    return ;
}

static void test_command_roll_validate_handles_null_expression()
{
    int result;

    result = ft_command_roll_validate(ft_nullptr);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression is null");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL when expression is null");
    return ;
}

static void test_command_roll_validate_rejects_empty_expression()
{
    char expression[] = "";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression is empty");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL for empty expression");
    return ;
}

static void test_command_roll_validate_rejects_trailing_operator()
{
    char expression[] = "2d6+";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression ends with an operator");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL when expression ends with operator");
    return ;
}

static void test_command_roll_validate_rejects_missing_dice_size()
{
    char expression[] = "10d";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when dice sides are missing");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL when dice sides are missing");
    return ;
}

static void test_command_roll_validate_rejects_invalid_characters()
{
    char expression[] = "2d6+x";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression contains invalid characters");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL for invalid characters");
    return ;
}

static void test_command_roll_validate_accepts_uppercase_dice_identifier()
{
    char expression[] = "2D6+3";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result == 0, "ft_command_roll_validate should accept uppercase dice identifiers");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll_validate should set errno to success for uppercase dice identifiers");
    return ;
}

static void test_command_roll_validate_rejects_whitespace()
{
    char expression[] = "2d6 + 3";
    int result;

    result = ft_command_roll_validate(expression);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression contains whitespace");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL when whitespace appears in expression");
    return ;
}

void run_roll_validation_tests()
{
    test_command_roll_validate_accepts_valid_expression();
    test_command_roll_validate_rejects_mismatched_parenthesis();
    test_command_roll_validate_accepts_complex_expression();
    test_command_roll_validate_handles_null_expression();
    test_command_roll_validate_rejects_empty_expression();
    test_command_roll_validate_rejects_trailing_operator();
    test_command_roll_validate_rejects_missing_dice_size();
    test_command_roll_validate_rejects_invalid_characters();
    test_command_roll_validate_accepts_uppercase_dice_identifier();
    test_command_roll_validate_rejects_whitespace();
    return ;
}
