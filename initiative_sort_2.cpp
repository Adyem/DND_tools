#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libft/printf/ft_printf.hpp"
#include "libft/printf_fd/ft_printf_fd.hpp"

void	ft_initiative_print(void)
{
	int		i;
	int		fd;
	char	**content;

	fd = open("data/data--initiative", O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "Error opening file: %s\n", strerror(errno));
		return;
	}
	content = ft_read_file_dnd(fd);
	close(fd);
	if (!content)
	{
		ft_printf_fd(2, "261-Error allocating memory\n");
		return ;
	}
	ft_printf("\n\ninitiative rolls are:\n");
	i = 0;
	while (content[i])
	{
		ft_printf("%s", content[i]);
		i++;
	}
	ft_free_double_char(content);
	return ;
}

void	ft_initiative_print_pc(t_pc *players)
{
	t_pc	*temp;

	temp = players;
	while (temp)
	{
		ft_printf("%s=%i\n", temp->name, temp->initiative);
		temp = temp->next;
	}
	return ;
}

void	ft_initiative_sort_2(t_pc *players)
{
	int		turn;
	int		fd;
	t_pc	*temp;
	t_pc	*highest;

	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "262-Error opening file: %s\n", strerror(errno));
		return ;
	}
	turn = 0;
	while (1)
	{
		temp = players;
		highest = NULL;
		while (temp)
		{
			if ((highest == NULL || temp->initiative > highest->initiative) &&
					temp->initiative != -1)
				highest = temp;
			temp = temp->next;
		}
		if (highest == NULL)
			break ;
		if (turn == 0)
		{
			ft_printf_fd(fd, "--turn--%s=%i\n", highest->name, highest->initiative);
			turn = 1;
		}
		else
			ft_printf_fd(fd, "%s=%i\n", highest->name, highest->initiative);
		highest->initiative = -1;
	}
	close(fd);
	return ;
}
