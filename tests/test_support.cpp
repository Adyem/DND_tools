#include "test_support.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../libft/Printf/printf.hpp"
#include "../libft/Libft/libft.hpp"
#include "../libft/File/file_utils.hpp"
#include "../libft/File/open_dir.hpp"
#include "../libft/GetNextLine/get_next_line.hpp"
#include "../libft/Compatebility/compatebility_internal.hpp"
#include "../dnd_tools.hpp"
#if defined(_WIN32)
# include <windows.h>
#else
# include <sys/stat.h>
#endif

static int          g_saved_stderr_fd = -1;
static int          g_saved_stdout_fd = -1;
static const char   *g_current_test_suite = NULL;

static void test_create_directory_component(const char *directory_path, size_t length)
{
    ft_string   partial;

    if (directory_path == ft_nullptr || length == 0)
        return ;
    partial.assign(directory_path, length);
    if (partial.size() == 0)
        return ;
    if (cmp_directory_exists(partial.c_str()) == 1)
    {
        ft_errno = ER_SUCCESS;
        return ;
    }
    if (file_create_directory(partial.c_str(), 0777) != 0)
    {
        if (cmp_directory_exists(partial.c_str()) == 1)
            ft_errno = ER_SUCCESS;
    }
    return ;
}

void    test_create_directory(const char *directory_path)
{
    size_t  index;
    size_t  length;

    if (directory_path == ft_nullptr)
        return ;
    if (cmp_directory_exists(directory_path) == 1)
    {
        ft_errno = ER_SUCCESS;
        return ;
    }
    length = static_cast<size_t>(ft_strlen(directory_path));
    index = 0;
    while (index < length)
    {
        if (directory_path[index] == '/' || directory_path[index] == '\\')
            test_create_directory_component(directory_path, index);
        index++;
    }
    test_create_directory_component(directory_path, length);
    return ;
}

static void ensure_tests_output_directory()
{
    test_create_directory("tests_output");
    return ;
}

int     test_path_exists(const char *path)
{
    if (path == ft_nullptr)
        return (0);
    if (cmp_directory_exists(path) == 1)
    {
        ft_errno = ER_SUCCESS;
        return (1);
    }
    if (file_exists(path) == 1)
    {
        ft_errno = ER_SUCCESS;
        return (1);
    }
    if (ft_errno == FT_EINVAL)
        ft_errno = ER_SUCCESS;
    return (0);
}

static int  test_remove_directory_contents(const char *directory_path);

void    test_remove_directory(const char *directory_path)
{
    if (directory_path == ft_nullptr)
        return ;
    if (test_remove_directory_contents(directory_path) != 0)
        return ;
#if defined(_WIN32)
    if (RemoveDirectoryA(directory_path) == 0)
    {
        DWORD last_error;

        last_error = GetLastError();
        if (last_error != 0)
            ft_errno = static_cast<int>(last_error) + ERRNO_OFFSET;
        else
            ft_errno = FT_EINVAL;
    }
    else
        ft_errno = ER_SUCCESS;
#else
    if (rmdir(directory_path) != 0)
        ft_errno = FT_EIO;
    else
        ft_errno = ER_SUCCESS;
#endif
    return ;
}

void    test_remove_path(const char *path)
{
    if (path == ft_nullptr)
        return ;
    if (cmp_directory_exists(path) == 1)
    {
        test_remove_directory(path);
        return ;
    }
    if (file_exists(path) == 1)
    {
        if (file_delete(path) == 0)
            ft_errno = ER_SUCCESS;
        return ;
    }
    if (ft_errno == FT_EINVAL)
        ft_errno = ER_SUCCESS;
    return ;
}

static int  test_remove_directory_contents(const char *directory_path)
{
    file_dir    *directory_stream;
    file_dirent *directory_entry;

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
        if (ft_strcmp(directory_entry->d_name, ".") != 0
            && ft_strcmp(directory_entry->d_name, "..") != 0)
        {
            ft_string   entry_path;

            entry_path = file_path_join(directory_path, directory_entry->d_name);
            if (entry_path.get_error() != ER_SUCCESS)
            {
                file_closedir(directory_stream);
                return (-1);
            }
            if (directory_entry->d_type == DT_DIR)
            {
                test_remove_directory(entry_path.c_str());
                if (ft_errno != ER_SUCCESS)
                {
                    file_closedir(directory_stream);
                    return (-1);
                }
            }
            else if (file_delete(entry_path.c_str()) != 0)
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

bool g_dnd_test = false;

void test_assert_true(int condition, const char *message)
{
    if (!condition)
    {
        if (g_current_test_suite != NULL)
        {
            pf_printf("%s: FAIL\n", g_current_test_suite);
            g_current_test_suite = NULL;
        }
        ft_fprintf(stderr, "Test failed: %s\n", message);
        ft_errno = ER_SUCCESS;
        ft_exit(ft_nullptr, 1);
    }
    return ;
}

void    test_begin_suite(const char *suite_name)
{
    g_current_test_suite = suite_name;
    return ;
}

void    test_end_suite_success()
{
    if (g_current_test_suite == NULL)
        return ;
    pf_printf("%s: PASS\n", g_current_test_suite);
    g_current_test_suite = NULL;
    return ;
}

void    test_begin_error_capture(const char *file_path)
{
    FILE    *file;
    int     file_descriptor;
    int     duplicate_result;

    if (file_path == NULL)
        return ;
    ensure_tests_output_directory();
    fflush(stderr);
    if (g_saved_stderr_fd == -1)
    {
        g_saved_stderr_fd = dup(fileno(stderr));
        test_assert_true(g_saved_stderr_fd != -1, "Failed to duplicate stderr for capture");
    }
    file = ft_fopen(file_path, "w");
    test_assert_true(file != NULL, "Failed to open error capture file");
    file_descriptor = fileno(file);
    duplicate_result = dup2(file_descriptor, fileno(stderr));
    test_assert_true(duplicate_result != -1, "Failed to redirect stderr to capture file");
    ft_fclose(file);
    return ;
}

void    test_end_error_capture()
{
    int restore_result;

    if (g_saved_stderr_fd == -1)
        return ;
    fflush(stderr);
    restore_result = dup2(g_saved_stderr_fd, fileno(stderr));
    test_assert_true(restore_result != -1, "Failed to restore stderr after capture");
    close(g_saved_stderr_fd);
    g_saved_stderr_fd = -1;
    return ;
}

void    test_begin_output_capture(const char *file_path)
{
    FILE    *file;
    int     file_descriptor;
    int     duplicate_result;

    if (file_path == NULL)
        return ;
    ensure_tests_output_directory();
    fflush(stdout);
    if (g_saved_stdout_fd == -1)
    {
        g_saved_stdout_fd = dup(fileno(stdout));
        test_assert_true(g_saved_stdout_fd != -1, "Failed to duplicate stdout for capture");
    }
    file = ft_fopen(file_path, "w");
    test_assert_true(file != NULL, "Failed to open output capture file");
    file_descriptor = fileno(file);
    duplicate_result = dup2(file_descriptor, fileno(stdout));
    test_assert_true(duplicate_result != -1, "Failed to redirect stdout to capture file");
    ft_fclose(file);
    return ;
}

void    test_end_output_capture()
{
    int restore_result;

    if (g_saved_stdout_fd == -1)
        return ;
    fflush(stdout);
    restore_result = dup2(g_saved_stdout_fd, fileno(stdout));
    test_assert_true(restore_result != -1, "Failed to restore stdout after capture");
    close(g_saved_stdout_fd);
    g_saved_stdout_fd = -1;
    return ;
}

ft_string    test_read_file_to_string(const char *file_path)
{
    char    **lines;
    ft_string   content;
    int     index;

    if (file_path == NULL)
        return (ft_string());
    lines = ft_open_and_read_file(file_path, 256);
    if (lines == ft_nullptr)
        return (ft_string());
    index = 0;
    while (lines[index] != ft_nullptr)
    {
        content.append(lines[index]);
        cma_free(lines[index]);
        index++;
    }
    cma_free(lines);
    return (content);
}

void    test_delete_file(const char *file_path)
{
    if (file_path == NULL)
        return ;
    test_remove_path(file_path);
    return ;
}
