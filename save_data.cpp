#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <string.h>

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
	ft_printf_fd(fd, "FLAME_GEYSER_DURATION=%i\n", info->bufs.flame_geyser.duration);
	ft_printf_fd(fd, "FLAME_GEYSER_CLOSE_TO_TOWER_D=%i\n", info->bufs.flame_geyser.close_to_tower_d);
	ft_printf_fd(fd, "FLAME_GEYSER_TOWER_EXPLODE_D=%i\n", info->bufs.flame_geyser.tower_explode_d);
	ft_printf_fd(fd, "METEOR_STRIKE_DURATION=%i\n", info->bufs.meteor_strike.duration);
	ft_printf_fd(fd, "METEOR_STRIKE_ONE_TARGET_D=%i\n", info->bufs.meteor_strike.one_target_d);
	ft_printf_fd(fd, "METEOR_STRIKE_TWO_TARGETS_D=%i\n", info->bufs.meteor_strike.two_targets_d);
	ft_printf_fd(fd, "METEOR_STRIKE_THREE_TARGETS_D=%i\n", info->bufs.meteor_strike.three_targets_d);
	ft_printf_fd(fd, "METEOR_STRIKE_FOUR_TARGETS_D=%i\n", info->bufs.meteor_strike.four_targets_d);
	ft_printf_fd(fd, "METEOR_STRIKE_FIVE_TARGETS_D=%i\n", info->bufs.meteor_strike.five_targets_d);
	ft_npc_write_file_double_char("METEOR_STRIKE_TARGET=", info->bufs.meteor_strike.target_id, fd, info);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_DURATION=%i\n", info->bufs.lightning_strike.duration);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_AMOUNT=%i\n", info->bufs.lightning_strike.amount);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_DISTANCE=%i\n", info->bufs.lightning_strike.distance);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_DICE_AMOUNT=%i\n", info->bufs.lightning_strike.dice_amount);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_DICE_FACES=%i\n", info->bufs.lightning_strike.dice_faces);
	ft_printf_fd(fd, "LIGHTNING_STRIKE_EXTRA_DAMAGE=%i\n", info->bufs.lightning_strike.extra_damage);
	ft_printf_fd(fd, "LIGHTNING_STRIKEV2_DURATION=%i\n", info->bufs.lightning_strikeV2.duration);
	ft_printf_fd(fd, "LIGHTNING_STRIKEV2_AMOUNT=%i\n", info->bufs.lightning_strikeV2.amount);
	ft_printf_fd(fd, "LIGHTNING_STRIKEV2_DISTANCE=%i\n", info->bufs.lightning_strikeV2.distance);
	ft_printf_fd(fd, "LIGHTNING_STRIKEV2_DICE_AMOUNT=%i\n", info->bufs.lightning_strikeV2.dice_amount);
	ft_printf_fd(fd, "LIGHTNING_STRIKEV2_DICE_FACES=%i\n", info->bufs.lightning_strikeV2.dice_faces);
	ft_printf_fd(fd, "LIGHTNING_STRIKEV2_EXTRA_DAMAGE=%i\n", info->bufs.lightning_strikeV2.extra_damage);
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
	ft_npc_write_file_2(info, resistance, fd);
	close(fd);
	info->flags.alreaddy_saved = 1;
	return ;
}
