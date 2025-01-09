#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#define EXIT_FAILURE 1

void ft_fclean(void)
{
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
        execvp(command[0], (char* const*)command);
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
}

void ft_clean(void)
{
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
        execvp(command[0], (char* const*)command);
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
    return ;
}

