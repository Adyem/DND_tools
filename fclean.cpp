#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/File/file_utils.hpp"
#include "libft/File/open_dir.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/System_utils/system_utils.hpp"
#include "libft/Compatebility/compatebility_internal.hpp"
#if defined(_WIN32)
# include <windows.h>
#endif

static int ft_should_skip_entry(const char *name, int remove_all)
{
    if (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
        return (1);
    if (remove_all != 0)
        return (0);
    if (ft_strncmp(name, "data--", 6) == 0)
        return (1);
    if (ft_strncmp(name, "pc--", 4) == 0)
        return (1);
    if (ft_strncmp(name, "PC--", 4) == 0)
        return (1);
    return (0);
}

#if defined(_WIN32)
static int ft_handle_remove_error(void)
{
    DWORD last_error;

    last_error = GetLastError();
    if (last_error != 0)
        ft_errno = static_cast<int>(last_error) + ERRNO_OFFSET;
    else
        ft_errno = FT_ERR_INVALID_ARGUMENT;
    return (-1);
}
#endif

static int ft_remove_directory_leaf(const char *path)
{
#if defined(_WIN32)
    if (RemoveDirectoryA(path) == 0)
        return (ft_handle_remove_error());
    ft_errno = ER_SUCCESS;
    return (0);
#else
    if (rmdir(path) != 0)
    {
        ft_errno = FT_ERR_IO;
        return (-1);
    }
    ft_errno = ER_SUCCESS;
    return (0);
#endif
}

static int ft_remove_directory_contents(const char *directory_path);

static int ft_remove_directory_entry(const char *entry_path, unsigned char entry_type)
{
    int directory_check;

    (void)entry_type;
    directory_check = cmp_directory_exists(entry_path);
    if (directory_check == 1)
        return (ft_remove_directory_contents(entry_path));
    if (ft_errno != ER_SUCCESS)
        return (-1);
    return (file_delete(entry_path));
}

static int ft_remove_directory_contents(const char *directory_path)
{
    file_dir    *directory_stream;
    file_dirent *directory_entry;

    if (directory_path == ft_nullptr)
        return (-1);
    directory_stream = file_opendir(directory_path);
    if (directory_stream == ft_nullptr)
    {
        if (cmp_directory_exists(directory_path) != 1)
        {
            ft_errno = ER_SUCCESS;
            return (0);
        }
        return (-1);
    }
    directory_entry = file_readdir(directory_stream);
    while (directory_entry != ft_nullptr)
    {
        if (ft_should_skip_entry(directory_entry->d_name, 1) == 0)
        {
            ft_string entry_path;
            int         remove_result;
            int         directory_check;

            entry_path = file_path_join(directory_path, directory_entry->d_name);
            if (entry_path.get_error())
            {
                file_closedir(directory_stream);
                return (-1);
            }
            remove_result = ft_remove_directory_entry(entry_path.c_str(), directory_entry->d_type);
            if (remove_result != 0)
            {
                file_closedir(directory_stream);
                return (-1);
            }
            directory_check = cmp_directory_exists(entry_path.c_str());
            if (directory_check == 1)
            {
                if (ft_remove_directory_leaf(entry_path.c_str()) != 0)
                {
                    file_closedir(directory_stream);
                    return (-1);
                }
            }
            else if (directory_check == 0 && ft_errno != ER_SUCCESS)
            {
                file_closedir(directory_stream);
                return (-1);
            }
        }
        directory_entry = file_readdir(directory_stream);
    }
    if (file_closedir(directory_stream) != 0)
        return (-1);
    ft_errno = ER_SUCCESS;
    return (0);
}

static int ft_clear_directory_entries(const char *directory_path, int remove_all)
{
    file_dir    *directory_stream;
    file_dirent *directory_entry;

    if (directory_path == ft_nullptr)
        return (-1);
    directory_stream = file_opendir(directory_path);
    if (directory_stream == ft_nullptr)
    {
        if (cmp_directory_exists(directory_path) != 1)
        {
            ft_errno = ER_SUCCESS;
            return (0);
        }
        return (-1);
    }
    directory_entry = file_readdir(directory_stream);
    while (directory_entry != ft_nullptr)
    {
        if (ft_should_skip_entry(directory_entry->d_name, remove_all) == 0)
        {
            ft_string entry_path;
            int         remove_result;
            int         directory_status;

            entry_path = file_path_join(directory_path, directory_entry->d_name);
            if (entry_path.get_error())
            {
                file_closedir(directory_stream);
                return (-1);
            }
            remove_result = ft_remove_directory_entry(entry_path.c_str(), directory_entry->d_type);
            if (remove_result != 0)
            {
                file_closedir(directory_stream);
                return (-1);
            }
            directory_status = cmp_directory_exists(entry_path.c_str());
            if (directory_status == 1)
            {
                if (ft_remove_directory_leaf(entry_path.c_str()) != 0)
                {
                    file_closedir(directory_stream);
                    return (-1);
                }
            }
            else if (directory_status == 0 && ft_errno != ER_SUCCESS)
            {
                file_closedir(directory_stream);
                return (-1);
            }
        }
        directory_entry = file_readdir(directory_stream);
    }
    if (file_closedir(directory_stream) != 0)
        return (-1);
    ft_errno = ER_SUCCESS;
    return (0);
}

void ft_fclean(void)
{
    int confirm;

    confirm = 0;
    if (g_dnd_test == false)
    {
        confirm = ft_readline_confirm("type yes to confirm or no to abort: ");
        if (confirm == RL_INPUT_CANCEL)
        {
            pf_printf("Command cancelled.\n");
            return ;
        }
        if (confirm != 0)
            return ;
    }
    if (ft_clear_directory_entries("./data", 1) != 0)
    {
        const char  *error_message;

        error_message = ft_strerror(ft_errno);
        if (!error_message)
            error_message = "unknown error";
        pf_printf_fd(2, "138-Error: remove failed: %s\n", error_message);
    }
    return ;
}

void ft_clean(void)
{
    int confirm;

    confirm = 0;
    if (g_dnd_test == false)
    {
        confirm = ft_readline_confirm("type yes to confirm or no to abort: ");
        if (confirm == RL_INPUT_CANCEL)
        {
            pf_printf("Command cancelled.\n");
            return ;
        }
        if (confirm != 0)
            return ;
    }
    if (ft_clear_directory_entries("./data", 0) != 0)
    {
        const char  *error_message;

        error_message = ft_strerror(ft_errno);
        if (!error_message)
            error_message = "unknown error";
        pf_printf_fd(2, "143-Error: remove failed: %s\n", error_message);
    }
    return ;
}
