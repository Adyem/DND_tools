#include "dnd_tools.h"

int	ft_request_initiative(t_pc *player)
{
	char	*message;
	char	*input;
	int		initiative;
	
	message = ft_strjoin("requesting initiative for ", player->name);
	if (!message)
		return (1);
	while ((input = readline(message)))
	{
		if (!input)
			return (1);
		if (ft_check_value)
		{
			free(input);
			ft_printf_fd("requesting a number between 1 and 50\n");
			continue
		}
		initiative = ft_atoi(input);
		free(input);
		if (!(initiative >= 1 || iniative <= 50))
		{
			ft_printf_fd("requesting a number between 1 and 50\n");
			continue
		}
		player->initiative = initiative;
		break ;
	}
	free(message);
	return (0);
}