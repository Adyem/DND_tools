#include "test_support.hpp"
#include "../dnd_tools.hpp"
#include "../libft/Modules/CPP_class/class_nullptr.hpp"
#include "../libft/Modules/CPP_class/class_file.hpp"
#include "../libft/Modules/CPP_class/class_string.hpp"
#include "../libft/Modules/Errno/errno.hpp"
#include "../libft/Modules/File/file_utils.hpp"
#include "../libft/Modules/Basic/basic.hpp"

void    ft_open_all_files(t_name *name)
{
    (void)name;
    return ;
}

void    ft_turn_next(t_name *name)
{
    (void)name;
    return ;
}

void    ft_test(t_name *name)
{
    (void)name;
    return ;
}

void    ft_print_help(void)
{
    return ;
}

void    ft_encounter(int argument_count, const char **argument_vector, t_name *name)
{
    (void)argument_count;
    (void)argument_vector;
    (void)name;
    return ;
}

static void command_builtin_stub_ensure_data_directory(void)
{
    test_create_directory("data");
    return ;
}

void    ft_player(const char **input)
{
    ft_string   path;
    ft_file     file;

    if (!input || !input[0])
        return ;
    if (ft_strcmp(input[0], "add") != 0 || !input[2])
        return ;
    command_builtin_stub_ensure_data_directory();
    if (FT_ERR_SUCCESS != FT_ERR_SUCCESS)
        return ;
    path = ft_string("data/PC--");
    if (path.get_error() != FT_ERR_SUCCESS)
        return ;
    path.append(input[2]);
    if (path.get_error() != FT_ERR_SUCCESS)
        return ;
    file = ft_file(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file.get_error() != FT_ERR_SUCCESS)
        return ;
    file.write("stub");
    if (file.get_error() == FT_ERR_SUCCESS)
    return ;
}
