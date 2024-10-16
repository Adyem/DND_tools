#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "identification.hpp"

int ft_set_stat_int(char *content_i, const char *key, int *field, int unset_value, t_char *info)
{
	int	i;

	i = ft_strlen(key);
    if (ft_strncmp(content_i, key, i) == 0 && *field == unset_value)
    {
        *field = ft_check_stat(info, content_i, i);
        return (1);
    }
    return (0);
}

int ft_set_stats_1(t_char *info, char **content, int i)
{
    if (ft_set_stat_int(content[i], HEALTH_KEY, &(info->stats.health), -1, info) ||
        ft_set_stat_int(content[i], TEMP_HP_KEY, &(info->stats.temp_hp), -1, info) ||
        ft_set_stat_int(content[i], STR_KEY, &(info->stats.str), -1, info) ||
        ft_set_stat_int(content[i], DEX_KEY, &(info->stats.dex), -1, info) ||
        ft_set_stat_int(content[i], CON_KEY, &(info->stats.con), -1, info) ||
        ft_set_stat_int(content[i], INT_KEY, &(info->stats.inte), -1, info) ||
        ft_set_stat_int(content[i], WIS_KEY, &(info->stats.wis), -1, info) ||
        ft_set_stat_int(content[i], CHA_KEY, &(info->stats.cha), -1, info) ||
        ft_set_stat_int(content[i], TURN_KEY, &(info->stats.turn), -1, info) ||
        ft_set_stat_int(content[i], INITIATIVE_KEY, &(info->initiative), -1, info) ||
        ft_set_stat_int(content[i], BLESS_DUR_KEY, &(info->bufs.bless.duration), 0, info) ||
        ft_set_stat_int(content[i], PHASE_KEY, &(info->stats.phase), -1, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_DUR_KEY, &(info->bufs.lightning_strike.duration), 0, info) ||
        ft_set_stat_int(content[i], PROTECTIVE_WINDS_DUR_KEY, &(info->bufs.protective_winds.duration), 0, info))
	{
        return (0);
    }
    return (1);
}

int ft_set_stats_2(t_char *info, char **content, int i)
{
    if (ft_set_stat_int(content[i], ACID_RESISTANCE_KEY, &(info->c_resistance.acid), -501, info) ||
        ft_set_stat_int(content[i], BLUDGEONING_RESISTANCE_KEY, &(info->c_resistance.bludgeoning), -501, info) ||
        ft_set_stat_int(content[i], COLD_RESISTANCE_KEY, &(info->c_resistance.cold), -501, info) ||
        ft_set_stat_int(content[i], FIRE_RESISTANCE_KEY, &(info->c_resistance.fire), -501, info) ||
        ft_set_stat_int(content[i], FORCE_RESISTANCE_KEY, &(info->c_resistance.force), -501, info) ||
        ft_set_stat_int(content[i], LIGHTNING_RESISTANCE_KEY, &(info->c_resistance.lightning), -501, info) ||
        ft_set_stat_int(content[i], NECROTIC_RESISTANCE_KEY, &(info->c_resistance.necrotic), -501, info) ||
        ft_set_stat_int(content[i], PIERCING_RESISTANCE_KEY, &(info->c_resistance.piercing), -501, info) ||
        ft_set_stat_int(content[i], POISON_RESISTANCE_KEY, &(info->c_resistance.poison), -501, info) ||
        ft_set_stat_int(content[i], PSYCHIC_RESISTANCE_KEY, &(info->c_resistance.psychic), -501, info) ||
        ft_set_stat_int(content[i], RADIANT_RESISTANCE_KEY, &(info->c_resistance.radiant), -501, info) ||
        ft_set_stat_int(content[i], SLASHING_RESISTANCE_KEY, &(info->c_resistance.slashing), -501, info) ||
        ft_set_stat_int(content[i], THUNDER_RESISTANCE_KEY, &(info->c_resistance.thunder), -501, info) ||
        ft_set_stat_int(content[i], CONCENTRATION_KEY, &(info->concentration.concentration), 0, info) ||
        ft_set_stat_int(content[i], CONC_SPELL_ID_KEY, &(info->concentration.spell_id), 0, info) ||
        ft_set_stat_int(content[i], CONC_DICE_AMOUNT_KEY, &(info->concentration.dice_amount_mod), 0, info) ||
        ft_set_stat_int(content[i], CONC_DICE_FACES_KEY, &(info->concentration.dice_faces_mod), 0, info) ||
        ft_set_stat_int(content[i], CONC_BASE_MOD_KEY, &(info->concentration.base_mod), 0, info) ||
        ft_set_stat_int(content[i], CONC_DURATION_KEY, &(info->concentration.duration), 0, info) ||
        ft_set_stat_int(content[i], HUNTERS_MARK_AMOUNT_KEY, &(info->debufs.hunters_mark.amount), 0, info) ||
        ft_set_stat_int(content[i], CHAOS_ARMOR_DURATION_KEY, &(info->bufs.chaos_armor.duration), 0, info) ||
        ft_set_stat_int(content[i], PRONE_KEY, &(info->flags.prone), 0, info) ||
        ft_set_stat_int(content[i], BLINDED_KEY, &(info->debufs.blinded.duration), 0, info) ||
        ft_set_stat_int(content[i], FLAME_GEYSER_DURATION_KEY, &(info->bufs.flame_geyser.duration), 0, info) ||
        ft_set_stat_int(content[i], FLAME_GEYSER_AMOUNT_KEY, &(info->bufs.flame_geyser.amount), 0, info) ||
        ft_set_stat_int(content[i], FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY, &(info->bufs.flame_geyser.close_to_tower_d), 0, info) ||
        ft_set_stat_int(content[i], FLAME_GEYSER_TOWER_EXPLODE_D_KEY, &(info->bufs.flame_geyser.tower_explode_d), 0, info) ||
        ft_set_stat_int(content[i], METEOR_STRIKE_DURATION_KEY, &(info->bufs.meteor_strike.duration), 0, info) ||
        ft_set_stat_int(content[i], METEOR_STRIKE_ONE_TARGET_D_KEY, &(info->bufs.meteor_strike.one_target_d), 0, info) ||
        ft_set_stat_int(content[i], METEOR_STRIKE_TWO_TARGETS_D_KEY, &(info->bufs.meteor_strike.two_targets_d), 0, info) ||
        ft_set_stat_int(content[i], METEOR_STRIKE_THREE_TARGETS_D_KEY, &(info->bufs.meteor_strike.three_targets_d), 0, info) ||
        ft_set_stat_int(content[i], METEOR_STRIKE_FOUR_TARGETS_D_KEY, &(info->bufs.meteor_strike.four_targets_d), 0, info) ||
        ft_set_stat_int(content[i], METEOR_STRIKE_FIVE_TARGETS_D_KEY, &(info->bufs.meteor_strike.five_targets_d), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_DURATION_KEY, &(info->bufs.lightning_strike.duration), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_AMOUNT_KEY, &(info->bufs.lightning_strike.amount), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_DISTANCE_KEY, &(info->bufs.lightning_strike.distance), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_DICE_AMOUNT_KEY, &(info->bufs.lightning_strike.dice_amount), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_DICE_FACES_KEY, &(info->bufs.lightning_strike.dice_faces), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY, &(info->bufs.lightning_strike.extra_damage), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKEV2_DURATION_KEY, &(info->bufs.lightning_strikeV2.duration), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKEV2_AMOUNT_KEY, &(info->bufs.lightning_strikeV2.amount), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKEV2_DISTANCE_KEY, &(info->bufs.lightning_strikeV2.distance), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY, &(info->bufs.lightning_strikeV2.dice_amount), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKEV2_DICE_FACES_KEY, &(info->bufs.lightning_strikeV2.dice_faces), 0, info) ||
        ft_set_stat_int(content[i], LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY, &(info->bufs.lightning_strikeV2.extra_damage), 0, info) ||
        ft_set_stat_int(content[i], EARTH_POUNCE_ACTIVE_KEY, &(info->bufs.earth_pounce.active), 0, info) ||
        ft_set_stat_int(content[i], EARTH_POUNCE_BASE_DAMAGE_KEY, &(info->bufs.earth_pounce.base_damage), 0, info) ||
        ft_set_stat_int(content[i], ARCANE_POUNCE_ACTIVE_KEY, &(info->bufs.arcane_pounce.active), 0, info) ||
        ft_set_stat_int(content[i], ARCANE_POUNCE_EREA_DAMAGE_KEY, &(info->bufs.arcane_pounce.erea_damage), 0, info) ||
        ft_set_stat_int(content[i], ARCANE_POUNCE_MAGIC_DAMAGE_KEY, &(info->bufs.arcane_pounce.magic_damage), 0, info) ||
        ft_set_stat_int(content[i], FROST_BREATH_ACTIVE_KEY, &(info->bufs.frost_breath.active), 0, info) ||
        ft_set_stat_int(content[i], FROST_BREATH_DAMAGE_KEY, &(info->bufs.frost_breath.damage), 0, info))
    {
        return (0);
    }
    return (1);
}

static int handle_set_stat(char *content_i, size_t key_len, char ***target_field, t_char *info)
{
    *target_field = ft_set_stats_con_targets(content_i, key_len, *target_field, info);
    if (DEBUG == 1)
        ft_printf("printing %s", *target_field);
    if (*target_field == NULL)
        return (-1);
    return (0);
}

static int ft_set_stats_string(t_char *info, char **content, int i)
{
	if (ft_strncmp(content[i], CONC_TARGETS_KEY, ft_strlen(CONC_TARGETS_KEY)) == 0)
        return (handle_set_stat(content[i], ft_strlen(CONC_TARGETS_KEY), &info->concentration.targets, info));
	if (ft_strncmp(content[i], HUNTERS_MARK_CASTER_KEY, ft_strlen(HUNTERS_MARK_CASTER_KEY)) == 0)
        return (handle_set_stat(content[i], ft_strlen(HUNTERS_MARK_CASTER_KEY), &info->debufs.hunters_mark.caster_name, info));
	if (ft_strncmp(content[i], METEOR_STRIKE_TARGET_KEY, ft_strlen(METEOR_STRIKE_TARGET_KEY)) == 0)
        return (handle_set_stat(content[i], ft_strlen(METEOR_STRIKE_TARGET_KEY), &info->bufs.meteor_strike.target_id, info));
	if (ft_strncmp(content[i], EARTH_POUNCE_TARGET_ID_KEY, ft_strlen(EARTH_POUNCE_TARGET_ID_KEY)) == 0)
		return (handle_set_stat(content[i], ft_strlen(EARTH_POUNCE_TARGET_ID_KEY), &info->bufs.earth_pounce.target_id, info));
	if (ft_strncmp(content[i], ARCANE_POUNCE_TARGET_ID_KEY, ft_strlen(ARCANE_POUNCE_TARGET_ID_KEY)) == 0)
		return (handle_set_stat(content[i], ft_strlen(ARCANE_POUNCE_TARGET_ID_KEY), &info->bufs.arcane_pounce.target_id, info));
	if (ft_strncmp(content[i], FROST_BREATH_TARGET_ID_KEY, ft_strlen(FROST_BREATH_TARGET_ID_KEY)))
		return (handle_set_stat(content[i], ft_strlen(FROST_BREATH_TARGET_ID_KEY), &info->bufs.frost_breath.target_id, info));
    return (1);
}

int ft_set_stats(t_char *info, char **content)
{
    int error;
    int i;

	i = 0;
    while (content[i])
    {
		if (DEBUG == 1)
			ft_printf(content[i]);
        if (ft_set_stats_1(info, content, i) == 0)
        {
            i++;
            continue ;
        }
        if (ft_set_stats_2(info, content, i) == 0)
        {
            i++;
            continue ;
        }
        error = ft_set_stats_string(info, content, i);
        if (error <= 0)
        {
            if (error == 0)
            {
                i++;
                continue ;
            }
            else if (error < 0)
                return (1);
        }
        else
        {
            ft_printf_fd(2, "1-Something is wrong with the save file for %s at the line: %s, please reinitialize the save\n", info->name, content[i]);
            info->flags.error = 1;
            return (1);
        }
        i++;
    }
    return (0);
}
