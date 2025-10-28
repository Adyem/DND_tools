#include "test_groups.hpp"
#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Errno/errno.hpp"
#include "../libft/RNG/rng.hpp"
#include "../libft/Printf/printf.hpp"
#include "../libft/CPP_class/class_string_class.hpp"

static void test_dice_roll_rejects_invalid_parameters()
{
    int         result;
    const char  *file_path;
    ft_string   error_output;
    const char  *expected_message;

    file_path = "tests_output/dice_roll_invalid_parameters.log";
    test_begin_error_capture(file_path);
    result = ft_dice_roll(0, 6);
    test_end_error_capture();
    test_assert_true(result == -1,
        "ft_dice_roll should return -1 when the number of dice is invalid");
    char errno_message[128];
    int  error_code;

    error_code = ft_errno;
    pf_snprintf(errno_message, sizeof(errno_message),
        "ft_dice_roll should set errno to FT_ERR_INVALID_ARGUMENT for invalid dice parameters (errno %d)",
        error_code);
    test_assert_true(error_code == FT_ERR_INVALID_ARGUMENT, errno_message);
    error_output = test_read_file_to_string(file_path);
    expected_message = "";
    test_assert_true(error_output == expected_message,
        "ft_dice_roll should not emit stderr output for invalid parameters");
    test_delete_file(file_path);
    return ;
}

static void test_dice_roll_returns_values_within_expected_range()
{
    int result;
    int iteration;
    int minimum_observed;
    int maximum_observed;

    iteration = 0;
    minimum_observed = 1000;
    maximum_observed = -1;
    while (iteration < 32)
    {
        result = ft_dice_roll(3, 6);
        test_assert_true(ft_errno == ER_SUCCESS,
            "ft_dice_roll should set errno to success for valid rolls");
        test_assert_true(result >= 3,
            "ft_dice_roll should never produce a value below the minimum sum");
        test_assert_true(result <= 18,
            "ft_dice_roll should never produce a value above the maximum sum");
        if (result < minimum_observed)
            minimum_observed = result;
        if (result > maximum_observed)
            maximum_observed = result;
        iteration++;
    }
    test_assert_true(minimum_observed >= 3,
        "ft_dice_roll should not record results below the minimum bound");
    test_assert_true(maximum_observed <= 18,
        "ft_dice_roll should not record results above the maximum bound");
    return ;
}

static void test_dice_roll_handles_zero_dice_and_faces()
{
    int result;

    result = ft_dice_roll(0, 0);
    test_assert_true(result == 0,
        "ft_dice_roll should return zero when both dice and faces are zero");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_dice_roll should set errno to success when both parameters are zero");
    return ;
}

void run_dice_roll_tests()
{
    test_begin_suite("dice_roll_tests");
    test_dice_roll_rejects_invalid_parameters();
    test_dice_roll_returns_values_within_expected_range();
    test_dice_roll_handles_zero_dice_and_faces();
    test_end_suite_success();
    return ;
}
