#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "identification.hpp"

typedef struct s_key_value_triplet
{
    const char *key;
    int *value;
    int unset_value;
} t_key_value_triplet;

static int ft_set_stat_int_internal(char *content, const char *key, int *field, int unset_value, ft_sharedptr<t_char> &info)
{
    int index = ft_strlen(key);
    if (ft_strncmp(content, key, index) == 0 && (unset_value == -1 || *field == unset_value))
    {
        *field = ft_check_stat(info, content, index);
        return (1);
    }
    return (0);
}

static int ft_handle_int_mapping(char *line, const t_key_value_triplet *array, ft_sharedptr<t_char> &info)
{
    int j = 0;
    while (array[j].key)
    {
        if (ft_set_stat_int_internal(line, array[j].key, array[j].value, array[j].unset_value,
					info) == 1)
            return (0);
        j++;
    }
    return (1);
}

static int ft_handle_set_stat_char_pointer(char *content_i, size_t key_len, char **target_field)
{
    if (ft_set_stat_player(key_len, const_cast<const char **>(target_field), content_i))
        return (-1);
    return (0);
}

static int ft_handle_set_stat_double_char(char *content_i, size_t key_len, char ***target_field,
		ft_sharedptr<t_char> &info)
{
    *target_field = ft_set_stats_con_targets(content_i, key_len, *target_field, info);
    if (*target_field == ft_nullptr)
        return (-1);
    return (0);
}

static int ft_handle_string_fields(char *line, ft_sharedptr<t_char> &info)
{
    if (ft_strncmp(line, CONC_TARGETS_KEY, ft_strlen(CONC_TARGETS_KEY)) == 0)
        return (ft_handle_set_stat_double_char(line, ft_strlen(CONC_TARGETS_KEY),
				&info->concentration.targets, info));
    if (ft_strncmp(line, HUNTERS_MARK_CASTER_KEY, ft_strlen(HUNTERS_MARK_CASTER_KEY)) == 0)
        return (ft_handle_set_stat_double_char(line, ft_strlen(HUNTERS_MARK_CASTER_KEY),
				&info->debufs.hunters_mark.caster_name, info));
    if (ft_strncmp(line, METEOR_STRIKE_TARGET_KEY, ft_strlen(METEOR_STRIKE_TARGET_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(METEOR_STRIKE_TARGET_KEY),
				&info->bufs.meteor_strike.target_id));
    if (ft_strncmp(line, FROST_BREATH_TARGET_ID_KEY, ft_strlen(FROST_BREATH_TARGET_ID_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(FROST_BREATH_TARGET_ID_KEY),
				&info->bufs.frost_breath.target_id));
    if (ft_strncmp(line, ARCANE_POUNCE_TARGET_ID_KEY, ft_strlen(ARCANE_POUNCE_TARGET_ID_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(ARCANE_POUNCE_TARGET_ID_KEY),
				&info->bufs.arcane_pounce.target_id));
    if (ft_strncmp(line, EARTH_POUNCE_TARGET_ID_KEY, ft_strlen(EARTH_POUNCE_TARGET_ID_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(EARTH_POUNCE_TARGET_ID_KEY),
				&info->bufs.earth_pounce.target_id));
    return (1);
}

int ft_set_stats(ft_sharedptr<t_char> &info, char **content)
{
    t_key_value_triplet arr[] =
    {
        {HEALTH_KEY, &info->stats.health, -1},
        {TEMP_HP_KEY, &info->stats.temp_hp, -1},
        {STR_KEY, &info->stats.str, -1},
        {DEX_KEY, &info->stats.dex, -1},
        {CON_KEY, &info->stats.con, -1},
        {INT_KEY, &info->stats.inte, -1},
        {WIS_KEY, &info->stats.wis, -1},
        {CHA_KEY, &info->stats.cha, -1},
        {TURN_KEY, &info->stats.turn, -1},
        {INITIATIVE_KEY, &info->initiative, -1},
        {BLESS_DUR_KEY, &info->bufs.bless.duration, 0},
        {PHASE_KEY, &info->stats.phase, -1},
        {LIGHTNING_STRIKE_DUR_KEY, &info->bufs.lightning_strike.duration, 0},
        {PROTECTIVE_WINDS_DUR_KEY, &info->bufs.protective_winds.duration, 0},
        {LEVEL_1_AVAILABLE_KEY, &info->spell_slots.level_1.available, -1},
        {LEVEL_1_TOTAL_KEY, &info->spell_slots.level_1.total, -1},
        {LEVEL_1_LEVEL_KEY, &info->spell_slots.level_1.level, -1},
        {LEVEL_1_REPLENISHING_SLOT_KEY, &info->spell_slots.level_1.replenishing_slot, -1},
        {LEVEL_2_AVAILABLE_KEY, &info->spell_slots.level_2.available, -1},
        {LEVEL_2_TOTAL_KEY, &info->spell_slots.level_2.total, -1},
        {LEVEL_2_LEVEL_KEY, &info->spell_slots.level_2.level, -1},
        {LEVEL_2_REPLENISHING_SLOT_KEY, &info->spell_slots.level_2.replenishing_slot, -1},
        {LEVEL_3_AVAILABLE_KEY, &info->spell_slots.level_3.available, -1},
        {LEVEL_3_TOTAL_KEY, &info->spell_slots.level_3.total, -1},
        {LEVEL_3_LEVEL_KEY, &info->spell_slots.level_3.level, -1},
        {LEVEL_3_REPLENISHING_SLOT_KEY, &info->spell_slots.level_3.replenishing_slot, -1},
        {LEVEL_4_AVAILABLE_KEY, &info->spell_slots.level_4.available, -1},
        {LEVEL_4_TOTAL_KEY, &info->spell_slots.level_4.total, -1},
        {LEVEL_4_LEVEL_KEY, &info->spell_slots.level_4.level, -1},
        {LEVEL_4_REPLENISHING_SLOT_KEY, &info->spell_slots.level_4.replenishing_slot, -1},
        {LEVEL_5_AVAILABLE_KEY, &info->spell_slots.level_5.available, -1},
        {LEVEL_5_TOTAL_KEY, &info->spell_slots.level_5.total, -1},
        {LEVEL_5_LEVEL_KEY, &info->spell_slots.level_5.level, -1},
        {LEVEL_5_REPLENISHING_SLOT_KEY, &info->spell_slots.level_5.replenishing_slot, -1},
        {LEVEL_6_AVAILABLE_KEY, &info->spell_slots.level_6.available, -1},
        {LEVEL_6_TOTAL_KEY, &info->spell_slots.level_6.total, -1},
        {LEVEL_6_LEVEL_KEY, &info->spell_slots.level_6.level, -1},
        {LEVEL_6_REPLENISHING_SLOT_KEY, &info->spell_slots.level_6.replenishing_slot, -1},
        {LEVEL_7_AVAILABLE_KEY, &info->spell_slots.level_7.available, -1},
        {LEVEL_7_TOTAL_KEY, &info->spell_slots.level_7.total, -1},
        {LEVEL_7_LEVEL_KEY, &info->spell_slots.level_7.level, -1},
        {LEVEL_7_REPLENISHING_SLOT_KEY, &info->spell_slots.level_7.replenishing_slot, -1},
        {LEVEL_8_AVAILABLE_KEY, &info->spell_slots.level_8.available, -1},
        {LEVEL_8_TOTAL_KEY, &info->spell_slots.level_8.total, -1},
        {LEVEL_8_LEVEL_KEY, &info->spell_slots.level_8.level, -1},
        {LEVEL_8_REPLENISHING_SLOT_KEY, &info->spell_slots.level_8.replenishing_slot, -1},
        {LEVEL_9_AVAILABLE_KEY, &info->spell_slots.level_9.available, -1},
        {LEVEL_9_TOTAL_KEY, &info->spell_slots.level_9.total, -1},
        {LEVEL_9_LEVEL_KEY, &info->spell_slots.level_9.level, -1},
        {LEVEL_9_REPLENISHING_SLOT_KEY, &info->spell_slots.level_9.replenishing_slot, -1},
        {WARLOCK_AVAILABLE_KEY, &info->spell_slots.warlock.available, -1},
        {WARLOCK_TOTAL_KEY, &info->spell_slots.warlock.total, -1},
        {WARLOCK_LEVEL_KEY, &info->spell_slots.warlock.level, -1},
        {WARLOCK_REPLENISHING_SLOT_KEY, &info->spell_slots.warlock.replenishing_slot, -1},
        {ACID_RESISTANCE_KEY, &info->c_resistance.acid, -501},
        {BLUDGEONING_RESISTANCE_KEY, &info->c_resistance.bludgeoning, -501},
        {COLD_RESISTANCE_KEY, &info->c_resistance.cold, -501},
        {FIRE_RESISTANCE_KEY, &info->c_resistance.fire, -501},
        {FORCE_RESISTANCE_KEY, &info->c_resistance.force, -501},
        {LIGHTNING_RESISTANCE_KEY, &info->c_resistance.lightning, -501},
        {NECROTIC_RESISTANCE_KEY, &info->c_resistance.necrotic, -501},
        {PIERCING_RESISTANCE_KEY, &info->c_resistance.piercing, -501},
        {POISON_RESISTANCE_KEY, &info->c_resistance.poison, -501},
        {PSYCHIC_RESISTANCE_KEY, &info->c_resistance.psychic, -501},
        {RADIANT_RESISTANCE_KEY, &info->c_resistance.radiant, -501},
        {SLASHING_RESISTANCE_KEY, &info->c_resistance.slashing, -501},
        {THUNDER_RESISTANCE_KEY, &info->c_resistance.thunder, -501},
        {CONCENTRATION_KEY, &info->concentration.concentration, 0},
        {CONC_SPELL_ID_KEY, &info->concentration.spell_id, 0},
        {CONC_DICE_AMOUNT_KEY, &info->concentration.dice_amount_mod, 0},
        {CONC_DICE_FACES_KEY, &info->concentration.dice_faces_mod, 0},
        {CONC_BASE_MOD_KEY, &info->concentration.base_mod, 0},
        {CONC_DURATION_KEY, &info->concentration.duration, 0},
        {HUNTERS_MARK_AMOUNT_KEY, &info->debufs.hunters_mark.amount, 0},
        {CHAOS_ARMOR_DURATION_KEY, &info->bufs.chaos_armor.duration, 0},
        {PRONE_KEY, &info->flags.prone, 0},
        {BLINDED_KEY, &info->debufs.blinded.duration, 0},
        {FLAME_GEYSER_DURATION_KEY, &info->bufs.flame_geyser.duration, 0},
        {FLAME_GEYSER_AMOUNT_KEY, &info->bufs.flame_geyser.amount, 0},
        {FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY, &info->bufs.flame_geyser.close_to_tower_d, 0},
        {FLAME_GEYSER_TOWER_EXPLODE_D_KEY, &info->bufs.flame_geyser.tower_explode_d, 0},
        {METEOR_STRIKE_DURATION_KEY, &info->bufs.meteor_strike.duration, 0},
        {METEOR_STRIKE_ONE_TARGET_D_KEY, &info->bufs.meteor_strike.one_target_d, 0},
        {METEOR_STRIKE_TWO_TARGETS_D_KEY, &info->bufs.meteor_strike.two_targets_d, 0},
        {METEOR_STRIKE_THREE_TARGETS_D_KEY, &info->bufs.meteor_strike.three_targets_d, 0},
        {METEOR_STRIKE_FOUR_TARGETS_D_KEY, &info->bufs.meteor_strike.four_targets_d, 0},
        {METEOR_STRIKE_FIVE_TARGETS_D_KEY, &info->bufs.meteor_strike.five_targets_d, 0},
        {LIGHTNING_STRIKE_DURATION_KEY, &info->bufs.lightning_strike.duration, 0},
        {LIGHTNING_STRIKE_AMOUNT_KEY, &info->bufs.lightning_strike.amount, 0},
        {LIGHTNING_STRIKE_DISTANCE_KEY, &info->bufs.lightning_strike.distance, 0},
        {LIGHTNING_STRIKE_DICE_AMOUNT_KEY, &info->bufs.lightning_strike.dice_amount, 0},
        {LIGHTNING_STRIKE_DICE_FACES_KEY, &info->bufs.lightning_strike.dice_faces, 0},
        {LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY, &info->bufs.lightning_strike.extra_damage, 0},
        {LIGHTNING_STRIKEV2_DURATION_KEY, &info->bufs.lightning_strikeV2.duration, 0},
        {LIGHTNING_STRIKEV2_AMOUNT_KEY, &info->bufs.lightning_strikeV2.amount, 0},
        {LIGHTNING_STRIKEV2_DISTANCE_KEY, &info->bufs.lightning_strikeV2.distance, 0},
        {LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY, &info->bufs.lightning_strikeV2.dice_amount, 0},
        {LIGHTNING_STRIKEV2_DICE_FACES_KEY, &info->bufs.lightning_strikeV2.dice_faces, 0},
        {LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY, &info->bufs.lightning_strikeV2.extra_damage, 0},
        {EARTH_POUNCE_ACTIVE_KEY, &info->bufs.earth_pounce.active, 0},
        {EARTH_POUNCE_BASE_DAMAGE_KEY, &info->bufs.earth_pounce.base_damage, 0},
        {ARCANE_POUNCE_ACTIVE_KEY, &info->bufs.arcane_pounce.active, 0},
        {ARCANE_POUNCE_EREA_DAMAGE_KEY, &info->bufs.arcane_pounce.erea_damage, 0},
        {ARCANE_POUNCE_MAGIC_DAMAGE_KEY, &info->bufs.arcane_pounce.magic_damage, 0},
        {FROST_BREATH_ACTIVE_KEY, &info->bufs.frost_breath.active, 0},
        {FROST_BREATH_DAMAGE_KEY, &info->bufs.frost_breath.damage, 0},
        {REACTION_USED_KEY, &info->flags.reaction_used, 0},
        {NULL, NULL, 0}
    };
    int i = 0;
    while (content[i])
    {
        if (ft_handle_int_mapping(content[i], arr, info) == 0)
        {
            i++;
            continue ;
        }
        int err = ft_handle_string_fields(content[i], info);
        if (err == 0)
        {
            i++;
            continue ;
        }
        pf_printf_fd(2, "1-Something is wrong with the save file for %s at the line: %s" \
				", please reinitialize the save\n", info->name, content[i]);
        info->flags.error = 1;
        return (1);
    }
    return (0);
}
