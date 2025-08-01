#ifndef KEY_LIST_HPP
# define KEY_LIST_HPP

#include <cstddef>

constexpr std::size_t constexpr_strlen(const char* str)
{
    std::size_t len = 0;
    while (str[len] != '\0')
        ++len;
    return len;
}

constexpr bool ends_with(const char* str, const char* suffix)
{
    std::size_t str_len = constexpr_strlen(str);
    std::size_t suffix_len = constexpr_strlen(suffix);
    if (suffix_len > str_len)
        return false;
    for (std::size_t i = 0; i < suffix_len; ++i)
    {
        if (str[str_len - suffix_len + i] != suffix[i])
            return false;
    }
    return true;
}

constexpr bool is_valid_key_impl(const char* str, std::size_t i)
{
    if (str[i] == '=')
        return (i > 0 && str[i + 1] == '\0');
    if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') ||
        (str[i] >= '0' && str[i] <= '9'))
        return is_valid_key_impl(str, i + 1);
    return false;
}

constexpr bool is_valid_key(const char* str)
{
    return is_valid_key_impl(str, 0);
}

#define KEY_LIST \
    X(HEALTH_KEY, "HEALTH=") \
    X(MAX_HEALTH_KEY, "MAX_HEALTH=") \
    X(TEMP_HP_KEY, "TEMP_HP=") \
    X(STR_KEY, "STR=") \
    X(DEX_KEY, "DEX=") \
    X(CON_KEY, "CON=") \
    X(INT_KEY, "INT=") \
    X(WIS_KEY, "WIS=") \
    X(CHA_KEY, "CHA=") \
    X(TURN_KEY, "TURN=") \
    X(INITIATIVE_KEY, "INITIATIVE=") \
    X(BLESS_DUR_KEY, "BLESS_DUR=") \
    X(PHASE_KEY, "PHASE=") \
    X(CONCENTRATION_KEY, "CONCENTRATION=") \
    X(HUNTERS_MARK_AMOUNT_KEY, "HUNTERS_MARK_AMOUNT=") \
    X(HUNTERS_MARK_CASTER_KEY, "HUNTERS_MARK_CASTER=") \
    X(CHAOS_ARMOR_DURATION_KEY, "CHAOS_ARMOR_DURATION=") \
    X(PRONE_KEY, "PRONE=") \
    X(BLINDED_KEY, "BLINDED=") \
    X(REACTION_USED_KEY, "REACTION_USED=") \
    X(LIGHTNING_STRIKE_DUR_KEY, "LIGHTNING_STRIKE_DUR=") \
    X(PROTECTIVE_WINDS_DUR_KEY, "PROTECTIVE_WINDS_DUR=") \
    X(ACID_RESISTANCE_KEY, "ACID_RESISTANCE=") \
    X(BLUDGEONING_RESISTANCE_KEY, "BLUDGEONING_RESISTANCE=") \
    X(COLD_RESISTANCE_KEY, "COLD_RESISTANCE=") \
    X(FIRE_RESISTANCE_KEY, "FIRE_RESISTANCE=") \
    X(FORCE_RESISTANCE_KEY, "FORCE_RESISTANCE=") \
    X(LIGHTNING_RESISTANCE_KEY, "LIGHTNING_RESISTANCE=") \
    X(NECROTIC_RESISTANCE_KEY, "NECROTIC_RESISTANCE=") \
    X(PIERCING_RESISTANCE_KEY, "PIERCING_RESISTANCE=") \
    X(POISON_RESISTANCE_KEY, "POISON_RESISTANCE=") \
    X(PSYCHIC_RESISTANCE_KEY, "PSYCHIC_RESISTANCE=") \
    X(RADIANT_RESISTANCE_KEY, "RADIANT_RESISTANCE=") \
    X(SLASHING_RESISTANCE_KEY, "SLASHING_RESISTANCE=") \
    X(THUNDER_RESISTANCE_KEY, "THUNDER_RESISTANCE=") \
    X(CONC_TARGETS_KEY, "CONC_TARGETS=") \
    X(CONC_SPELL_ID_KEY, "CONC_SPELL_ID=") \
    X(CONC_DICE_AMOUNT_KEY, "CONC_DICE_AMOUNT=") \
    X(CONC_DICE_FACES_KEY, "CONC_DICE_FACES=") \
    X(CONC_BASE_MOD_KEY, "CONC_BASE_MOD=") \
    X(CONC_DURATION_KEY, "CONC_DURATION=") \
    X(FLAME_GEYSER_DURATION_KEY, "FLAME_GEYSER_DURATION=") \
    X(FLAME_GEYSER_AMOUNT_KEY, "FLAME_GEYSER_AMOUNT=") \
    X(FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY, "FLAME_GEYSER_CLOSE_TO_TOWER_D=") \
    X(FLAME_GEYSER_TOWER_EXPLODE_D_KEY, "FLAME_GEYSER_TOWER_EXPLODE_D=") \
    X(METEOR_STRIKE_DURATION_KEY, "METEOR_STRIKE_DURATION=") \
    X(METEOR_STRIKE_ONE_TARGET_D_KEY, "METEOR_STRIKE_ONE_TARGET_D=") \
    X(METEOR_STRIKE_TWO_TARGETS_D_KEY, "METEOR_STRIKE_TWO_TARGETS_D=") \
    X(METEOR_STRIKE_THREE_TARGETS_D_KEY, "METEOR_STRIKE_THREE_TARGETS_D=") \
    X(METEOR_STRIKE_FOUR_TARGETS_D_KEY, "METEOR_STRIKE_FOUR_TARGETS_D=") \
    X(METEOR_STRIKE_FIVE_TARGETS_D_KEY, "METEOR_STRIKE_FIVE_TARGETS_D=") \
    X(METEOR_STRIKE_TARGET_KEY, "METEOR_STRIKE_TARGET=") \
    X(LIGHTNING_STRIKE_DURATION_KEY, "LIGHTNING_STRIKE_DURATION=") \
    X(LIGHTNING_STRIKE_AMOUNT_KEY, "LIGHTNING_STRIKE_AMOUNT=") \
    X(LIGHTNING_STRIKE_DISTANCE_KEY, "LIGHTNING_STRIKE_DISTANCE=") \
    X(LIGHTNING_STRIKE_DICE_AMOUNT_KEY, "LIGHTNING_STRIKE_DICE_AMOUNT=") \
    X(LIGHTNING_STRIKE_DICE_FACES_KEY, "LIGHTNING_STRIKE_DICE_FACES=") \
    X(LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY, "LIGHTNING_STRIKE_EXTRA_DAMAGE=") \
    X(LIGHTNING_STRIKEV2_DURATION_KEY, "LIGHTNING_STRIKEV2_DURATION=") \
    X(LIGHTNING_STRIKEV2_AMOUNT_KEY, "LIGHTNING_STRIKEV2_AMOUNT=") \
    X(LIGHTNING_STRIKEV2_DISTANCE_KEY, "LIGHTNING_STRIKEV2_DISTANCE=") \
    X(LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY, "LIGHTNING_STRIKEV2_DICE_AMOUNT=") \
    X(LIGHTNING_STRIKEV2_DICE_FACES_KEY, "LIGHTNING_STRIKEV2_DICE_FACES=") \
    X(LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY, "LIGHTNING_STRIKEV2_EXTRA_DAMAGE=") \
    X(EARTH_POUNCE_ACTIVE_KEY, "EARTH_POUNCE_ACTIVE=") \
    X(EARTH_POUNCE_BASE_DAMAGE_KEY, "EARTH_POUNCE_BASE_DAMAGE=") \
    X(EARTH_POUNCE_TARGET_ID_KEY, "EARTH_POUNCE_TARGET_ID=") \
    X(ARCANE_POUNCE_ACTIVE_KEY, "ARCANE_POUNCE_ACTIVE=") \
    X(ARCANE_POUNCE_MAGIC_DAMAGE_KEY, "ARCANE_POUNCE_MAGIC_DAMAGE=") \
    X(ARCANE_POUNCE_EREA_DAMAGE_KEY, "ARCANE_POUNCE_EREA_DAMAGE=") \
    X(ARCANE_POUNCE_TARGET_ID_KEY, "ARCANE_POUNCE_TARGET_ID=") \
    X(FROST_BREATH_ACTIVE_KEY, "FROST_BREATH_ACTIVE=") \
    X(FROST_BREATH_DAMAGE_KEY, "FROST_BREATH_DAMAGE=") \
    X(FROST_BREATH_TARGET_ID_KEY, "FROST_BREATH_TARGET_ID=") \
    X(SHADOW_ILLUSION_ACTIVE_KEY, "SHADOW_ILLUSION_ACTIVE=") \
    X(SHADOW_ILLUSION_DURATION_KEY, "SHADOW_ILLUSION_DURATION=") \
    X(LEVEL_1_AVAILABLE_KEY, "LEVEL_1_AVAILABLE=") \
    X(LEVEL_1_TOTAL_KEY, "LEVEL_1_TOTAL=") \
    X(LEVEL_1_LEVEL_KEY, "LEVEL_1_LEVEL=") \
    X(LEVEL_1_REPLENISHING_SLOT_KEY, "LEVEL_1_REPLENISHING_SLOT=") \
    X(LEVEL_2_AVAILABLE_KEY, "LEVEL_2_AVAILABLE=") \
    X(LEVEL_2_TOTAL_KEY, "LEVEL_2_TOTAL=") \
    X(LEVEL_2_LEVEL_KEY, "LEVEL_2_LEVEL=") \
    X(LEVEL_2_REPLENISHING_SLOT_KEY, "LEVEL_2_REPLENISHING_SLOT=") \
    X(LEVEL_3_AVAILABLE_KEY, "LEVEL_3_AVAILABLE=") \
    X(LEVEL_3_TOTAL_KEY, "LEVEL_3_TOTAL=") \
    X(LEVEL_3_LEVEL_KEY, "LEVEL_3_LEVEL=") \
    X(LEVEL_3_REPLENISHING_SLOT_KEY, "LEVEL_3_REPLENISHING_SLOT=") \
    X(LEVEL_4_AVAILABLE_KEY, "LEVEL_4_AVAILABLE=") \
    X(LEVEL_4_TOTAL_KEY, "LEVEL_4_TOTAL=") \
    X(LEVEL_4_LEVEL_KEY, "LEVEL_4_LEVEL=") \
    X(LEVEL_4_REPLENISHING_SLOT_KEY, "LEVEL_4_REPLENISHING_SLOT=") \
    X(LEVEL_5_AVAILABLE_KEY, "LEVEL_5_AVAILABLE=") \
    X(LEVEL_5_TOTAL_KEY, "LEVEL_5_TOTAL=") \
    X(LEVEL_5_LEVEL_KEY, "LEVEL_5_LEVEL=") \
    X(LEVEL_5_REPLENISHING_SLOT_KEY, "LEVEL_5_REPLENISHING_SLOT=") \
    X(LEVEL_6_AVAILABLE_KEY, "LEVEL_6_AVAILABLE=") \
    X(LEVEL_6_TOTAL_KEY, "LEVEL_6_TOTAL=") \
    X(LEVEL_6_LEVEL_KEY, "LEVEL_6_LEVEL=") \
    X(LEVEL_6_REPLENISHING_SLOT_KEY, "LEVEL_6_REPLENISHING_SLOT=") \
    X(LEVEL_7_AVAILABLE_KEY, "LEVEL_7_AVAILABLE=") \
    X(LEVEL_7_TOTAL_KEY, "LEVEL_7_TOTAL=") \
    X(LEVEL_7_LEVEL_KEY, "LEVEL_7_LEVEL=") \
    X(LEVEL_7_REPLENISHING_SLOT_KEY, "LEVEL_7_REPLENISHING_SLOT=") \
    X(LEVEL_8_AVAILABLE_KEY, "LEVEL_8_AVAILABLE=") \
    X(LEVEL_8_TOTAL_KEY, "LEVEL_8_TOTAL=") \
    X(LEVEL_8_LEVEL_KEY, "LEVEL_8_LEVEL=") \
    X(LEVEL_8_REPLENISHING_SLOT_KEY, "LEVEL_8_REPLENISHING_SLOT=") \
    X(LEVEL_9_AVAILABLE_KEY, "LEVEL_9_AVAILABLE=") \
    X(LEVEL_9_TOTAL_KEY, "LEVEL_9_TOTAL=") \
    X(LEVEL_9_LEVEL_KEY, "LEVEL_9_LEVEL=") \
    X(LEVEL_9_REPLENISHING_SLOT_KEY, "LEVEL_9_REPLENISHING_SLOT=") \
    X(WARLOCK_AVAILABLE_KEY, "WARLOCK_AVAILABLE=") \
    X(WARLOCK_TOTAL_KEY, "WARLOCK_TOTAL=") \
    X(WARLOCK_LEVEL_KEY, "WARLOCK_LEVEL=") \
    X(WARLOCK_REPLENISHING_SLOT_KEY, "WARLOCK_REPLENISHING_SLOT=") \
    X(BUFF_BLESS_DURATION_KEY, "BUFF_BLESS_DURATION=") \
    X(BUFF_BLESS_DICE_AMOUNT_MOD_KEY, "BUFF_BLESS_DICE_AMOUNT_MOD=") \
    X(BUFF_BLESS_DICE_FACES_MOD_KEY, "BUFF_BLESS_DICE_FACES_MOD=") \
    X(BUFF_BLESS_BASE_MOD_KEY, "BUFF_BLESS_BASE_MOD=") \
    X(BUFF_BLESS_CASTER_NAME_KEY, "BUFF_BLESS_CASTER_NAME=") \
    X(SPELL_MAGIC_DRAIN_TARGET_KEY, "SPELL_MAGIC_DRAIN=") \
    X(SPELL_MAGIC_DRAIN_DAMAGE_FLAT_KEY, "SPELL_MAGIC_DRAIN_DAMAGE_FLAT=") \
    X(SPELL_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN_KEY, \
			"SPELL_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN=") \
    X(SPELL_MAGIC_DRAIN_DICE_AMOUNT_KEY, "SPELL_MAGIC_DRAIN_DICE_AMOUNT=") \
    X(SPELL_MAGIC_DRAIN_DICE_FACES_KEY, "SPELL_MAGIC_DRAIN_DICE_FACES=") \
    X(SPELL_MAGIC_DRAIN_DEX_SAVE_KEY, "SPELL_MAGIC_DRAIN_DEX_SAVE=") \
    X(SPELL_MAGIC_DRAIN_TURNS_PASSED_FROM_LAST_CAST_KEY, \
			"SPELL_MAGIC_DRAIN_TURNS_FRON_LAST_CAST=") \
    X(SPELL_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT_KEY, "SPELL_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT=") \
    X(SPELL_MAGIC_DRAIN_EXTRA_DICE_AMOUNT_KEY, "SPELL_MAGIC_DRAIN_EXTRA_DICE_AMOUNT=") \
    X(SPELL_MAGIC_DRAIN_EXTRA_DICE_FACES_KEY, "SPELL_MAGIC_DRAIN_EXTRA_DICE_FACES=") \
    X(SPELL_MAGIC_DRAIN_COOLDOWN_KEY, "SPELL_MAGIC_DRAIN_COOLDOWN=") \
    X(DEBUFF_MAGIC_DRAIN_CASTER_KEY, "DEBUFF_MAGIC_DRAIN=") \
    X(DEBUFF_MAGIC_DRAIN_DAMAGE_FLAT_KEY, "DEBUFF_MAGIC_DRAIN_DAMAGE_FLAT=") \
    X(DEBUFF_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN_KEY, \
			"DEBUFF_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN=") \
    X(DEBUFF_MAGIC_DRAIN_DICE_AMOUNT_KEY, "DEBUFF_MAGIC_DRAIN_DICE_AMOUNT=") \
    X(DEBUFF_MAGIC_DRAIN_DICE_FACES_KEY, "DEBUFF_MAGIC_DRAIN_DICE_FACES=") \
    X(DEBUFF_MAGIC_DRAIN_CON_SAVE_KEY, "DEBUFF_MAGIC_DRAIN_CON_SAVE=") \
    X(DEBUFF_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT_KEY, "DEBUFF_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT=") \
    X(DEBUFF_MAGIC_DRAIN_EXTRA_DICE_AMOUNT_KEY, "DEBUFF_MAGIC_DRAIN_EXTRA_DICE_AMOUNT=") \
    X(DEBUFF_MAGIC_DRAIN_EXTRA_DICE_FACES_KEY, "DEBUFF_MAGIC_DRAIN_EXTRA_DICE_FACES=") \
	X(SPELL_MAGIC_DRAIN_LEARNED_KEY, "SPELL_MAGIC_DRAIN_LEARNED=") \
	X(DEBUFF_MAGIC_DRAIN_AMOUNT_KEY, "DEBUFF_MAGIC_DRAIN_DEBUFF_AMOUNT=") \
	X(DEBUFF_FELL_POISON_DURATION_KEY, "DEBUFF_FELL_DURATION_POISON=") \
	X(BUFF_REJUVENATION_DURATION_KEY, "BUFF_REJUVENATION_DURATION=") \
	X(BUFF_REJUVENATION_DICE_AMOUNT_KEY, "BUFF_REJUVENATION_DICE_AMOUNT=") \
	X(BUFF_REJUVENATION_DICE_FACES_KEY, "BUFF_REJUVENATION_DICE_FACES=") \
	X(BUFF_REJUVENATION_EXTRA_KEY, "BUFF_REJUVENATION_EXTRA=") \
	X(BUFF_GROWTH_STACKS_KEY, "BUFF_GROWTH_STACKS=") 

#define X(name, value) \
    static_assert(ends_with(#name, "_KEY"), "Macro name must end with _KEY"); \
    static_assert(is_valid_key(value), "Invalid key: " value); \
    extern const char* name; \
    extern const int name##_LEN;

KEY_LIST

#undef X

#endif
