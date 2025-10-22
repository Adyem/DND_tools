#include "test_support.hpp"
#include "test_groups.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"
#include "../libft/Printf/printf.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void test_command_roll_rejects_null_argv()
{
    int *result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    file_path = "tests_output/roll_command_null_argv.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(ft_nullptr);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when argv is null");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when argv is null");
    error_output = test_read_file_to_string(file_path);
    expected_message = "401-Error: Roll command expression is missing\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log missing argument error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_requires_expression_argument()
{
    char *arguments[2];
    int *result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = ft_nullptr;
    file_path = "tests_output/roll_command_missing_expression.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should return null when expression argument is missing");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL when expression argument is missing");
    error_output = test_read_file_to_string(file_path);
    expected_message = "401-Error: Roll command expression is missing\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log missing expression error message");
    test_delete_file(file_path);
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

static void test_command_roll_concatenates_tokenized_parentheses_expression()
{
    char *arguments[12];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("(");
    arguments[2] = const_cast<char *>("1d1");
    arguments[3] = const_cast<char *>("+");
    arguments[4] = const_cast<char *>("2d1");
    arguments[5] = const_cast<char *>(")");
    arguments[6] = const_cast<char *>("+");
    arguments[7] = const_cast<char *>("(");
    arguments[8] = const_cast<char *>("3d1");
    arguments[9] = const_cast<char *>("-4d1");
    arguments[10] = const_cast<char *>(")");
    arguments[11] = ft_nullptr;
    result = ft_command_roll(arguments);
    char message[128];

    pf_snprintf(message, sizeof(message),
        "ft_command_roll should join tokenized parentheses expressions correctly (errno %d)",
        ft_errno);
    test_assert_true(result != ft_nullptr, message);
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should succeed when tokens form a valid expression");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 2, "ft_command_roll should evaluate (1d1+2d1)+(3d1-4d1) to 2");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_concatenates_fragmented_tokens_into_expression()
{
    char *arguments[14];
    int *result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("(");
    arguments[2] = const_cast<char *>("1");
    arguments[3] = const_cast<char *>("d1");
    arguments[4] = const_cast<char *>("+2");
    arguments[5] = const_cast<char *>("d1)");
    arguments[6] = const_cast<char *>("*");
    arguments[7] = const_cast<char *>("3");
    arguments[8] = const_cast<char *>("d1");
    arguments[9] = const_cast<char *>("+");
    arguments[10] = const_cast<char *>("5");
    arguments[11] = const_cast<char *>("-");
    arguments[12] = const_cast<char *>("1");
    arguments[13] = ft_nullptr;
    result = ft_command_roll(arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should concatenate fragmented tokens into a full expression");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should succeed when fragmented tokens form a valid expression");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 13, "ft_command_roll should evaluate (1d1+2d1)*3d1+5-1 to 13");
        cma_free(result);
    }
    return ;
}

static void test_command_roll_resets_errno_after_error()
{
    char *invalid_arguments[3];
    char *valid_arguments[3];
    int *result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    invalid_arguments[0] = const_cast<char *>("roll");
    invalid_arguments[1] = const_cast<char *>("1d1+");
    invalid_arguments[2] = ft_nullptr;
    file_path = "tests_output/roll_command_resets_errno_error.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll(invalid_arguments);
    test_end_error_capture();
    test_assert_true(result == ft_nullptr, "ft_command_roll should fail when expression terminates with an operator");
    test_assert_true(ft_errno == FT_EINVAL, "ft_command_roll should set errno to FT_EINVAL after an invalid expression");
    error_output = test_read_file_to_string(file_path);
    expected_message = "403-Error: Failed to evaluate roll expression: 1d1+\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll should log invalid expression error message");
    test_delete_file(file_path);
    valid_arguments[0] = const_cast<char *>("roll");
    valid_arguments[1] = const_cast<char *>("1d1+5");
    valid_arguments[2] = ft_nullptr;
    result = ft_command_roll(valid_arguments);
    test_assert_true(result != ft_nullptr, "ft_command_roll should succeed immediately after a failure");
    test_assert_true(ft_errno == ER_SUCCESS, "ft_command_roll should reset errno to success for a valid expression");
    if (result != ft_nullptr)
    {
        test_assert_true(*result == 6, "ft_command_roll should evaluate 1d1+5 to 6 after resetting errno");
        cma_free(result);
    }
    return ;
}

void run_roll_command_argument_tests()
{
    test_begin_suite("roll_command_argument_tests");
    test_command_roll_rejects_null_argv();
    test_command_roll_requires_expression_argument();
    test_command_roll_concatenates_arguments_and_rolls_expression();
    test_command_roll_concatenates_tokenized_parentheses_expression();
    test_command_roll_concatenates_fragmented_tokens_into_expression();
    test_command_roll_resets_errno_after_error();
    test_end_suite_success();
    return ;
}
