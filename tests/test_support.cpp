#include "test_support.hpp"
#include "../libft/CMA/CMA.hpp"
#include "../dnd_tools.hpp"
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <system_error>
#include <unistd.h>

static int  g_saved_stderr_fd = -1;

static void ensure_tests_output_directory()
{
    std::error_code  error;

    std::filesystem::create_directories("tests_output", error);
    return ;
}

bool g_dnd_test = false;

void test_assert_true(int condition, const char *message)
{
    if (!condition)
    {
        std::fprintf(stderr, "Test failed: %s\n", message);
        cma_cleanup();
        std::exit(1);
    }
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
    std::fflush(stderr);
    if (g_saved_stderr_fd == -1)
    {
        g_saved_stderr_fd = dup(fileno(stderr));
        test_assert_true(g_saved_stderr_fd != -1, "Failed to duplicate stderr for capture");
    }
    file = std::fopen(file_path, "w");
    test_assert_true(file != NULL, "Failed to open error capture file");
    file_descriptor = fileno(file);
    duplicate_result = dup2(file_descriptor, fileno(stderr));
    test_assert_true(duplicate_result != -1, "Failed to redirect stderr to capture file");
    std::fclose(file);
    return ;
}

void    test_end_error_capture()
{
    int restore_result;

    if (g_saved_stderr_fd == -1)
        return ;
    std::fflush(stderr);
    restore_result = dup2(g_saved_stderr_fd, fileno(stderr));
    test_assert_true(restore_result != -1, "Failed to restore stderr after capture");
    close(g_saved_stderr_fd);
    g_saved_stderr_fd = -1;
    return ;
}

std::string  test_read_file_to_string(const char *file_path)
{
    FILE            *file;
    std::string     content;
    char            buffer[256];
    size_t          read_bytes;
    int             continue_reading;

    if (file_path == NULL)
        return (content);
    file = std::fopen(file_path, "r");
    if (file == NULL)
        return (content);
    continue_reading = 1;
    while (continue_reading)
    {
        read_bytes = std::fread(buffer, 1, sizeof(buffer), file);
        if (read_bytes == 0)
            continue_reading = 0;
        else
            content.append(buffer, read_bytes);
    }
    std::fclose(file);
    return (content);
}

void    test_delete_file(const char *file_path)
{
    std::error_code  error;

    if (file_path == NULL)
        return ;
    std::filesystem::remove(file_path, error);
    return ;
}
