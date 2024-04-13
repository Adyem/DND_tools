#include "dnd_tools.h"

void	ft_fclean(void)
{
	int		status; 
	char	*command[5];
	pid_t	pid;

	command[0] = "/bin/sh";
	command[1] = "-c";
	command[2] = "rm -rf";
	command[3] = "./data/*";
	command[4] = NULL;
	if (ft_read_line_yesorno("type yes for confirm or no to abort: "))
			return ;
	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "Fork failed: %s\n", strerror(errno));
		return ;
	}
	else if (pid == 0)
	{
		execvp(command[0], command);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return ;
}
