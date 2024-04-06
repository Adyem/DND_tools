#include "dnd_tools.h"

static void	ft_free_parse(char **to_parse)
{
	int	i;

	i = 0;
	if (to_parse)
	{
		while (to_parse[i])
		{
			free(to_parse[1]);
			i++;
		}
		free(to_parse);
	}
}

static char	**ft_realloc_result(char *result, int index)
{
	char	**temp;
	int		i;

	temp = ft_calloc(index + 2, sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while(result[i])
	{
		temp[i] = result[i];
		i++;
	}
	free(result);
	return (temp);
}

static void	ft_command_parse(char *string, int nested)
{
	int	i;
	int	j;

	while (*string)
	{
		i = 0;
		while (string[i] != '(' && string[i])
			i++;
		if (string[i] == '(')
			ft_command_parse(&string[i], 1);
		else if (string[i] == ')' && nested == 0)
			break ;
		else if (!string[i] && nested == 1)
			break ;
		else if (string[i] == ')' && nested == 1)
			j = i;
		if (!string[i])
			j = i;
	}
	return ;
}

void	ft_command_roll(char **argv)
{
	char	**original;
	char	*result;
	int		i;

	original = argv;
	result = NULL;
	argv++;
	i = 1;
	while(argv[i])
	{
		result = ft_strjoin_gnl(result, argv[i]);
		if (!result)
		{
			free(argv);
			return ;
		}
		i++;
	}
	ft_command_roll_parse(result, 0);
	free(result);
	free(argv);
	return ;
}
