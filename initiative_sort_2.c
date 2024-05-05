#include "dnd_tools.h"

void	ft_initiative_print(void)
{
	int		i;
	int		fd;
	char	**content;

	fd = open("data/data--initiative", O_RDONLY);
	if (fd == -1)
		return ;
	content = ft_read_file_dnd(fd);
	close(fd);
	if (!content)
		return ;
	ft_printf("\n\ninitiative rolls are:\n");
	i = 0;
	while (content[i])
	{
		ft_printf("%s", content[i]);
		i++;
	}
	ft_free_content(content);
	return ;
}

void	ft_initiative_sort_2(t_pc *players)
{
	int		fd;
	t_pc	*temp;
	t_pc	*highest;

	fd = open("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
		return ;
	while (1)
	{
		temp = players;
		highest = players;
		if (temp->next)
		{
			temp = temp->next;
			if (highest->initiative < temp->initiative)
				highest = temp;
		}
		if (highest->initiative == -1)
			break ;
		ft_printf_fd(fd, "%s=%i\n", highest->name, highest->initiative);
		highest->initiative = -1;
		free(highest->name);
		highest->name = NULL;
	}
	close(fd);
	return ;
}
