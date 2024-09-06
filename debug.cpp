#include "dnd_tools.hpp"
#include "libft/printf/ft_printf.hpp"

void	ft_print_content(char **content)
{
	int	i;

	if (DEBUG != 1)
		return ;
	i = 0;
	if (content)
	{
		while (content[i])
		{
			ft_printf("%s\n", content[i]);
			i++;
		}
	}
	return ;
}
