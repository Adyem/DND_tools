#include "dnd_tools.h"
#include "libft/printf_fd/ft_printf_fd.h"

static void	ft_npc_write_file_1(t_char *info, t_stats *stats, int fd)
{
	ft_printf_fd(fd, "HEALTH=%i\n", stats->health);
	ft_printf_fd(fd, "TEMP_HP=%i\n", stats->temp_hp);
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

static void	ft_npc_write_file_double_char(const char *msg, char **targets, int fd, t_char *info)
{
	int	i;

	i = 0;
	if (targets)
	{
		while (targets[i])
		{
			if (DEBUG == 1)
				ft_printf_fd(1, "saving array %s %s%s\n", info->name, msg, targets[i]);
			ft_printf_fd(fd, "%s%s\n", msg, targets[i]);
			i++;
		}
	}
}

static void	ft_npc_write_file_2(t_char *info, t_resistance *resistance, int fd)
{
	ft_printf_fd(fd, "ACID_RESISTANCE=%i\n", resistance->acid);
	ft_printf_fd(fd, "BLUDGEONING_RESISTANCE=%i\n", resistance->bludgeoning);
	ft_printf_fd(fd, "COLD_RESISTANCE=%i\n", resistance->cold);
	ft_printf_fd(fd, "FIRE_RESISTANCE=%i\n", resistance->fire);
	ft_printf_fd(fd, "FORCE_RESISTANCE=%i\n", resistance->force);
	ft_printf_fd(fd, "LIGHTNING_RESISTANCE=%i\n", resistance->lightning);
	ft_printf_fd(fd, "NECROTIC_RESISTANCE=%i\n", resistance->necrotic);
	ft_printf_fd(fd, "PIERCING_RESISTANCE=%i\n", resistance->piercing);
	ft_printf_fd(fd, "POISON_RESISTANCE=%i\n", resistance->poison);
	ft_printf_fd(fd, "PSYCHIC_RESISTANCE=%i\n", resistance->psychic);
	ft_printf_fd(fd, "RADIANT_RESISTANCE=%i\n", resistance->radiant);
	ft_printf_fd(fd, "SLASHING_RESISTANCE=%i\n", resistance->slashing);
	ft_printf_fd(fd, "THUNDER_RESISTANCE=%i\n", resistance->thunder);
	ft_printf_fd(fd, "CONCENTRATION=%i\n", info->concentration.concentration);
	ft_printf_fd(fd, "CONC_SPELL_ID=%i\n", info->concentration.spell_id);
	ft_printf_fd(fd, "CONC_DICE_AMOUNT=%i\n", info->concentration.dice_amount_mod);
	ft_printf_fd(fd, "CONC_DICE_FACES=%i\n", info->concentration.dice_faces_mod);
	ft_printf_fd(fd, "CONC_BASE_MOD=%i\n", info->concentration.base_mod);
	ft_printf_fd(fd, "CONC_DURATION=%i\n", info->concentration.duration);
	ft_npc_write_file_double_char("CONC_TARGETS=", info->concentration.targets, fd, info);
	ft_printf_fd(fd, "HUNTERS_MARK_AMOUNT=%i\n", info->debufs.hunters_mark.amount);
	ft_npc_write_file_double_char("HUNTERS_MARK_CASTER=", info->debufs.hunters_mark.caster_name, fd, info);
	ft_printf_fd(fd, "CHAOS_ARMOR_DURATION=%i\n", info->bufs.chaos_armor.duration);
	ft_printf_fd(fd, "PRONE=%i\n", info->flags.prone);
	ft_printf_fd(fd, "BLINDED=%i\n", info->debufs.blinded);
	return ;
}

void	ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance, int fd)
{
	if (DEBUG == 1)
		ft_printf("fd = %i\n", fd);
	if (info->flags.alreaddy_saved)
		return ;
	if (fd == -1)
		fd = open(info->save_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf_fd(2, "2-Error opening file %s: %s\n", info->save_file, strerror(errno));
		return ;
	}
	ft_npc_write_file_1(info, stats, fd);
	if (info->version_number >= 2)
		ft_npc_write_file_2(info, resistance, fd);
	close(fd);
	info->flags.alreaddy_saved = 1;
	return ;
}
