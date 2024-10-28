#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

void ft_fclean(void)
{
    int         status; 
    const char  *command[4];
    pid_t       pid;

    command[0] = "/bin/sh";
    command[1] = "-c";
    command[2] = "rm -rf ./data/*";
    command[3] = ft_nullptr;
    if (dnd_test == false && ft_read_line_confirm("type yes to confirm or no to abort: "))
        return ;
    pid = fork();
    if (pid == -1)
    {
        ft_printf_fd(2, "Fork failed: %s\n", strerror(errno));
        return ;
    }
    else if (pid == 0)
    {
        execvp(command[0], (char* const*)command);
        ft_printf_fd(2, "Execvp failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                ft_printf_fd(2, "Command failed with exit status %d\n", exit_status);
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
    command[2] = "rm -rf ./logs/*";
    command[3] = ft_nullptr;
    if (dnd_test == 0 && ft_read_line_confirm("type yes to confirm or no to abort: "))
        return ;
    pid = fork();
    if (pid == -1)
    {
        ft_printf_fd(2, "Fork failed: %s\n", strerror(errno));
        return ;
    }
    else if (pid == 0)
    {
        execvp(command[0], (char* const*)command);
        ft_printf_fd(2, "Execvp failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                ft_printf_fd(2, "Command failed with exit status %d\n", exit_status);
        }
    }
	return ;
}
