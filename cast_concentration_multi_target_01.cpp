#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

static int ft_open_target_files(t_char *info, t_char **target, int *fd, char **string, int amount)
{
    int i;
	int j;

	i = 0;
    while (i < amount)
    {
        if (!target[i] || !target[i]->save_file)
        {
            ft_printf("112-Error: invalid target or missing save file\n");
            break ;
        }
        fd[i] = open(target[i]->save_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd[i] == -1)
        {
            ft_printf("113-Error: opening file %s\n", target[i]->save_file);
            break ;
        }
		i++;
    }

    if (i < amount)
    {
		j = 0;
        while (j < i)
		{
            ft_npc_write_file(info, &info->stats, &info->c_resistance, fd[j]);
            close(fd[j]);
            fd[j] = -1;
			j++;
        }
		j = 0;
        while(j < amount)
        {
            if (target[j])
            {
                ft_free_info(target[j]);
                target[j] = nullptr;
            }
            if (string[j])
            {
                cma_free(string[j]);
                string[j] = nullptr;
            }
			j++;
        }
        return (0);
    }
	return (1);
}

static void ft_initialize_variables(int *fd, char **string, t_char **target)
{
    int i = 0;
    while (i < 20)
    {
        string[i] = nullptr;
        fd[i] = -1;
        target[i] = nullptr;
        i++;
    }
    return ;
}

static int ft_check_target_amount(int target_amount)
{
    if (target_amount > 20)
    {
        ft_printf("110-Error: too many targets\n");
        return (0);
    }
    return (1);
}

static char *ft_read_target_name(int i)
{
    char message[55];
    char *target_name;

    sprintf(message, "Requesting the name of the %s target", ft_ordinal_suffix(i + 1));
    target_name = rl_readline(message);
    if (!target_name)
    {
        ft_printf("108-Error: Failed to allocate memory for readline target\n");
        return (nullptr);
    }
    return (target_name);
}

static t_char *ft_validate_and_fetch_target(char *target_name, t_char *info)
{
    if (ft_set_stats_check_name(target_name))
    {
        if (ft_check_player_character(target_name))
        {
            ft_printf("111-Error: target does not exist\n");
            return (nullptr);
        }
        return (nullptr);
    }
    else
    {
        t_char *target_info = ft_get_info(target_name, info->struct_name);
        if (!target_info)
        {
            ft_printf("109-Error: getting info for %s\n", target_name);
            return (nullptr);
        }
        return (target_info);
    }
}

static void ft_free_memory_cmt(t_char **target, char **string, int amount)
{
    int j = 0;

    while (j < amount)
    {
        if (target[j])
            ft_free_info(target[j]);
        if (string[j])
            cma_free(string[j]);
        target[j] = nullptr;
        string[j] = nullptr;
        j++;
    }
    return ;
}

void ft_cast_concentration_multi_target(t_char *info, const char **input, t_buff *buff)
{
    int     fd[20];
    char    *string[20];
    t_char  *target[20];
    int     i;

    (void)input;
    ft_initialize_variables(fd, string, target);
    if (!ft_check_target_amount(buff->target_amount))
        return ;
    i = 0;
    while (i < buff->target_amount)
    {
        string[i] = ft_read_target_name(i);
        if (!string[i])
        {
            ft_free_memory_cmt(target, string, i);
            return ;
        }
        target[i] = ft_validate_and_fetch_target(string[i], info);
        while (!target[i])
        {
            cma_free(string[i]);
            string[i] = nullptr;
            i++;
        }
        i++;
    }
    if (!ft_open_target_files(info, target, fd, string, buff->target_amount))
		return ;
	ft_free_memory_cmt(target, string, i);
	return ;
}
