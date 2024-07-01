#include "dnd_tools.h"

int	ft_dice_roll(int number, int faces)
{
	int	roll;
	int	result;
	int	i;

	if (faces == 1)
		return (number);
	if (faces < 1 || number < 1)
		return (0);
	result = 0;
	i = 0;
	roll = 0;
	while (i < number)
	{
		do
			roll = rand();
		while
			(roll > (RAND_MAX - (RAND_MAX % faces)) + 1);
		result += (roll % faces) + 1;
		i++;
	}
	if (DEBUG == 1)
		ft_printf("The dice rolled %i on %i faces with %i amount of dice\n",
				result, faces, number);
	return (result);
}

void	ft_reroll(t_char *info, int *result)
{
	int second_roll;
	if (info->advantage > 0)
	{
		second_roll = ft_dice_roll(1, 20);
		if (second_roll > *result)
			*result = second_roll;
	}
	else if (info->advantage < 0)
	{
		second_roll = ft_dice_roll(1, 20);
		if (second_roll < *result)
			*result = second_roll;
	}
	return ;
}

int	ft_double_char_length(char **double_char)
{
	int	i;

	if (!double_char)
		return(0);
	i = 0;
	while (double_char[i])
		i++;
	return (i);
}

int ft_open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		ft_printf_fd(2, "Error opening file %s: %s\n", filename, strerror(errno));
	return (fd);
}

void	ft_dual_save_file(t_char *info, t_char *target)
{
	int	fd_target;
	int	fd_info;

	fd_target = ft_open_file(target->save_file);
	fd_info = ft_open_file(info->save_file);
    if (fd_target == -1 || fd_info == -1)
    {
        if (fd_target != -1)
            close(fd_target);
        if (fd_info != -1)
            close(fd_info);
        info->flags.alreaddy_saved = 1;
        ft_free_info(target);
        return;
    }
	ft_npc_write_file(target, &target->stats, &target->c_resistance, fd_target);
    ft_npc_write_file(info, &info->stats, &info->c_resistance, fd_info);
}
