#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"

int check_range(int value, int min, int max, const char *name, const char *field_name, int *error)
{
    if (value < min || value > max)
	{
        pf_printf("%s: %s value (%d) out of bounds (%d to %d)\n", name, field_name, value, min, max);
        (*error)++;
        return (1);
    }
    return (0);
}

int check_flag(int value, const char *name, const char *field_name, int *error)
{
    if (value != 0 && value != 1)
	{
        pf_printf("%s: %s flag value (%d) out of bounds (0 or 1)\n", name, field_name, value);
        (*error)++;
        return (1);
    }
    return (0);
}

void check_resistances(t_char *info, int *error) 
{
    check_range(info->c_resistance.bludgeoning, -500, 500, info->name,
			"bludgeoning resistance", error);
    check_range(info->c_resistance.cold, -500, 500, info->name,
			"cold resistance", error);
    check_range(info->c_resistance.fire, -500, 500, info->name,
			"fire resistance", error);
    check_range(info->c_resistance.force, -500, 500, info->name,
			"force resistance", error);
    check_range(info->c_resistance.lightning, -500, 500, info->name,
			"lightning resistance", error);
    check_range(info->c_resistance.necrotic, -500, 500, info->name,
			"necrotic resistance", error);
    check_range(info->c_resistance.piercing, -500, 500, info->name,
			"piercing resistance", error);
    check_range(info->c_resistance.poison, -500, 500, info->name,
			"poison resistance", error);
    check_range(info->c_resistance.psychic, -500, 500, info->name,
			"psychic resistance", error);
    check_range(info->c_resistance.radiant, -500, 500, info->name,
			"radiant resistance", error);
    check_range(info->c_resistance.slashing, -500, 500, info->name,
			"slashing resistance", error);
    check_range(info->c_resistance.thunder, -500, 500, info->name,
			"thunder resistance", error);
    check_range(info->c_resistance.acid, -500, 500, info->name,
			"acid resistance", error);
}

void check_concentration(t_char *info, int *error)
{
    if (info->concentration.concentration < 0)
	{
        pf_printf("%s: concentration value (%d) is negative\n", info->name,
				info->concentration.concentration);
        (*error)++;
    }
    if (info->concentration.spell_id < 0)
	{
        pf_printf("%s: spell_id (%d) is negative\n", info->name, info->concentration.spell_id);
        (*error)++;
    }
    if (info->concentration.dice_amount_mod < 0)
	{
        pf_printf("%s: dice_amount_mod (%d) is negative\n", info->name,
				info->concentration.dice_amount_mod);
        (*error)++;
    }
    if (info->concentration.dice_faces_mod < 0)
	{
        pf_printf("%s: dice_faces_mod (%d) is negative\n", info->name,
				info->concentration.dice_faces_mod);
        (*error)++;
    }
    if (info->concentration.base_mod < 0)
	{
        pf_printf("%s: base_mod (%d) is negative\n", info->name, info->concentration.base_mod);
        (*error)++;
    }
    if (info->concentration.duration < -1)
	{
        pf_printf("%s: duration (%d) is less than -1\n", info->name, info->concentration.duration);
        (*error)++;
    }
	return ;
}

void check_flags(t_char *info, int *error)
{
    check_flag(info->flags.prone, info->name,
			"prone", error);
    check_flag(info->flags.reaction_used, info->name,
			"reaction_used", error);
}

void check_debuffs(t_char *info, int *error)
{
    check_range(info->debufs.blinded.duration, 0, 50, info->name,
			"blinded debuff duration", error);
}

void check_buffs(t_char *info, int *error)
{
    check_range(info->bufs.flame_geyser.duration, 0, 100, info->name,
			"flame geyser duration", error);
    check_range(info->bufs.flame_geyser.close_to_tower_d, 0, 100, info->name,
			"flame geyser close_to_tower_d", error);
    check_range(info->bufs.flame_geyser.tower_explode_d, 0, 100, info->name,
			"flame geyser tower_explode_d", error);
    check_range(info->bufs.flame_geyser.amount, 0, 5, info->name,
			"flame geyser amount", error);
    check_range(info->bufs.meteor_strike.duration, 0, 100, info->name,
			"meteor strike duration", error);
    check_range(info->bufs.meteor_strike.one_target_d, 0, 100, info->name,
			"meteor strike one_target_d", error);
    check_range(info->bufs.meteor_strike.two_targets_d, 0, 100, info->name,
			"meteor strike two_targets_d", error);
    check_range(info->bufs.meteor_strike.three_targets_d, 0, 100, info->name,
			"meteor strike three_targets_d", error);
    check_range(info->bufs.meteor_strike.four_targets_d, 0, 100, info->name,
			"meteor strike four_targets_d", error);
    check_range(info->bufs.meteor_strike.five_targets_d, 0, 100, info->name,
			"meteor strike five_targets_d", error);
    check_range(info->bufs.lightning_strike.duration, 0, 100, info->name,
			"lightning strike duration", error);
    check_range(info->bufs.lightning_strike.amount, 0, 100, info->name,
			"lightning strike amount", error);
    check_range(info->bufs.lightning_strike.distance, 0, 1000, info->name,
			"lightning strike distance", error);
    check_range(info->bufs.lightning_strike.dice_amount, 0, 100, info->name,
			"lightning strike dice_amount", error);
    check_range(info->bufs.lightning_strike.dice_faces, 0, 100, info->name,
			"lightning strike dice_faces", error);
    check_range(info->bufs.lightning_strike.extra_damage, 0, 1000, info->name,
			"lightning strike extra_damage", error);
    check_range(info->bufs.lightning_strikeV2.duration, 0, 100, info->name,
			"lightning strike V2 duration", error);
    check_range(info->bufs.lightning_strikeV2.amount, 0, 100, info->name,
			"lightning strike V2 amount", error);
    check_range(info->bufs.lightning_strikeV2.distance, 0, 1000, info->name,
			"lightning strike V2 distance", error);
    check_range(info->bufs.lightning_strikeV2.dice_amount, 0, 100, info->name,
			"lightning strike V2 dice_amount", error);
    check_range(info->bufs.lightning_strikeV2.dice_faces, 0, 100, info->name,
			"lightning strike V2 dice_faces", error);
    check_range(info->bufs.lightning_strikeV2.extra_damage, 0, 1000, info->name,
			"lightning strike V2 extra_damage", error);
    check_range(info->bufs.earth_pounce.active, 0, 1, info->name,
			"earth pounce active", error);
    check_range(info->bufs.earth_pounce.base_damage, 0, 1000, info->name,
			"earth pounce base_damage", error);
    check_range(info->bufs.arcane_pounce.active, 0, 1, info->name,
			"arcane pounce active", error);
    check_range(info->bufs.arcane_pounce.erea_damage, 0, 1000, info->name,
			"arcane pounce area_damage", error);
    check_range(info->bufs.arcane_pounce.magic_damage, 0, 1000, info->name,
			"arcane pounce magic_damage", error);
	return ;
}

int ft_npc_check_info_2(t_char *info)
{
    int error = 0;
    check_resistances(info, &error);
    check_concentration(info, &error);
    check_flags(info, &error);
    check_debuffs(info, &error);
    check_buffs(info, &error);
    return (error);
}

void check_stats(t_char *info, int *error)
{
    check_range(info->stats.health, 0, info->dstats.health, info->name, "health", error);
    check_range(info->stats.temp_hp, 0, 5000, info->name, "temp_hp", error);
    check_range(info->stats.str, 0, 30, info->name, "strength", error);
    check_range(info->stats.dex, 0, 30, info->name, "dexterity", error);
    check_range(info->stats.con, 0, 30, info->name, "constitution", error);
    check_range(info->stats.inte, 0, 30, info->name, "intelligence", error);
    check_range(info->stats.wis, 0, 30, info->name, "wisdom", error);
    check_range(info->stats.cha, 0, 30, info->name, "charisma", error);
    check_range(info->stats.turn, 0, 30, info->name, "turn", error);
    check_range(info->stats.phase, 0, 30, info->name, "phase", error);
}

void check_other_buffs_debuffs(t_char *info, int *error)
{
    check_range(info->bufs.bless.duration, 0, 50, info->name, "bless duration", error);
    if (info->initiative < -50)
	{
        pf_printf("%s: initiative value (%d) is less than -50\n", info->name, info->initiative);
        (*error)++;
    }
    if (info->bufs.lightning_strike.duration < 0)
	{
        pf_printf("%s: lightning strike duration (%d) is negative\n", info->name,
				info->bufs.lightning_strike.duration);
        (*error)++;
    }
    if (info->debufs.hunters_mark.amount < 0 || info->debufs.hunters_mark.amount !=
		ft_double_char_length((const char **)info->debufs.hunters_mark.caster_name))
	{
        pf_printf("%s: hunters mark data is not correct\n", info->name);
        (*error)++;
    }

    if (info->bufs.protective_winds.duration < 0)
	{
        pf_printf("%s: protective winds duration (%d) is negative\n", info->name,
				info->bufs.protective_winds.duration);
        (*error)++;
    }

    if (info->bufs.chaos_armor.duration < 0) {
        pf_printf("%s: chaos armor duration (%d) is negative\n", info->name,
				info->bufs.chaos_armor.duration);
        (*error)++;
    }
	return ;
}

int ft_npc_check_info(t_char *info)
{
    int error = 0;
    check_stats(info, &error);
    check_other_buffs_debuffs(info, &error);
    error += ft_check_equipment_slots(info);
    error += ft_npc_check_info_2(info);
    if (error)
        pf_printf("%s: Error with the save file, please reinitialize it with the " \
				"correct values\n", info->name);
    return (error);
}
