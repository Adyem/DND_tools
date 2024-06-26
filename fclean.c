/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fclean.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adyem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:16:10 by adyem             #+#    #+#             */
/*   Updated: 2024/05/03 18:38:06 by adyem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dnd_tools.h"

void	ft_fclean(void)
{
	int		status; 
	char	*command[4];
	pid_t	pid;

	command[0] = "/bin/sh";
	command[1] = "-c";
	command[2] = "rm -rf ./data/*";
	command[3] = NULL;
	if (ft_read_line_confirm("type yes for confirm or no to abort: "))
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

void    ft_clean(void)
{
	int     status;
	char    *command[4];
	pid_t   pid;

	command[0] = "/bin/sh";
	command[1] = "-c";
	command[2] = "find ./data/ -type f ! -name 'data--*' " \
		"! -name 'PC--*' -exec rm -rf {} +";
	command[3] = NULL;
	if (ft_read_line_confirm("type yes for confirm or no to abort: "))
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
