#include "dnd_tools.h"

static void	ft_npc_write_file_1(t_char *info, t_stats *stats, int fd)
{
	ft_printf_fd(fd, "HEALTH=%i\n", stats->health);
	ft_printf_fd(fd, "TEMP_HP=%i\n", stats->temp_hp);
	ft_printf_fd(fd, "AC=%i\n", stats->ac);
	ft_printf_fd(fd, "STR=%i\n", stats->str);
	ft_printf_fd(fd, "DEX=%i\n", stats->dex);
	ft_printf_fd(fd, "CON=%i\n", stats->con);
	ft_printf_fd(fd, "INT=%i\n", stats->inte);
	ft_printf_fd(fd, "WIS=%i\n", stats->wis);
	ft_printf_fd(fd, "CHA=%i\n", stats->cha);
	ft_printf_fd(fd, "TURN=%i\n", stats->turn);
	ft_printf_fd(fd, "PHASE=%i\n", stats->phase);
	ft_printf_fd(fd, "INITIATIVE=%i\n", info->initiative);
	ft_printf_fd(fd, "BLESS_DUR=%i\n", info->bufs.bless.duration);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_DUR=%i\n", info->bufs.lightning_strike.duration);
	ft_printf_fd(fd, "PROTECTIVE_WINDS_DUR=%i\n", info->bufs.protective_winds.duration);
	return ;
}

void	ft_npc_write_file(t_char *info, t_stats *stats)
{
	int	fd;

	fd = open(info->save_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "2-Error opening file %s: %s\n", info->save_file, strerror(errno));
		return ;
	}
	ft_npc_write_file_1(info, stats, fd);
	return ;
}
