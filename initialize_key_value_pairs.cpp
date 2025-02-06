#include "key_list.hpp"
#include "dnd_tools.hpp"
#include "treeNode.hpp"

#define X(name, value) const char* name = value; const int name##_LEN = sizeof(value) - 1;
KEY_LIST
#undef X

void initialize_stat_key_value_pairs(ft_sharedptr<t_char>& info)
{
    TreeNode* node = *ft_return_main_treeNode();
    node->insert(HEALTH_KEY, &info->stats.health, -1);
    node->insert(TEMP_HP_KEY, &info->stats.temp_hp, -1);
    node->insert(STR_KEY, &info->stats.str, -1);
    node->insert(DEX_KEY, &info->stats.dex, -1);
    node->insert(CON_KEY, &info->stats.con, -1);
    node->insert(INT_KEY, &info->stats.inte, -1);
    node->insert(WIS_KEY, &info->stats.wis, -1);
    node->insert(CHA_KEY, &info->stats.cha, -1);
    node->insert(TURN_KEY, &info->stats.turn, -1);
    node->insert(INITIATIVE_KEY, &info->initiative, -1);
    node->insert(BLESS_DUR_KEY, &info->bufs.bless.duration, 0);
    node->insert(PHASE_KEY, &info->stats.phase, -1);
    node->insert(LIGHTNING_STRIKE_DUR_KEY, &info->bufs.lightning_strike.duration, 0);
    node->insert(PROTECTIVE_WINDS_DUR_KEY, &info->bufs.protective_winds.duration, 0);
    node->insert(LEVEL_1_AVAILABLE_KEY, &info->spell_slots.level_1.available, -1);
    node->insert(LEVEL_1_TOTAL_KEY, &info->spell_slots.level_1.total, -1);
    node->insert(LEVEL_1_LEVEL_KEY, &info->spell_slots.level_1.level, -1);
    node->insert(LEVEL_1_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_1.replenishing_slot, -1);
    node->insert(LEVEL_2_AVAILABLE_KEY, &info->spell_slots.level_2.available, -1);
    node->insert(LEVEL_2_TOTAL_KEY, &info->spell_slots.level_2.total, -1);
    node->insert(LEVEL_2_LEVEL_KEY, &info->spell_slots.level_2.level, -1);
    node->insert(LEVEL_2_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_2.replenishing_slot, -1);
    node->insert(LEVEL_3_AVAILABLE_KEY, &info->spell_slots.level_3.available, -1);
    node->insert(LEVEL_3_TOTAL_KEY, &info->spell_slots.level_3.total, -1);
    node->insert(LEVEL_3_LEVEL_KEY, &info->spell_slots.level_3.level, -1);
    node->insert(LEVEL_3_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_3.replenishing_slot, -1);
    node->insert(LEVEL_4_AVAILABLE_KEY, &info->spell_slots.level_4.available, -1);
    node->insert(LEVEL_4_TOTAL_KEY, &info->spell_slots.level_4.total, -1);
    node->insert(LEVEL_4_LEVEL_KEY, &info->spell_slots.level_4.level, -1);
    node->insert(LEVEL_4_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_4.replenishing_slot, -1);
    node->insert(LEVEL_5_AVAILABLE_KEY, &info->spell_slots.level_5.available, -1);
    node->insert(LEVEL_5_TOTAL_KEY, &info->spell_slots.level_5.total, -1);
    node->insert(LEVEL_5_LEVEL_KEY, &info->spell_slots.level_5.level, -1);
    node->insert(LEVEL_5_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_5.replenishing_slot, -1);
    node->insert(LEVEL_6_AVAILABLE_KEY, &info->spell_slots.level_6.available, -1);
    node->insert(LEVEL_6_TOTAL_KEY, &info->spell_slots.level_6.total, -1);
    node->insert(LEVEL_6_LEVEL_KEY, &info->spell_slots.level_6.level, -1);
    node->insert(LEVEL_6_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_6.replenishing_slot, -1);
    node->insert(LEVEL_7_AVAILABLE_KEY, &info->spell_slots.level_7.available, -1);
    node->insert(LEVEL_7_TOTAL_KEY, &info->spell_slots.level_7.total, -1);
    node->insert(LEVEL_7_LEVEL_KEY, &info->spell_slots.level_7.level, -1);
    node->insert(LEVEL_7_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_7.replenishing_slot, -1);
    node->insert(LEVEL_8_AVAILABLE_KEY, &info->spell_slots.level_8.available, -1);
    node->insert(LEVEL_8_TOTAL_KEY, &info->spell_slots.level_8.total, -1);
    node->insert(LEVEL_8_LEVEL_KEY, &info->spell_slots.level_8.level, -1);
    node->insert(LEVEL_8_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_8.replenishing_slot, -1);
    node->insert(LEVEL_9_AVAILABLE_KEY, &info->spell_slots.level_9.available, -1);
    node->insert(LEVEL_9_TOTAL_KEY, &info->spell_slots.level_9.total, -1);
    node->insert(LEVEL_9_LEVEL_KEY, &info->spell_slots.level_9.level, -1);
    node->insert(LEVEL_9_REPLENISHING_SLOT_KEY,
			&info->spell_slots.level_9.replenishing_slot, -1);
    node->insert(WARLOCK_AVAILABLE_KEY, &info->spell_slots.warlock.available, -1);
    node->insert(WARLOCK_TOTAL_KEY, &info->spell_slots.warlock.total, -1);
    node->insert(WARLOCK_LEVEL_KEY, &info->spell_slots.warlock.level, -1);
    node->insert(WARLOCK_REPLENISHING_SLOT_KEY,
			&info->spell_slots.warlock.replenishing_slot, -1);
    node->insert(ACID_RESISTANCE_KEY, &info->c_resistance.acid, -501);
    node->insert(BLUDGEONING_RESISTANCE_KEY, &info->c_resistance.bludgeoning, -501);
    node->insert(COLD_RESISTANCE_KEY, &info->c_resistance.cold, -501);
    node->insert(FIRE_RESISTANCE_KEY, &info->c_resistance.fire, -501);
    node->insert(FORCE_RESISTANCE_KEY, &info->c_resistance.force, -501);
    node->insert(LIGHTNING_RESISTANCE_KEY, &info->c_resistance.lightning, -501);
    node->insert(NECROTIC_RESISTANCE_KEY, &info->c_resistance.necrotic, -501);
    node->insert(PIERCING_RESISTANCE_KEY, &info->c_resistance.piercing, -501);
    node->insert(POISON_RESISTANCE_KEY, &info->c_resistance.poison, -501);
    node->insert(PSYCHIC_RESISTANCE_KEY, &info->c_resistance.psychic, -501);
    node->insert(RADIANT_RESISTANCE_KEY, &info->c_resistance.radiant, -501);
    node->insert(SLASHING_RESISTANCE_KEY, &info->c_resistance.slashing, -501);
    node->insert(THUNDER_RESISTANCE_KEY, &info->c_resistance.thunder, -501);
    node->insert(CONCENTRATION_KEY, &info->concentration.concentration, 0);
    node->insert(CONC_SPELL_ID_KEY, &info->concentration.spell_id, 0);
    node->insert(CONC_DICE_AMOUNT_KEY, &info->concentration.dice_amount_mod, 0);
    node->insert(CONC_DICE_FACES_KEY, &info->concentration.dice_faces_mod, 0);
    node->insert(CONC_BASE_MOD_KEY, &info->concentration.base_mod, 0);
    node->insert(CONC_DURATION_KEY, &info->concentration.duration, 0);
    node->insert(HUNTERS_MARK_AMOUNT_KEY, &info->debufs.hunters_mark.amount, 0);
    node->insert(CHAOS_ARMOR_DURATION_KEY, &info->bufs.chaos_armor.duration, 0);
    node->insert(PRONE_KEY, &info->flags.prone, 0);
    node->insert(BLINDED_KEY, &info->debufs.blinded.duration, 0);
    node->insert(FLAME_GEYSER_DURATION_KEY, &info->bufs.flame_geyser.duration, 0);
    node->insert(FLAME_GEYSER_AMOUNT_KEY, &info->bufs.flame_geyser.amount, 0);
    node->insert(FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY, &info->bufs.flame_geyser.close_to_tower_d, 0);
    node->insert(FLAME_GEYSER_TOWER_EXPLODE_D_KEY, &info->bufs.flame_geyser.tower_explode_d, 0);
    node->insert(METEOR_STRIKE_DURATION_KEY, &info->bufs.meteor_strike.duration, 0);
    node->insert(METEOR_STRIKE_ONE_TARGET_D_KEY, &info->bufs.meteor_strike.one_target_d, 0);
    node->insert(METEOR_STRIKE_TWO_TARGETS_D_KEY, &info->bufs.meteor_strike.two_targets_d, 0);
    node->insert(METEOR_STRIKE_THREE_TARGETS_D_KEY, &info->bufs.meteor_strike.three_targets_d, 0);
    node->insert(METEOR_STRIKE_FOUR_TARGETS_D_KEY, &info->bufs.meteor_strike.four_targets_d, 0);
    node->insert(METEOR_STRIKE_FIVE_TARGETS_D_KEY, &info->bufs.meteor_strike.five_targets_d, 0);
    node->insert(LIGHTNING_STRIKE_DURATION_KEY, &info->bufs.lightning_strike.duration, 0);
    node->insert(LIGHTNING_STRIKE_AMOUNT_KEY, &info->bufs.lightning_strike.amount, 0);
    node->insert(LIGHTNING_STRIKE_DISTANCE_KEY, &info->bufs.lightning_strike.distance, 0);
    node->insert(LIGHTNING_STRIKE_DICE_AMOUNT_KEY, &info->bufs.lightning_strike.dice_amount, 0);
    node->insert(LIGHTNING_STRIKE_DICE_FACES_KEY, &info->bufs.lightning_strike.dice_faces, 0);
    node->insert(LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY, &info->bufs.lightning_strike.extra_damage, 0);
    node->insert(LIGHTNING_STRIKEV2_DURATION_KEY, &info->bufs.lightning_strikeV2.duration, 0);
    node->insert(LIGHTNING_STRIKEV2_AMOUNT_KEY, &info->bufs.lightning_strikeV2.amount, 0);
    node->insert(LIGHTNING_STRIKEV2_DISTANCE_KEY, &info->bufs.lightning_strikeV2.distance, 0);
    node->insert(LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY,
			&info->bufs.lightning_strikeV2.dice_amount, 0);
    node->insert(LIGHTNING_STRIKEV2_DICE_FACES_KEY, &info->bufs.lightning_strikeV2.dice_faces, 0);
    node->insert(LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY,
			&info->bufs.lightning_strikeV2.extra_damage, 0);
    node->insert(EARTH_POUNCE_ACTIVE_KEY, &info->bufs.earth_pounce.active, 0);
    node->insert(EARTH_POUNCE_BASE_DAMAGE_KEY, &info->bufs.earth_pounce.base_damage, 0);
    node->insert(ARCANE_POUNCE_ACTIVE_KEY, &info->bufs.arcane_pounce.active, 0);
    node->insert(ARCANE_POUNCE_EREA_DAMAGE_KEY, &info->bufs.arcane_pounce.erea_damage, 0);
    node->insert(ARCANE_POUNCE_MAGIC_DAMAGE_KEY, &info->bufs.arcane_pounce.magic_damage, 0);
    node->insert(FROST_BREATH_ACTIVE_KEY, &info->bufs.frost_breath.active, 0);
    node->insert(FROST_BREATH_DAMAGE_KEY, &info->bufs.frost_breath.damage, 0);
    node->insert(REACTION_USED_KEY, &info->flags.reaction_used, 0);
    node->insert(BUFF_BLESS_BASE_MOD_KEY, &info->bufs.bless.base_mod, 0);
    node->insert(BUFF_BLESS_DURATION_KEY, &info->bufs.bless.duration, 0);
    node->insert(BUFF_BLESS_DICE_FACES_MOD_KEY, &info->bufs.bless.dice_faces_mod, 0);
    node->insert(BUFF_BLESS_DICE_AMOUNT_MOD_KEY, &info->bufs.bless.dice_amount_mod, 0);
	node->insert(CONC_TARGETS_KEY, &info->concentration.targets);
	node->insert(HUNTERS_MARK_CASTER_KEY, &info->debufs.hunters_mark.caster_name);
	node->insert(METEOR_STRIKE_TARGET_KEY, &info->bufs.meteor_strike.target_id);
	node->insert(FROST_BREATH_TARGET_ID_KEY, &info->bufs.frost_breath.target_id);
	node->insert(ARCANE_POUNCE_TARGET_ID_KEY, &info->bufs.arcane_pounce.target_id);
	node->insert(EARTH_POUNCE_TARGET_ID_KEY, &info->bufs.earth_pounce.target_id);
	node->insert(BUFF_BLESS_CASTER_NAME_KEY, &info->bufs.bless.caster_name);
	return ;
}
