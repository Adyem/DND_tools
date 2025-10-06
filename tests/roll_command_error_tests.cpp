#include "test_support.hpp"
#include "test_groups.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"
#include <cstdio>
#include <string>

static void test_command_roll_rejects_invalid_expression()
{
    char *arguments[3];
    int *result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("2d6+");
    arguments[2] = ft_nullptr;
    file_path = "tests_output/roll_command_invalid_expression.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when expression is invalid");
    char message[128];

    std::snprintf(message, sizeof(message), "ft_command_roll invalid expression errno %d", ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: 2d6+\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log invalid expression message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_rejects_whitespace_in_expression()
{
    char *arguments[4];
    int *result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1");
    arguments[2] = const_cast<char *>("+2 ");
    arguments[3] = ft_nullptr;
    file_path = "tests_output/roll_command_whitespace_expression.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when expression contains whitespace");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when whitespace is present");
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: 1d1+2 \n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log whitespace expression error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_detects_division_by_zero()
{
    char *arguments[3];
    int *result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1/0");
    arguments[2] = ft_nullptr;
    file_path = "tests_output/roll_command_division_by_zero.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject division by zero expressions");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for division by zero");
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: 1d1/0\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log division by zero error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_rejects_unbalanced_parentheses()
{
    char *arguments[3];
    int *result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("(1d1+2))");
    arguments[2] = ft_nullptr;
    file_path = "tests_output/roll_command_unbalanced_parentheses.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject expressions with unbalanced parentheses");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for unbalanced parentheses");
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: (1d1+2))\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log unbalanced parentheses error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_rejects_invalid_character()
{
    char *arguments[3];
    int *result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1+2#3");
    arguments[2] = ft_nullptr;
    file_path = "tests_output/roll_command_invalid_character.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject expressions containing invalid characters");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL for invalid characters");
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: 1d1+2#3\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log invalid character error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_detects_overflow_result()
{
    char *arguments[3];
    int *result;
    const char  *file_path;
    std::string error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("2147483647+1");
    arguments[2] = ft_nullptr;
    file_path = "tests_output/roll_command_overflow_expression.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should reject expressions whose results overflow");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when overflow is detected");
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: 2147483647+1\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log overflow error message");
    test_delete_file(file_path);
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
    test_begin_suite("roll_command_error_tests");
    test_command_roll_rejects_invalid_expression();
    test_command_roll_rejects_whitespace_in_expression();
    test_command_roll_detects_division_by_zero();
    test_command_roll_rejects_unbalanced_parentheses();
    test_command_roll_rejects_invalid_character();
    test_command_roll_detects_overflow_result();
    test_command_roll_handles_zero_dice_quantity();
    test_command_roll_handles_zero_sided_die();
    test_end_suite_success();
    return ;
}
