#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <string.h>

static void	ft_npc_write_file_1(t_char *info, t_stats *stats, int fd)
{
	pf_printf_fd(fd, "%s%i\n", HEALTH_KEY, stats->health);
	pf_printf_fd(fd, "%s%i\n", TEMP_HP_KEY, stats->temp_hp);
	pf_printf_fd(fd, "%s%i\n", STR_KEY, stats->str);
	pf_printf_fd(fd, "%s%i\n", DEX_KEY, stats->dex);
	pf_printf_fd(fd, "%s%i\n", CON_KEY, stats->con);
	pf_printf_fd(fd, "%s%i\n", INT_KEY, stats->inte);
	pf_printf_fd(fd, "%s%i\n", WIS_KEY, stats->wis);
	pf_printf_fd(fd, "%s%i\n", CHA_KEY, stats->cha);
	pf_printf_fd(fd, "%s%i\n", TURN_KEY, stats->turn);
	pf_printf_fd(fd, "%s%i\n", PHASE_KEY, stats->phase);
	pf_printf_fd(fd, "%s%i\n", INITIATIVE_KEY, info->initiative);
	pf_printf_fd(fd, "%s%i\n", BLESS_DUR_KEY, info->bufs.bless.duration);
	pf_printf_fd(fd, "%s%i\n", PROTECTIVE_WINDS_DUR_KEY, info->bufs.protective_winds.duration);
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
				pf_printf_fd(1, "saving array %s %s%s\n", info->name, msg, targets[i]);
			pf_printf_fd(fd, "%s%s\n", msg, targets[i]);
			i++;
		}
	}
}

static void	ft_npc_write_file_2(t_char *info, t_resistance *resistance, int fd)
{
	pf_printf_fd(fd, "%s%i\n", ACID_RESISTANCE_KEY, resistance->acid);
	pf_printf_fd(fd, "%s%i\n", BLUDGEONING_RESISTANCE_KEY, resistance->bludgeoning);
	pf_printf_fd(fd, "%s%i\n", COLD_RESISTANCE_KEY, resistance->cold);
	pf_printf_fd(fd, "%s%i\n", FIRE_RESISTANCE_KEY, resistance->fire);
	pf_printf_fd(fd, "%s%i\n", FORCE_RESISTANCE_KEY, resistance->force);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_RESISTANCE_KEY, resistance->lightning);
	pf_printf_fd(fd, "%s%i\n", NECROTIC_RESISTANCE_KEY, resistance->necrotic);
	pf_printf_fd(fd, "%s%i\n", PIERCING_RESISTANCE_KEY, resistance->piercing);
	pf_printf_fd(fd, "%s%i\n", POISON_RESISTANCE_KEY, resistance->poison);
	pf_printf_fd(fd, "%s%i\n", PSYCHIC_RESISTANCE_KEY, resistance->psychic);
	pf_printf_fd(fd, "%s%i\n", RADIANT_RESISTANCE_KEY, resistance->radiant);
	pf_printf_fd(fd, "%s%i\n", SLASHING_RESISTANCE_KEY, resistance->slashing);
	pf_printf_fd(fd, "%s%i\n", THUNDER_RESISTANCE_KEY, resistance->thunder);
	pf_printf_fd(fd, "%s%i\n", CONCENTRATION_KEY, info->concentration.concentration);
	pf_printf_fd(fd, "%s%i\n", CONC_SPELL_ID_KEY, info->concentration.spell_id);
	pf_printf_fd(fd, "%s%i\n", CONC_DICE_AMOUNT_KEY, info->concentration.dice_amount_mod);
	pf_printf_fd(fd, "%s%i\n", CONC_DICE_FACES_KEY, info->concentration.dice_faces_mod);
	pf_printf_fd(fd, "%s%i\n", CONC_BASE_MOD_KEY, info->concentration.base_mod);
	pf_printf_fd(fd, "%s%i\n", CONC_DURATION_KEY, info->concentration.duration);
	ft_npc_write_file_double_char(CONC_TARGETS_KEY, info->concentration.targets, fd, info);
	pf_printf_fd(fd, "%s%i\n", HUNTERS_MARK_AMOUNT_KEY, info->debufs.hunters_mark.amount);
	ft_npc_write_file_double_char(HUNTERS_MARK_CASTER_KEY,
			info->debufs.hunters_mark.caster_name, fd, info);
	pf_printf_fd(fd, "%s%i\n", CHAOS_ARMOR_DURATION_KEY, info->bufs.chaos_armor.duration);
	pf_printf_fd(fd, "%s%i\n", PRONE_KEY, info->flags.prone);
	pf_printf_fd(fd, "%s%i\n", BLINDED_KEY, info->debufs.blinded.duration);
	pf_printf_fd(fd, "%s%i\n", FLAME_GEYSER_DURATION_KEY,
			info->bufs.flame_geyser.duration);
	pf_printf_fd(fd, "%s%i\n", FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY,
			info->bufs.flame_geyser.close_to_tower_d);
	pf_printf_fd(fd, "%s%i\n", FLAME_GEYSER_TOWER_EXPLODE_D_KEY,
			info->bufs.flame_geyser.tower_explode_d);
	pf_printf_fd(fd, "%s%i\n", FLAME_GEYSER_AMOUNT_KEY,
			info->bufs.flame_geyser.amount);
	pf_printf_fd(fd, "%s%i\n", METEOR_STRIKE_DURATION_KEY,
			info->bufs.meteor_strike.duration);
	pf_printf_fd(fd, "%s%i\n", METEOR_STRIKE_ONE_TARGET_D_KEY,
			info->bufs.meteor_strike.one_target_d);
	pf_printf_fd(fd, "%s%i\n", METEOR_STRIKE_TWO_TARGETS_D_KEY,
			info->bufs.meteor_strike.two_targets_d);
	pf_printf_fd(fd, "%s%i\n", METEOR_STRIKE_THREE_TARGETS_D_KEY,
			info->bufs.meteor_strike.three_targets_d);
	pf_printf_fd(fd, "%s%i\n", METEOR_STRIKE_FOUR_TARGETS_D_KEY,
			info->bufs.meteor_strike.four_targets_d);
	pf_printf_fd(fd, "%s%i\n", METEOR_STRIKE_FIVE_TARGETS_D_KEY,
			info->bufs.meteor_strike.five_targets_d);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKE_DURATION_KEY,
			info->bufs.lightning_strike.duration);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKE_AMOUNT_KEY,
			info->bufs.lightning_strike.amount);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKE_DISTANCE_KEY,
			info->bufs.lightning_strike.distance);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKE_DICE_AMOUNT_KEY,
			info->bufs.lightning_strike.dice_amount);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKE_DICE_FACES_KEY,
			info->bufs.lightning_strike.dice_faces);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY,
			info->bufs.lightning_strike.extra_damage);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKEV2_DURATION_KEY,
			info->bufs.lightning_strikeV2.duration);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKEV2_AMOUNT_KEY,
			info->bufs.lightning_strikeV2.amount);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKEV2_DISTANCE_KEY,
			info->bufs.lightning_strikeV2.distance);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY,
			info->bufs.lightning_strikeV2.dice_amount);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKEV2_DICE_FACES_KEY,
			info->bufs.lightning_strikeV2.dice_faces);
	pf_printf_fd(fd, "%s%i\n", LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY,
			info->bufs.lightning_strikeV2.extra_damage);
	pf_printf_fd(fd, "%s%i\n", EARTH_POUNCE_ACTIVE_KEY,
			info->bufs.earth_pounce.active);
	pf_printf_fd(fd, "%s%i\n", EARTH_POUNCE_BASE_DAMAGE_KEY,
			info->bufs.earth_pounce.base_damage);
	pf_printf_fd(fd, "%s%i\n", ARCANE_POUNCE_ACTIVE_KEY,
			info->bufs.arcane_pounce.active);
	pf_printf_fd(fd, "%s%i\n", ARCANE_POUNCE_EREA_DAMAGE_KEY,
			info->bufs.arcane_pounce.erea_damage);
	pf_printf_fd(fd, "%s%i\n", ARCANE_POUNCE_MAGIC_DAMAGE_KEY,
			info->bufs.arcane_pounce.magic_damage);
	pf_printf_fd(fd, "%s%i\n", FROST_BREATH_ACTIVE_KEY,
			info->bufs.frost_breath.active);
		pf_printf_fd(fd, "%s%i\n", FROST_BREATH_DAMAGE_KEY,
			info->bufs.frost_breath.damage);
	if (info->bufs.meteor_strike.target_id)
		pf_printf_fd(fd, "%s%s\n", METEOR_STRIKE_TARGET_KEY,
			info->bufs.meteor_strike.target_id);
	if (info->bufs.frost_breath.target_id)
		pf_printf_fd(fd, "%s%s\n", FROST_BREATH_TARGET_ID_KEY,
			info->bufs.frost_breath.target_id);
	if (info->bufs.arcane_pounce.target_id)
		pf_printf_fd(fd, "%s%s\n", ARCANE_POUNCE_TARGET_ID_KEY,
			info->bufs.arcane_pounce.target_id);
	if (info->bufs.earth_pounce.target_id)
		pf_printf_fd(fd, "%s%s\n", EARTH_POUNCE_TARGET_ID_KEY,
			info->bufs.earth_pounce.target_id);
	pf_printf_fd(fd, "%s%i\n", REACTION_USED_KEY,
			info->flags.reaction_used);
	return ;
}

void	ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance, int fd)
{
	if (DEBUG == 1)
		pf_printf("fd = %i\n", fd);
	if (info->flags.alreaddy_saved || info->flags.dont_save)
		return ;
	if (fd == -1)
		fd = open(info->save_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		pf_printf_fd(2, "2-Error opening file %s: %s\n", info->save_file, strerror(errno));
		return ;
	}
	ft_npc_write_file_1(info, stats, fd);
	ft_npc_write_file_2(info, resistance, fd);
	close(fd);
	info->flags.alreaddy_saved = 1;
	return ;
}
