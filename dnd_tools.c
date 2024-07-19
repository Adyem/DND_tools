#include "dnd_tools.h"

static int	ft_create_dir()
{
	struct	stat st = {0};

	if (stat("data", &st) == -1)
	{
		if (mkdir("data", 0700) == -1)
		{
			ft_printf_fd(2, "Failed to create directory: %s\n", strerror(errno));
			return (1);
		}
		else
			if (DEBUG == 1)
				ft_printf("Data folder created succesfully\n");
	}
	else if (DEBUG == 1)
		ft_printf("Data folder alreaddy exists\n");
	return (0);
}

int main(int argc, char **argv)
{
	t_name	*name;

	(void)argv;
	printf("size of t_char struct is %zu\n", sizeof(t_char));
	if (argc > 1)
	{
		ft_printf_fd(2, "Error: expecting no arguments\n");
		return (1);
	}
	srand((unsigned)time(NULL));
	if (DEBUG == 1)
	{
		ft_printf("DEBUGGING\n");
		ft_printf("Rand Max = %i\n", RAND_MAX);
	}
	if (ft_create_dir())
		return (1);
	name = ft_allocate_memory_name();
	ft_request_input(name);
	clear_history();
	ft_free_memory_name(name, 0);
	return (0);
}
