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

static void test_command_roll_validate_handles_null_expression()
{
    int result;

    result = ft_command_roll_validate(ft_nullptr);
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression is null");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll_validate should set errno to FT_EINVAL when expression is null");
    return ;
}

void run_roll_validation_tests()
{
    test_command_roll_validate_accepts_valid_expression();
    test_command_roll_validate_rejects_mismatched_parenthesis();
    test_command_roll_validate_handles_null_expression();
    return ;
}
