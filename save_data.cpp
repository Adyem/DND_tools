#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

static void ft_npc_write_spell_slots(t_char *info, ft_file &file)
{
    file.printf("%s%i\n", LEVEL_1_AVAILABLE_KEY, info->spell_slots.level_1.available);
    file.printf("%s%i\n", LEVEL_1_TOTAL_KEY, info->spell_slots.level_1.total);
    file.printf("%s%i\n", LEVEL_1_LEVEL_KEY, info->spell_slots.level_1.level);
    file.printf("%s%i\n", LEVEL_1_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_1.replenishing_slot);
    file.printf("%s%i\n", LEVEL_2_AVAILABLE_KEY, info->spell_slots.level_2.available);
    file.printf("%s%i\n", LEVEL_2_TOTAL_KEY, info->spell_slots.level_2.total);
    file.printf("%s%i\n", LEVEL_2_LEVEL_KEY, info->spell_slots.level_2.level);
    file.printf("%s%i\n", LEVEL_2_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_2.replenishing_slot);
    file.printf("%s%i\n", LEVEL_3_AVAILABLE_KEY, info->spell_slots.level_3.available);
    file.printf("%s%i\n", LEVEL_3_TOTAL_KEY, info->spell_slots.level_3.total);
    file.printf("%s%i\n", LEVEL_3_LEVEL_KEY, info->spell_slots.level_3.level);
    file.printf("%s%i\n", LEVEL_3_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_3.replenishing_slot);
    file.printf("%s%i\n", LEVEL_4_AVAILABLE_KEY, info->spell_slots.level_4.available);
    file.printf("%s%i\n", LEVEL_4_TOTAL_KEY, info->spell_slots.level_4.total);
    file.printf("%s%i\n", LEVEL_4_LEVEL_KEY, info->spell_slots.level_4.level);
    file.printf("%s%i\n", LEVEL_4_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_4.replenishing_slot);
    file.printf("%s%i\n", LEVEL_5_AVAILABLE_KEY, info->spell_slots.level_5.available);
    file.printf("%s%i\n", LEVEL_5_TOTAL_KEY, info->spell_slots.level_5.total);
    file.printf("%s%i\n", LEVEL_5_LEVEL_KEY, info->spell_slots.level_5.level);
    file.printf("%s%i\n", LEVEL_5_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_5.replenishing_slot);
    file.printf("%s%i\n", LEVEL_6_AVAILABLE_KEY, info->spell_slots.level_6.available);
    file.printf("%s%i\n", LEVEL_6_TOTAL_KEY, info->spell_slots.level_6.total);
    file.printf("%s%i\n", LEVEL_6_LEVEL_KEY, info->spell_slots.level_6.level);
    file.printf("%s%i\n", LEVEL_6_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_6.replenishing_slot);
    file.printf("%s%i\n", LEVEL_7_AVAILABLE_KEY, info->spell_slots.level_7.available);
    file.printf("%s%i\n", LEVEL_7_TOTAL_KEY, info->spell_slots.level_7.total);
    file.printf("%s%i\n", LEVEL_7_LEVEL_KEY, info->spell_slots.level_7.level);
    file.printf("%s%i\n", LEVEL_7_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_7.replenishing_slot);
    file.printf("%s%i\n", LEVEL_8_AVAILABLE_KEY, info->spell_slots.level_8.available);
    file.printf("%s%i\n", LEVEL_8_TOTAL_KEY, info->spell_slots.level_8.total);
    file.printf("%s%i\n", LEVEL_8_LEVEL_KEY, info->spell_slots.level_8.level);
    file.printf("%s%i\n", LEVEL_8_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_8.replenishing_slot);
    file.printf("%s%i\n", LEVEL_9_AVAILABLE_KEY, info->spell_slots.level_9.available);
    file.printf("%s%i\n", LEVEL_9_TOTAL_KEY, info->spell_slots.level_9.total);
    file.printf("%s%i\n", LEVEL_9_LEVEL_KEY, info->spell_slots.level_9.level);
    file.printf("%s%i\n", LEVEL_9_REPLENISHING_SLOT_KEY,
			info->spell_slots.level_9.replenishing_slot);
    file.printf("%s%i\n", WARLOCK_AVAILABLE_KEY, info->spell_slots.warlock.available);
    file.printf("%s%i\n", WARLOCK_TOTAL_KEY, info->spell_slots.warlock.total);
    file.printf("%s%i\n", WARLOCK_LEVEL_KEY, info->spell_slots.warlock.level);
    file.printf("%s%i\n", WARLOCK_REPLENISHING_SLOT_KEY,
			info->spell_slots.warlock.replenishing_slot);
}


static void ft_npc_write_file_1(t_char *info, t_stats *stats, ft_file &file)
{
    file.printf("%s%i\n", HEALTH_KEY, stats->health);
    file.printf("%s%i\n", TEMP_HP_KEY, stats->temp_hp);
    file.printf("%s%i\n", STR_KEY, stats->str);
    file.printf("%s%i\n", DEX_KEY, stats->dex);
    file.printf("%s%i\n", CON_KEY, stats->con);
    file.printf("%s%i\n", INT_KEY, stats->inte);
    file.printf("%s%i\n", WIS_KEY, stats->wis);
    file.printf("%s%i\n", CHA_KEY, stats->cha);
    file.printf("%s%i\n", TURN_KEY, stats->turn);
    file.printf("%s%i\n", PHASE_KEY, stats->phase);
    file.printf("%s%i\n", INITIATIVE_KEY, info->initiative);
    file.printf("%s%i\n", BLESS_DUR_KEY, info->bufs.bless.duration);
    file.printf("%s%i\n", PROTECTIVE_WINDS_DUR_KEY,
			info->bufs.protective_winds.duration);
	return ;
}

static void ft_npc_write_file_double_char(const char *msg, char **targets, ft_file &file,
											t_char *info)
{
    int i = 0;
    if (targets)
    {
        while (targets[i])
        {
            if (DEBUG == 1)
                pf_printf_fd(1, "saving array %s %s%s\n", info->name, msg, targets[i]);
            file.printf("%s%s\n", msg, targets[i]);
            i++;
        }
    }
	return ;
}

static void ft_npc_write_file_2(t_char *info, t_resistance *resistance, ft_file &file)
{
    file.printf("%s%i\n", ACID_RESISTANCE_KEY, resistance->acid);
    file.printf("%s%i\n", BLUDGEONING_RESISTANCE_KEY, resistance->bludgeoning);
    file.printf("%s%i\n", COLD_RESISTANCE_KEY, resistance->cold);
    file.printf("%s%i\n", FIRE_RESISTANCE_KEY, resistance->fire);
    file.printf("%s%i\n", FORCE_RESISTANCE_KEY, resistance->force);
    file.printf("%s%i\n", LIGHTNING_RESISTANCE_KEY, resistance->lightning);
    file.printf("%s%i\n", NECROTIC_RESISTANCE_KEY, resistance->necrotic);
    file.printf("%s%i\n", PIERCING_RESISTANCE_KEY, resistance->piercing);
    file.printf("%s%i\n", POISON_RESISTANCE_KEY, resistance->poison);
    file.printf("%s%i\n", PSYCHIC_RESISTANCE_KEY, resistance->psychic);
    file.printf("%s%i\n", RADIANT_RESISTANCE_KEY, resistance->radiant);
    file.printf("%s%i\n", SLASHING_RESISTANCE_KEY, resistance->slashing);
    file.printf("%s%i\n", THUNDER_RESISTANCE_KEY, resistance->thunder);
    file.printf("%s%i\n", CONCENTRATION_KEY, info->concentration.concentration);
    file.printf("%s%i\n", CONC_SPELL_ID_KEY, info->concentration.spell_id);
    file.printf("%s%i\n", CONC_DICE_AMOUNT_KEY, info->concentration.dice_amount_mod);
    file.printf("%s%i\n", CONC_DICE_FACES_KEY, info->concentration.dice_faces_mod);
    file.printf("%s%i\n", CONC_BASE_MOD_KEY, info->concentration.base_mod);
    file.printf("%s%i\n", CONC_DURATION_KEY, info->concentration.duration);
    ft_npc_write_file_double_char(CONC_TARGETS_KEY,
			info->concentration.targets, file, info);
    file.printf("%s%i\n", HUNTERS_MARK_AMOUNT_KEY,
			info->debufs.hunters_mark.amount);
    ft_npc_write_file_double_char(HUNTERS_MARK_CASTER_KEY,
			info->debufs.hunters_mark.caster_name, file, info);
    file.printf("%s%i\n", CHAOS_ARMOR_DURATION_KEY,
			info->bufs.chaos_armor.duration);
    file.printf("%s%i\n", PRONE_KEY,
			info->flags.prone);
    file.printf("%s%i\n", BLINDED_KEY,
			info->debufs.blinded.duration);
    file.printf("%s%i\n", FLAME_GEYSER_DURATION_KEY,
			info->bufs.flame_geyser.duration);
    file.printf("%s%i\n", FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY,
			info->bufs.flame_geyser.close_to_tower_d);
    file.printf("%s%i\n", FLAME_GEYSER_TOWER_EXPLODE_D_KEY,
			info->bufs.flame_geyser.tower_explode_d);
    file.printf("%s%i\n", FLAME_GEYSER_AMOUNT_KEY,
			info->bufs.flame_geyser.amount);
    file.printf("%s%i\n", METEOR_STRIKE_DURATION_KEY,
			info->bufs.meteor_strike.duration);
    file.printf("%s%i\n", METEOR_STRIKE_ONE_TARGET_D_KEY,
			info->bufs.meteor_strike.one_target_d);
    file.printf("%s%i\n", METEOR_STRIKE_TWO_TARGETS_D_KEY,
			info->bufs.meteor_strike.two_targets_d);
    file.printf("%s%i\n", METEOR_STRIKE_THREE_TARGETS_D_KEY,
			info->bufs.meteor_strike.three_targets_d);
    file.printf("%s%i\n", METEOR_STRIKE_FOUR_TARGETS_D_KEY,
			info->bufs.meteor_strike.four_targets_d);
    file.printf("%s%i\n", METEOR_STRIKE_FIVE_TARGETS_D_KEY,
			info->bufs.meteor_strike.five_targets_d);
    file.printf("%s%i\n", LIGHTNING_STRIKE_DURATION_KEY,
			info->bufs.lightning_strike.duration);
    file.printf("%s%i\n", LIGHTNING_STRIKE_AMOUNT_KEY,
			info->bufs.lightning_strike.amount);
    file.printf("%s%i\n", LIGHTNING_STRIKE_DISTANCE_KEY,
			info->bufs.lightning_strike.distance);
    file.printf("%s%i\n", LIGHTNING_STRIKE_DICE_AMOUNT_KEY,
			info->bufs.lightning_strike.dice_amount);
    file.printf("%s%i\n", LIGHTNING_STRIKE_DICE_FACES_KEY,
			info->bufs.lightning_strike.dice_faces);
    file.printf("%s%i\n", LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY,
			info->bufs.lightning_strike.extra_damage);
    file.printf("%s%i\n", LIGHTNING_STRIKEV2_DURATION_KEY,
			info->bufs.lightning_strikeV2.duration);
    file.printf("%s%i\n", LIGHTNING_STRIKEV2_AMOUNT_KEY,
			info->bufs.lightning_strikeV2.amount);
    file.printf("%s%i\n", LIGHTNING_STRIKEV2_DISTANCE_KEY,
			info->bufs.lightning_strikeV2.distance);
    file.printf("%s%i\n", LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY,
			info->bufs.lightning_strikeV2.dice_amount);
    file.printf("%s%i\n", LIGHTNING_STRIKEV2_DICE_FACES_KEY,
			info->bufs.lightning_strikeV2.dice_faces);
    file.printf("%s%i\n", LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY,
			info->bufs.lightning_strikeV2.extra_damage);
    file.printf("%s%i\n", EARTH_POUNCE_ACTIVE_KEY,
			info->bufs.earth_pounce.active);
    file.printf("%s%i\n", EARTH_POUNCE_BASE_DAMAGE_KEY,
			info->bufs.earth_pounce.base_damage);
    file.printf("%s%i\n", ARCANE_POUNCE_ACTIVE_KEY,
			info->bufs.arcane_pounce.active);
    file.printf("%s%i\n", ARCANE_POUNCE_EREA_DAMAGE_KEY,
			info->bufs.arcane_pounce.erea_damage);
    file.printf("%s%i\n", ARCANE_POUNCE_MAGIC_DAMAGE_KEY,
			info->bufs.arcane_pounce.magic_damage);
    file.printf("%s%i\n", FROST_BREATH_ACTIVE_KEY,
			info->bufs.frost_breath.active);
    file.printf("%s%i\n", FROST_BREATH_DAMAGE_KEY,
			info->bufs.frost_breath.damage);
    if (info->bufs.meteor_strike.target_id)
        file.printf("%s%s\n", METEOR_STRIKE_TARGET_KEY,
				info->bufs.meteor_strike.target_id);
    if (info->bufs.frost_breath.target_id)
        file.printf("%s%s\n", FROST_BREATH_TARGET_ID_KEY,
				info->bufs.frost_breath.target_id);
    if (info->bufs.arcane_pounce.target_id)
        file.printf("%s%s\n", ARCANE_POUNCE_TARGET_ID_KEY,
				info->bufs.arcane_pounce.target_id);
    if (info->bufs.earth_pounce.target_id)
        file.printf("%s%s\n", EARTH_POUNCE_TARGET_ID_KEY,
				info->bufs.earth_pounce.target_id);
    file.printf("%s%i\n", REACTION_USED_KEY, info->flags.reaction_used);
	return ;
}

void ft_npc_write_file(t_char *info, t_stats *stats, t_resistance *resistance, ft_file &file)
{
    if (file.get_error_code())
    {
        pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
				file.get_error_message());
        return;
    }
	if (DEBUG == 1)
        pf_printf("fd = %i\n", file.get_fd());
	if (info->flags.alreaddy_saved)
        return;
	if (DEBUG == 1)
		pf_printf("saving %s %i\n", info->name, stats->health);
    ft_npc_write_file_1(info, stats, file);
    ft_npc_write_file_2(info, resistance, file);
	ft_npc_write_spell_slots(info, file);
    info->flags.alreaddy_saved = 1;
	return ;
}
