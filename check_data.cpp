#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <climits>

static int check_range(const int &value, const int &min, const int &max, const char *name,
		const char *field_name)
{
    if (value < min || value > max)
    {
        pf_printf("%s: %s value (%d) out of bounds (%d to %d)\n", name, field_name,
				value, min, max);
        return (1);
    }
    return (0);
}

static int check_flag(int value, const char *name, const char *field_name)
{
    if (value != 0 && value != 1)
    {
        pf_printf("%s: %s flag value (%d) out of bounds (0 or 1)\n", name, field_name, value);
        return (1);
    }
    return (0);
}

static int check_stats(t_char * info)
{
    int error = 0;
    error += check_range(info->stats.health, 0, info->dstats.health, info->name, "health");
    error += check_range(info->stats.temp_hp, 0, 5000, info->name, "temp_hp");
    error += check_range(info->stats.str, 0, 30, info->name, "strength");
    error += check_range(info->stats.dex, 0, 30, info->name, "dexterity");
    error += check_range(info->stats.con, 0, 30, info->name, "constitution");
    error += check_range(info->stats.inte, 0, 30, info->name, "intelligence");
    error += check_range(info->stats.wis, 0, 30, info->name, "wisdom");
    error += check_range(info->stats.cha, 0, 30, info->name, "charisma");
    error += check_range(info->stats.turn, 0, 30, info->name, "turn");
    error += check_range(info->stats.phase, 0, 30, info->name, "phase");
    return (error);
}

static int check_resistances(t_char * info)
{
    int error = 0;
    error += check_range(info->c_resistance.bludgeoning, -500, 500, info->name,
			"bludgeoning resistance");
    error += check_range(info->c_resistance.cold, -500, 500, info->name,
			"cold resistance");
    error += check_range(info->c_resistance.fire, -500, 500, info->name,
			"fire resistance");
    error += check_range(info->c_resistance.force, -500, 500, info->name,
			"force resistance");
    error += check_range(info->c_resistance.lightning, -500, 500, info->name,
			"lightning resistance");
    error += check_range(info->c_resistance.necrotic, -500, 500, info->name,
			"necrotic resistance");
    error += check_range(info->c_resistance.piercing, -500, 500, info->name,
			"piercing resistance");
    error += check_range(info->c_resistance.poison, -500, 500, info->name,
			"poison resistance");
    error += check_range(info->c_resistance.psychic, -500, 500, info->name,
			"psychic resistance");
    error += check_range(info->c_resistance.radiant, -500, 500, info->name,
			"radiant resistance");
    error += check_range(info->c_resistance.slashing, -500, 500, info->name,
			"slashing resistance");
    error += check_range(info->c_resistance.thunder, -500, 500, info->name,
			"thunder resistance");
    error += check_range(info->c_resistance.acid, -500, 500, info->name,
			"acid resistance");
    return (error);
}

static int check_concentration(t_char * info)
{
    int error = 0;
    error += check_range(info->concentration.concentration, 0, INT_MAX, info->name,
			"concentration");
    error += check_range(info->concentration.spell_id, 0, INT_MAX, info->name,
			"spell_id");
    error += check_range(info->concentration.dice_amount_mod, 0, INT_MAX, info->name,
			"dice_amount_mod");
    error += check_range(info->concentration.dice_faces_mod, 0, INT_MAX, info->name,
			"dice_faces_mod");
    error += check_range(info->concentration.base_mod, 0, INT_MAX, info->name, "base_mod");
    if (info->concentration.duration < -1)
    {
        pf_printf("%s: duration (%d) is less than -1\n", info->name,
				info->concentration.duration);
        error++;
    }
    return (error);
}

static int check_flags(t_char * info)
{
    int error = 0;
    error += check_flag(info->flags.prone, info->name, "prone");
    error += check_flag(info->flags.reaction_used, info->name, "reaction_used");
    return (error);
}

static int check_debuffs(t_char * info)
{
    int error = 0;
    error += check_range(info->debufs.blinded.duration, 0, 50, info->name,
			"blinded debuff duration");
    return (error);
}

static int check_buffs(t_char * info)
{
    int error = 0;
    error += check_range(info->bufs.flame_geyser.duration, 0, 100, info->name,
			"flame geyser duration");
    error += check_range(info->bufs.flame_geyser.close_to_tower_d, 0, 100, info->name,
			"flame geyser close_to_tower_d");
    error += check_range(info->bufs.flame_geyser.tower_explode_d, 0, 100, info->name,
			"flame geyser tower_explode_d");
    error += check_range(info->bufs.flame_geyser.amount, 0, 5, info->name,
			"flame geyser amount");
    error += check_range(info->bufs.meteor_strike.duration, 0, 100, info->name,
			"meteor strike duration");
    error += check_range(info->bufs.meteor_strike.one_target_d, 0, 100, info->name,
			"meteor strike one_target_d");
    error += check_range(info->bufs.meteor_strike.two_targets_d, 0, 100, info->name,
			"meteor strike two_targets_d");
    error += check_range(info->bufs.meteor_strike.three_targets_d, 0, 100, info->name,
			"meteor strike three_targets_d");
    error += check_range(info->bufs.meteor_strike.four_targets_d, 0, 100, info->name,
			"meteor strike four_targets_d");
    error += check_range(info->bufs.meteor_strike.five_targets_d, 0, 100, info->name,
			"meteor strike five_targets_d");
    error += check_range(info->bufs.lightning_strike.duration, 0, 100, info->name,
			"lightning strike duration");
    error += check_range(info->bufs.lightning_strike.amount, 0, 100, info->name,
			"lightning strike amount");
    error += check_range(info->bufs.lightning_strike.distance, 0, 1000, info->name,
			"lightning strike distance");
    error += check_range(info->bufs.lightning_strike.dice_amount, 0, 100, info->name,
			"lightning strike dice_amount");
    error += check_range(info->bufs.lightning_strike.dice_faces, 0, 100, info->name,
			"lightning strike dice_faces");
    error += check_range(info->bufs.lightning_strike.extra_damage, 0, 1000, info->name,
			"lightning strike extra_damage");
    error += check_range(info->bufs.lightning_strikeV2.duration, 0, 100, info->name,
			"lightning strike V2 duration");
    error += check_range(info->bufs.lightning_strikeV2.amount, 0, 100, info->name,
			"lightning strike V2 amount");
    error += check_range(info->bufs.lightning_strikeV2.distance, 0, 1000, info->name,
			"lightning strike V2 distance");
    error += check_range(info->bufs.lightning_strikeV2.dice_amount, 0, 100, info->name,
			"lightning strike V2 dice_amount");
    error += check_range(info->bufs.lightning_strikeV2.dice_faces, 0, 100, info->name,
			"lightning strike V2 dice_faces");
    error += check_range(info->bufs.lightning_strikeV2.extra_damage, 0, 1000, info->name,
			"lightning strike V2 extra_damage");
    error += check_flag(info->bufs.earth_pounce.active, info->name,
			"earth pounce active");
    error += check_range(info->bufs.earth_pounce.base_damage, 0, 1000, info->name,
			"earth pounce base_damage");
    error += check_flag(info->bufs.arcane_pounce.active, info->name,
			"arcane pounce active");
    error += check_range(info->bufs.arcane_pounce.erea_damage, 0, 1000, info->name,
			"arcane pounce area_damage");
    error += check_range(info->bufs.arcane_pounce.magic_damage, 0, 1000, info->name,
			"arcane pounce magic_damage");
	error += check_range(info->bufs.bless.base_mod, 0, 1000, info->name,
			"bless base mod");
	error += check_range(info->bufs.bless.duration, 0, 50, info->name,
			"bless duration");
	error += check_range(info->bufs.bless.dice_faces_mod, 0, 100, info->name,
			"bless dice faces");
	error += check_range(info->bufs.bless.dice_amount_mod, 0, 100, info->name,
			"bless dice amount");
	error += check_range(info->spells.magic_drain.damage_flat, 0, 50, info->name,
			"magic drain flat damage");
	error += check_range(info->spells.magic_drain.damage_dice_amount, 0, 50, info->name,
			"magic drain dice amount");
	error += check_range(info->spells.magic_drain.damage_dice_faces, 0, 50, info->name,
			"magic drain dice faces");
	error += check_range(info->spells.magic_drain.spell_slot_total_level_drain, 0, 50, info->name,
			"magic drain spell slot total level drain");
	error += check_range(info->spells.magic_drain.dex_save, 0, 50, info->name,
			"magic drain dex save");
	error += check_range(info->spells.magic_drain.turns_passed_fron_last_cast, 0, 50, info->name,
			"magic drain turns passed from last cast");
	error += check_range(info->spells.magic_drain.extra_damage_flat, 0, 50, info->name,
			"magic drain extra flat damage");
	error += check_range(info->spells.magic_drain.extra_dice_amount, 0, 50, info->name,
			"magic drain extra dice amount");
	error += check_range(info->spells.magic_drain.extra_dice_faces, 0, 50, info->name,
			"magic drain extra dice faces");
	error += check_range(info->spells.magic_drain.cooldown, 0, 50, info->name,
			"magic drain cooldown");
	error += check_range(info->debufs.magic_drain.damage_flat, 0, 50, info->name,
			"magic drain flat damage (debuff)");
	error += check_range(info->debufs.magic_drain.damage_dice_amount, 0, 50, info->name,
			"magic drain dice amount (debuff)");
	error += check_range(info->debufs.magic_drain.damage_dice_faces, 0, 50, info->name,
			"magic drain dice faces (debuff)");
	error += check_range(info->debufs.magic_drain.spell_slot_total_level_drain, 0, 50, info->name,
			"magic drain spell slot total level drain (debuff)");
	error += check_range(info->debufs.magic_drain.con_save, 0, 50, info->name,
			"magic drain con save (debuff)");
	error += check_range(info->debufs.magic_drain.extra_damage_flat, 0, 50, info->name,
			"magic drain extra flat damage (debuff)");
	error += check_range(info->debufs.magic_drain.extra_dice_amount, 0, 50, info->name,
			"magic drain extra dice amount (debuff)");
	error += check_range(info->debufs.magic_drain.extra_dice_faces, 0, 50, info->name,
			"magic drain extra dice faces (debuff)");
	error += check_range(info->spells.magic_drain.learned, 0, 1, info->name,
			"magic drain learned (spell)");
	return (error);

}

static int check_other_buffs_debuffs(t_char * info)
{
    int error = 0;
    error += check_range(info->bufs.bless.duration, 0, 50, info->name, "bless duration");
    if (info->initiative < -50)
    {
        pf_printf("%s: initiative value (%d) is less than -50\n", info->name, info->initiative);
        error++;
    }
    if (info->bufs.lightning_strike.duration < 0)
    {
        pf_printf("%s: lightning strike duration (%d) is negative\n", info->name,
				info->bufs.lightning_strike.duration);
        error++;
    }
    if (info->debufs.hunters_mark.amount < 0 || info->debufs.hunters_mark.amount
			!= ft_double_char_length(const_cast<const char **>(info->debufs.hunters_mark.caster_name)))
    {
        pf_printf("%s: hunters mark data is not correct\n", info->name);
        error++;
    }
	if (info->debufs.magic_drain.amount < 0 || info->debufs.magic_drain.amount
			!= ft_double_char_length(const_cast<const char **>(info->debufs.magic_drain.caster)))
    {
        pf_printf("%s: magic drain data is not correct\n", info->name);
        error++;
    }
    if (info->bufs.protective_winds.duration < 0)
    {
        pf_printf("%s: protective winds duration (%d) is negative\n", info->name,
				info->bufs.protective_winds.duration);
        error++;
    }
    if (info->bufs.chaos_armor.duration < 0)
    {
        pf_printf("%s: chaos armor duration (%d) is negative\n", info->name,
				info->bufs.chaos_armor.duration);
        error++;
    }
    return (error);
}

static int ft_npc_check_info_2(t_char * info)
{
    int error = 0;
    error += check_resistances(info);
    error += check_concentration(info);
    error += check_flags(info);
    error += check_debuffs(info);
    error += check_buffs(info);
    return (error);
}

static int check_spell_slot(t_char * info, const char *slot_name, t_spell_slot *slot)
{
    int error = 0;

    error += check_flag(slot->replenishing_slot, info->name, "replenishing_slot");
    if (ft_strcmp_dnd(slot_name, "warlock") == 0)
    {
        error += check_range(slot->level, 0, 9, info->name, "warlock_slot_level");
        if (slot->level == 0 && (slot->total != 0 || slot->available != 0))
        {
            error++;
            pf_printf("%s: Warlock slot level is 0, but total (%d) or available " \
					"(%d) slots are not 0\n", info->name, slot->total, slot->available);
        }
    }
    else
    {
        if (slot->level != 0)
        {
            error++;
            pf_printf("%s: Spell slot %s should have level 0, but found %d\n", 
					info->name, slot_name, slot->level);
        }
    }
    error += check_range(slot->total, 0, 9, info->name, "total_slots");
    if (slot->available < 0 || slot->available > slot->total)
    {
        error++;
        pf_printf("%s: Available slots (%d) for %s are out of range (0 to %d)\n",
				info->name, slot->available, slot_name, slot->total);
    }
    return (error);
}

static int check_spell_slots(t_char * info)
{
    int error = 0;
    error += check_spell_slot(info, "level_1", &info->spell_slots.level_1);
    error += check_spell_slot(info, "level_2", &info->spell_slots.level_2);
    error += check_spell_slot(info, "level_3", &info->spell_slots.level_3);
    error += check_spell_slot(info, "level_4", &info->spell_slots.level_4);
    error += check_spell_slot(info, "level_5", &info->spell_slots.level_5);
    error += check_spell_slot(info, "level_6", &info->spell_slots.level_6);
    error += check_spell_slot(info, "level_7", &info->spell_slots.level_7);
    error += check_spell_slot(info, "level_8", &info->spell_slots.level_8);
    error += check_spell_slot(info, "level_9", &info->spell_slots.level_9);
    error += check_spell_slot(info, "warlock", &info->spell_slots.warlock);
    return (error);
}

int ft_npc_check_info(t_char * info)
{
    int error = 0;
    error += check_stats(info);
    error += check_spell_slots(info);
    error += check_other_buffs_debuffs(info);
    error += ft_check_equipment_slots(info);
    error += ft_npc_check_info_2(info);
    if (error)
        pf_printf("%s: Error with the save file, please reinitialize it with the " \
				"correct values\n", info->name);
    return (error);
}
