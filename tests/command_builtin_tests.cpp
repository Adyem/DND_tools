#include "test_groups.hpp"
#include "test_support.hpp"
#include "../command_builtins.hpp"
#include "../libft/CPP_class/class_nullptr.hpp"
#include "../libft/Errno/errno.hpp"

static void test_dispatch_builtin_returns_not_found_for_null_input()
{
    int result;

    ft_errno = FT_ERR_IO;
    result = ft_dispatch_builtin_command(ft_nullptr, 0, ft_nullptr);
    test_assert_true(result == FT_BUILTIN_NOT_FOUND,
        "ft_dispatch_builtin_command should return not found when the input array is null");
    test_assert_true(ft_errno == FT_ERR_IO,
        "ft_dispatch_builtin_command should leave ft_errno unchanged when the input array is null");
    return ;
}

static void test_dispatch_builtin_exit_command_signals_exit()
{
    char *arguments[2];
    int   result;

    arguments[0] = const_cast<char *>("exit");
    arguments[1] = ft_nullptr;
    ft_errno = FT_ERR_IO;
    result = ft_dispatch_builtin_command(arguments, 1, ft_nullptr);
    test_assert_true(result == FT_BUILTIN_EXIT,
        "ft_dispatch_builtin_command should signal exit when the exit command is provided");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_dispatch_builtin_command should reset ft_errno to success after handling the exit command");
    return ;
}

static void test_dispatch_builtin_roll_command_executes_roll()
{
    char *arguments[3];
    int   result;

    arguments[0] = const_cast<char *>("roll");
    arguments[1] = const_cast<char *>("1d1");
    arguments[2] = ft_nullptr;
    ft_errno = FT_ERR_IO;
    result = ft_dispatch_builtin_command(arguments, 2, ft_nullptr);
    test_assert_true(result == FT_BUILTIN_HANDLED,
        "ft_dispatch_builtin_command should handle the roll command when provided with an expression");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_dispatch_builtin_command should reset ft_errno after a successful roll command");
    return ;
}

static void test_dispatch_builtin_add_player_creates_player_file()
{
    char    *arguments[4];
    int     result;

    arguments[0] = const_cast<char *>("add");
    arguments[1] = const_cast<char *>("player");
    arguments[2] = const_cast<char *>("BuiltinCommandTest");
    arguments[3] = ft_nullptr;
    test_create_directory("data");
    test_remove_path("data/PC--BuiltinCommandTest");
    ft_errno = FT_ERR_IO;
    result = ft_dispatch_builtin_command(arguments, 3, ft_nullptr);
    test_assert_true(result == FT_BUILTIN_HANDLED,
        "ft_dispatch_builtin_command should handle the add player command when valid arguments are provided");
    test_assert_true(ft_errno == ER_SUCCESS,
        "ft_dispatch_builtin_command should reset ft_errno after adding a player through the builtin map");
    test_assert_true(test_path_exists("data/PC--BuiltinCommandTest") == 1,
        "ft_dispatch_builtin_command should create the player file when the add player command succeeds");
    test_remove_path("data/PC--BuiltinCommandTest");
    return ;
}

void    run_command_builtin_tests()
{
    test_begin_suite("command_builtin_tests");
    test_dispatch_builtin_returns_not_found_for_null_input();
    test_dispatch_builtin_exit_command_signals_exit();
    test_dispatch_builtin_roll_command_executes_roll();
    test_dispatch_builtin_add_player_creates_player_file();
    test_end_suite_success();
    return ;
}
