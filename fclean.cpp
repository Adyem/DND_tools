#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#if !defined(_WIN32)
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
#else
# include <filesystem>
#endif
#include <cstdlib>
#include <cerrno>
#include <cstring>

#define EXIT_FAILURE 1

void ft_fclean(void)
{
#if !defined(_WIN32)
    int         status;
    const char  *command[4];
    pid_t       pid;

    command[0] = "/bin/sh";
    command[1] = "-c";
    command[2] = "rm -rf ./data/*";
    command[3] = ft_nullptr;
    if (g_dnd_test == false && ft_readline_confirm("type yes to confirm or no to abort: "))
        return ;
    pid = fork();
    if (pid == -1)
    {
        pf_printf_fd(2, "138-Error: Fork failed: %s\n", strerror(errno));
        return ;
    }
    else if (pid == 0)
    {
        execvp(command[0], const_cast<char* const*>(command));
        pf_printf_fd(2, "139-Error: Execvp failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                pf_printf_fd(2, "140-Error: Command failed with exit status %d\n", exit_status);
        }
    }
#else
    if (g_dnd_test == false && ft_readline_confirm("type yes to confirm or no to abort: "))
        return ;
    std::error_code ec;
    for (const auto &entry : std::filesystem::directory_iterator("./data", ec))
    {
        std::filesystem::remove_all(entry, ec);
        if (ec)
        {
            pf_printf_fd(2, "138-Error: remove failed: %s\n", ec.message().c_str());
            ec.clear();
        }
    }
#endif
}

void ft_clean(void)
{
#if !defined(_WIN32)
    int         status;
    const char  *command[4];
    pid_t       pid;

    command[0] = "/bin/sh";
    command[1] = "-c";
    command[2] = "find ./data -mindepth 1 -maxdepth 1 \\( ! -name 'data--*' !" \
                                  "-name 'pc--*' \\) -exec rm -rf {} +";
    command[3] = ft_nullptr;
    if (g_dnd_test == 0 && ft_readline_confirm("type yes to confirm or no to abort: "))
        return ;
    pid = fork();
    if (pid == -1)
    {
        pf_printf_fd(2, "141-Error: Fork failed: %s\n", strerror(errno));
        return ;
    }
    else if (pid == 0)
    {
        execvp(command[0], const_cast<char* const*>(command));
        pf_printf_fd(2, "142-Error: Execvp failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                pf_printf_fd(2, "143-Error: Command failed with exit status %d\n", exit_status);
        }
    }
#else
    if (g_dnd_test == 0 && ft_readline_confirm("type yes to confirm or no to abort: "))
        return ;
    std::error_code ec;
    for (const auto &entry : std::filesystem::directory_iterator("./data", ec))
    {
        std::string name = entry.path().filename().string();
        if (name.rfind("data--", 0) == 0 || name.rfind("pc--", 0) == 0)
            continue;
        std::filesystem::remove_all(entry, ec);
        if (ec)
        {
            pf_printf_fd(2, "143-Error: remove failed: %s\n", ec.message().c_str());
            ec.clear();
        }
    }
#endif
    return ;
}

