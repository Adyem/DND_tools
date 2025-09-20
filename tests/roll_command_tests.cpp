#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"
#include <cstdio>

static void test_command_roll_rejects_null_argv()
{
    int *result;

    result = ft_command_roll(ft_nullptr);
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when argv is null");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when argv is null");
    return ;
}

static void test_command_roll_requires_expression_argument()
{
    char *arguments[2];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when expression argument is missing");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when expression argument is missing");
    return ;
}

static void test_command_roll_concatenates_arguments_and_rolls_expression()
{
    char *arguments[4];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1");
    arguments[2] = const_cast<char *>("+3");
    arguments[3] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should return result pointer for valid expression");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should set errno to success for valid expression");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 4, "ft_command_roll should evaluate 1d1+3 to deterministic value 4");
        cma_free(result);
    }
    return ;
}

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

void run_roll_command_tests()
{
    test_command_roll_rejects_null_argv();
    test_command_roll_requires_expression_argument();
    test_command_roll_concatenates_arguments_and_rolls_expression();
    test_command_roll_rejects_invalid_expression();
    return ;
}
