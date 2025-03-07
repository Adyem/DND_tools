#ifndef INITIALIZE_H
# define INITIALIZE_H

# include <stddef.h>
# include "character.hpp"
# include "libft/CPP_class/nullptr.hpp"

static const	t_buff INITIALIZE_T_BUFF =
{
	.target_amount = 0,
	.target = ft_nullptr,
	.spell_id = 0,
	.dice_faces_mod = 0,
	.dice_amount_mod = 0,
	.extra_mod = 0,
	.duration = 0,
	.buff = 0,
	.error = 0,
	.cast_spell = ft_nullptr,
	.spell_name = ft_nullptr,
};

static const	t_saves INITIALIZE_SAVES =
{
	.str = 0,
	.dex = 0,
	.con = 0,
	.inte = 0,
	.wis = 0,
	.cha = 0,
};

static const	t_skills INITIALIZE_SKILLS =
{
	.athletics = 0,
	.acrobatics = 0,
	.sleight_of_hand = 0,
	.stealth = 0,
	.arcana = 0,
	.history = 0,
	.investigation = 0,
	.nature = 0,
	.religion = 0,
	.animal_handling = 0,
	.insight = 0,
	.medicine = 0,
	.perception = 0,
	.survival = 0,
	.deception = 0,
	.intimidation = 0,
	.performance = 0,
	.persuasion = 0,
};

static const	t_resistance INITIALIZE_RESISTANCE =
{
	.acid = 0,
	.bludgeoning = 0,
	.cold = 0,
	.fire = 0,
	.force = 0,
	.lightning = 0,
	.necrotic = 0,
	.piercing = 0,
	.poison = 0,
	.psychic = 0,
	.radiant = 0,
	.slashing = 0,
	.thunder = 0,
};

static const	t_resistance INITIALIZE_CURRENT_RESISTANCE =
{
	.acid = -501,
	.bludgeoning = -501,
	.cold = -501,
	.fire = -501,
	.force = -501,
	.lightning = -501,
	.necrotic = -501,
	.piercing = -501,
	.poison = -501,
	.psychic = -501,
	.radiant = -501,
	.slashing = -501,
	.thunder = -501,
};

static const t_equipment_action INITIALIZE_EQUIPMENT_ACTION =
{
	.function = ft_nullptr,
	.damage_type = ft_nullptr,
	.stat = ft_nullptr,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.effect_secund_dice_amount = 0,
	.effect_secund_dice_faces = 0,
	.bonus_mod = 0,
};

static const t_equipment_id INITIALIZE_EQUIPMENT_ID =
{
	.name = ft_nullptr,
	.projectile_name = ft_nullptr,
	.equipment_id = 0,
	.action_01 = INITIALIZE_EQUIPMENT_ACTION,
	.action_02 = INITIALIZE_EQUIPMENT_ACTION,
	.attack = INITIALIZE_EQUIPMENT_ACTION,
	.skill_mod = INITIALIZE_SKILLS,
	.resistance = INITIALIZE_RESISTANCE,
	.flat_dr = INITIALIZE_RESISTANCE,
	.skill_advantage = INITIALIZE_SKILLS,
	.save = INITIALIZE_SAVES,
	.save_advantage = INITIALIZE_SAVES,
	.crit_attack_fail_bonus = 0,
	.crit_attack_succes_bonus = 0,
	.type = 0,
	.dex_ac_max_bonus = 0,
	.ac = 0,
	.str = 0,
	.dex = 0,
	.con = 0,
	.inte = 0,
	.wis = 0,
	.cha = 0,
	.initiative = 0,
	.effect_id = 0,
	.effect_type = 0,
	.effect_dice_amount = 0,
	.effect_dice_faces = 0,
	.bonus_mod = 0,
	.slot = 0,
};

static const	t_stats INITIALIZE_STATS =
{
	.phase = -1,
	.turn = -1,
	.health = -1,
	.temp_hp = -1,
	.str = -1,
	.dex = -1,
	.con = -1,
	.inte = -1,
	.wis = -1,
	.cha = -1,
};

static const	t_concentration INITIALIZE_CONCENTRATION =
{
	.concentration = 0,
	.spell_id = 0,
	.dice_amount_mod = 0,
	.dice_faces_mod = 0,
	.extra = 0,
	.base_mod = 0,
	.duration = 0,
	.targets = ft_nullptr,
};


static const	t_buff_bless INITIALIZE_BLESS =
{
	.duration = 0,
	.dice_amount_mod = 0,
	.dice_faces_mod = 0,
	.base_mod = 0,
	.caster_name = ft_nullptr,
};

static const	t_buff_protective_winds INITIALIZE_PROTECTIVE_WINDS =
{
	.duration = 0,
};

static const	t_buff_lightning_strike INITIALIZE_LIGHTNING_STRIKE =
{
	.duration = 0,
	.amount = 0,
	.distance = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
};

static const	t_buff_air_totem INITIALIZE_AIR_TOTEM =
{
	.save_file = ft_nullptr,
	.health = 0,
	.ac = 0,
	.knock_back_distance = 0,
	.erea_of_effect = 0,
};

static const	t_buff_flame_geyser INITIALIZE_FLAME_GEYSER =
{
	.amount = 0,
	.duration = 0,
	.close_to_tower_d = 0,
	.tower_explode_d = 0,
};

static const	t_buff_meteor_strike INITIALIZE_METEOR_STRIKE =
{
	.duration = 0,
	.one_target_d = 0,
	.two_targets_d = 0,
	.three_targets_d = 0,
	.four_targets_d = 0,
	.five_targets_d = 0,
	.target_id = ft_nullptr,
};

static const	t_buff_chaos_armor INITIALIZE_CHAOS_ARMOR =
{
	.duration = 0,
};

static const	t_buff_earth_pounce INITIALIZE_EARTH_POUNCE =
{
	.active = 0,
	.base_damage = 0,
	.target_id = ft_nullptr,
};

static const	t_buff_arcane_pounce INITIALIZE_ARCANE_POUNCE =
{
	.active = 0,
	.magic_damage = 0,
	.erea_damage = 0,
	.target_id = ft_nullptr,
};

static const	t_buff_frost_breath INITIALIZE_FROST_BREATH =
{
	.active = 0,
	.damage = 0,
	.target_id = ft_nullptr,
};

static const	t_bufs INITIALIZE_BUFFS =
{
	.bless = INITIALIZE_BLESS,
	.protective_winds = INITIALIZE_PROTECTIVE_WINDS,
	.lightning_strike = INITIALIZE_LIGHTNING_STRIKE,
	.lightning_strikeV2 = INITIALIZE_LIGHTNING_STRIKE,
	.flame_geyser = INITIALIZE_FLAME_GEYSER,
	.meteor_strike = INITIALIZE_METEOR_STRIKE,
	.chaos_armor = INITIALIZE_CHAOS_ARMOR,
	.arcane_pounce = INITIALIZE_ARCANE_POUNCE,
	.earth_pounce = INITIALIZE_EARTH_POUNCE,
	.frost_breath = INITIALIZE_FROST_BREATH,
};

static const	t_debuff_hunters_mark INITIALIZE_HUNTERS_MARK =
{
	.amount = 0,
	.caster_name = ft_nullptr,
};

static const	t_debuff_blinded INITIALIZE_BLINDED =
{
	.duration = 0,
};

static const	t_debufs INITIALIZE_DEBUFFS =
{
	.hunters_mark = INITIALIZE_HUNTERS_MARK,
	.blinded = INITIALIZE_BLINDED,
};

static const	t_flags INITIALIZE_FLAGS =
{
	.alreaddy_saved = 0,
	.error = 0,
	.flanking = 0,
	.advantage = 0,
	.prone = 0,
	.reaction_used = 0,
	.dont_save = 0,
};

static const	t_crackback INITIALIZE_CRACKBACK =
{
	.active = 0,
};

static const	t_feats INITIALIZE_FEATS =
{
	.crackback = INITIALIZE_CRACKBACK,
};

static const t_spell_slot INITIALIZE_SPELL_SLOT =
{
	.available = 0,
	.total = 0,
	.level = 0,
	.replenishing_slot = 0,
};

static const t_spell_slots INITIALIZE_SPELL_SLOTS =
{
	.level_1 = INITIALIZE_SPELL_SLOT,
	.level_2 = INITIALIZE_SPELL_SLOT,
	.level_3 = INITIALIZE_SPELL_SLOT,
	.level_4 = INITIALIZE_SPELL_SLOT,
	.level_5 = INITIALIZE_SPELL_SLOT,
	.level_6 = INITIALIZE_SPELL_SLOT,
	.level_7 = INITIALIZE_SPELL_SLOT,
	.level_8 = INITIALIZE_SPELL_SLOT,
	.level_9 = INITIALIZE_SPELL_SLOT,
	.warlock = INITIALIZE_SPELL_SLOT,
};

static const	t_spell_magic_drain INITIALIZE_SPELL_MAGIC_DRAIN =
{
	.target = ft_nullptr,
	.damage_flat = 0,
	.damage_dice_amount = 0,
	.damage_dice_faces = 0,
	.spell_slot_total_level_drain = 0,
	.dex_save = 0,
};

static const t_spell_hunters_mark INITIALIZE_SPELL_HUNTERS_MARK =
{
	.learned = 0,
	.base_level = 0,
	.casting_at_level = 0,
	.duration = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
	.upcast_extra_dice_face = 0,
	.upcast_extra_dice_amount = 0,
	.upcast_extra_damage = 0,
};

static const t_spell_divine_smite INITIALIZE_SPELL_DIVINE_SMITE =
{
	.learned = 0,
	.base_level = 0,
	.casting_at_level = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_damage = 0,
	.upcast_extra_dice_face = 0,
	.upcast_extra_dice_amount = 0,
	.upcast_extra_damage = 0,
};

static const t_spell_cure_wounds INITIALIZE_SPELL_CURE_WOUNDS =
{
	.learned = 0,
	.base_level = 0,
	.casting_at_level = 0,
	.dice_amount = 0,
	.dice_faces = 0,
	.extra_healing = 0,
	.upcast_extra_dice_face = 0,
	.upcast_extra_dice_amount = 0,
	.upcast_extra_healing = 0,
};

static const t_spell_bless INITIALIZE_SPELL_BLESS =
{
	.learned = 0,
	.base_level = 0,
	.casting_at_level = 0,
	.duration = 0,
	.target_amount = 0,
	.dice_faces = 0,
	.dice_amount = 0,
	.upcast_extra_targets = 0,
	.upcast_extra_duration = 0,
	.upcast_extra_dice_faces = 0,
	.upcast_extra_dice_amount = 0,
};

static const t_spells INITIALIZE_SPELLS =
{
	.cure_wounds = INITIALIZE_SPELL_CURE_WOUNDS,
	.divine_smite = INITIALIZE_SPELL_DIVINE_SMITE,
	.hunters_mark = INITIALIZE_SPELL_HUNTERS_MARK,
	.bless = INITIALIZE_SPELL_BLESS,
	.magic_drain = INITIALIZE_SPELL_MAGIC_DRAIN,
};

static const	t_inventory INITIALIZE_INVENTORY =
{
	.gold = 0,
};

static const	t_hit_dice INITIALIZ_HIT_DICE =
{
	.dice_amount = 0,
	.dice_faces = 0,
};

#endif
