#include "test_support.hpp"
#include "test_groups.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"
#include <cstdio>

static void test_command_roll_rejects_invalid_expression()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("2d6+");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when expression is invalid");
    char message[128];

    std::snprintf(message, sizeof(message), "ft_command_roll invalid expression errno %d", ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, message);
    return ;
}

static void test_command_roll_rejects_whitespace_in_expression()
{
    char *arguments[4];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1");
    arguments[2] = const_cast<char *>("+2 ");
    arguments[3] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when expression contains whitespace");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when whitespace is present");
    return ;
}

static void test_command_roll_detects_division_by_zero()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1/0");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject division by zero expressions");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for division by zero");
    return ;
}

static void test_command_roll_rejects_unbalanced_parentheses()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("(1d1+2))");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject expressions with unbalanced parentheses");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for unbalanced parentheses");
    return ;
}

static void test_command_roll_rejects_invalid_character()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1+2#3");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject expressions containing invalid characters");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for invalid characters");
    return ;
}

static void test_command_roll_detects_overflow_result()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("2147483647+1");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject expressions whose results overflow");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when overflow is detected");
    return ;
}

static void test_command_roll_handles_zero_dice_quantity()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("0d6+1");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should treat zero-dice segments as contributing zero");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success when zero dice are requested");
    if (result != ft_nullptr)
    {
        cma_free(result);
    }
    return ;
}

static void test_command_roll_handles_zero_sided_die()
{
    char *arguments[3];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d0+2");
    arguments[2] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should handle zero-sided dice as zero contribution");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success when zero-sided dice are used");
    if (result != ft_nullptr)
    {
        cma_free(result);
    }
    return ;
}

void run_roll_command_error_tests()
{
    test_command_roll_rejects_invalid_expression();
    test_command_roll_rejects_whitespace_in_expression();
    test_command_roll_detects_division_by_zero();
    test_command_roll_rejects_unbalanced_parentheses();
    test_command_roll_rejects_invalid_character();
    test_command_roll_detects_overflow_result();
    test_command_roll_handles_zero_dice_quantity();
    test_command_roll_handles_zero_sided_die();
    return ;
}
