#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"
#include "../libft/Printf/printf.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

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
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    file_path = "tests_output/roll_validate_mismatched_parenthesis.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(expression);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate accepted an invalid roll expression");
    char errno_message[128];

    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL on invalid input (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "405-Error: Roll validation failed for expression: 2d6+3)\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log mismatched parenthesis error message");
    test_delete_file(file_path);
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
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;
    char        errno_message[128];

    file_path = "tests_output/roll_validate_null_expression.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(ft_nullptr);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression is null");
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL when expression is null (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "404-Error: Roll validation expression is missing\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log null expression error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_validate_rejects_empty_expression()
{
    char expression[] = "";
    int result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;
    char        errno_message[128];

    file_path = "tests_output/roll_validate_empty_expression.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(expression);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression is empty");
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL for empty expression (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "405-Error: Roll validation failed for expression: \n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log empty expression error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_validate_rejects_trailing_operator()
{
    char expression[] = "2d6+";
    int result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;
    char        errno_message[128];

    file_path = "tests_output/roll_validate_trailing_operator.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(expression);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression ends with an operator");
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL when expression ends with operator (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "405-Error: Roll validation failed for expression: 2d6+\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log trailing operator error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_validate_rejects_missing_dice_size()
{
    char expression[] = "10d";
    int result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;
    char        errno_message[128];

    file_path = "tests_output/roll_validate_missing_dice_size.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(expression);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate should fail when dice sides are missing");
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL when dice sides are missing (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "405-Error: Roll validation failed for expression: 10d\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log missing dice size error message");
    test_delete_file(file_path);
    return ;
}

static void test_command_roll_validate_rejects_invalid_characters()
{
    char expression[] = "2d6+x";
    int result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;
    char        errno_message[128];

    file_path = "tests_output/roll_validate_invalid_characters.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(expression);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression contains invalid characters");
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL for invalid characters (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "405-Error: Roll validation failed for expression: 2d6+x\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log invalid character error message");
    test_delete_file(file_path);
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
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;
    char        errno_message[128];

    file_path = "tests_output/roll_validate_whitespace.log";
    test_begin_error_capture(file_path);
    result = ft_command_roll_validate(expression);
    test_end_error_capture();
    test_assert_true(result != 0, "ft_command_roll_validate should fail when expression contains whitespace");
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_command_roll_validate should set errno to FT_EINVAL when whitespace appears in expression (errno %d)",
        ft_errno);
    test_assert_true(ft_errno == FT_EINVAL, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "405-Error: Roll validation failed for expression: 2d6 + 3\n";
    test_assert_true(error_output == expected_message,
        "ft_command_roll_validate should log whitespace error message");
    test_delete_file(file_path);
    return ;
}

void run_roll_validation_tests()
{
    test_begin_suite("roll_validation_tests");
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
    test_end_suite_success();
    return ;
}
