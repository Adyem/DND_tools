#include "dnd_tools.h"
#include "libft/printf_fd/ft_printf_fd.h"

static int ft_create_dir()
{
    struct stat st = {0};

    if (stat("data", &st) == -1)
    {
        if (errno == ENOENT)
        {
            if (mkdir("data", 0700) == -1)
            {
                ft_printf_fd(2, "001-Error failed to create directory: %s\n", strerror(errno));
                return (1);
            }
            else
            {
                if (DEBUG == 1)
                    ft_printf("Data folder created successfully\n");
            }
        }
        else
        {
            ft_printf_fd(2, "002-Error failed to stat directory: %s\n", strerror(errno));
            return (1);
        }
    }
    else if (S_ISDIR(st.st_mode))
    {
        if (access("data", R_OK | W_OK) == -1)
        {
            ft_printf_fd(2, "003-Error no read/write access to 'data' directory: %s\n", strerror(errno));
            return (1);
        }
        if (DEBUG == 1)
            ft_printf("Data folder already exists with proper access rights\n");
    }
    else
    {
        ft_printf_fd(2, "004-Error path exists but is not a directory\n");
        return (1);
    }

    return (0);
}

int main(int argc, char **argv)
{
	t_name	*name;

	(void)argv;
	if (DEBUG == 1)
		printf("size of t_char struct is %zu\n", sizeof(t_char));
	if (argc > 1)
	{
		ft_printf_fd(2, "005-Error expecting no arguments\n");
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
