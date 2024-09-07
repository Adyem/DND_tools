#include "dnd_tools.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>

void ft_fclean(void)
{
    int			status; 
    const char	*command[4];
    pid_t		pid;

    command[0] = "/bin/sh";
    command[1] = "-c";
    command[2] = "rm -rf ./data/*";
    command[3] = NULL;
    if (ft_read_line_confirm("type yes to confirm or no to abort: "))
        return;
    pid = fork();
    if (pid == -1)
    {
        std::cerr << "Fork failed: " << strerror(errno) << std::endl;
        return;
    }
    else if (pid == 0)
    {
        execvp(command[0], (char* const*)command);
        std::cerr << "Execvp failed: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                std::cerr << "Command failed with exit status " << exit_status << std::endl;
        }
    }
}

void ft_clean(void)
{
    int			status;
    const char	*command[4];
    pid_t		pid;

    command[0] = "/bin/sh";
    command[1] = "-c";
    command[2] = "rm -rf ./logs/*";
    command[3] = NULL;
    if (ft_read_line_confirm("type yes to confirm or no to abort: "))
        return;
    pid = fork();
    if (pid == -1)
    {
        std::cerr << "Fork failed: " << strerror(errno) << std::endl;
        return;
    }
    else if (pid == 0)
    {
        execvp(command[0], (char* const*)command);
        std::cerr << "Execvp failed: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                std::cerr << "Command failed with exit status " << exit_status << std::endl;
        }
    }
}
