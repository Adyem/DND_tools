#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/JSon/document.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/vector.hpp"
#include "libft/Libft/libft.hpp"
#include "key_list.hpp"
#include "set_utils.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct s_json_line_writer
{
    ft_vector<ft_string>    lines;
    bool                    error;
}   t_json_line_writer;

static void ft_json_line_writer_init(t_json_line_writer *writer)
{
    if (!writer)
        return ;
    writer->error = false;
    return ;
}

static void ft_json_line_writer_append_raw(t_json_line_writer *writer, const char *text)
{
    ft_string line;

    if (!writer || writer->error || !text)
        return ;
    line = ft_string(text);
    if (line.get_error() != ER_SUCCESS)
    {
        writer->error = true;
        return ;
    }
    writer->lines.push_back(line);
    if (writer->lines.get_error() != ER_SUCCESS)
        writer->error = true;
    return ;
}

static int ft_json_line_writer_flush(t_json_line_writer *writer, ft_file &file)
{
    json_document   document;
    json_group      *group;
    size_t          index;
    size_t          total;
    char            *key_string;
    json_item       *item;
    char            *content;

    if (!writer || writer->error)
        return (1);
    group = document.create_group("lines");
    if (!group)
        return (1);
    document.append_group(group);
    total = writer->lines.size();
    index = 0;
    while (index < total)
    {
        key_string = cma_itoa(static_cast<int>(index));
        if (!key_string)
            return (1);
        item = document.create_item(key_string, writer->lines[index].c_str());
        cma_free(key_string);
        if (!item)
            return (1);
        document.add_item(group, item);
        index++;
    }
    content = document.write_to_string();
    if (!content)
        return (1);
    file.write(content);
    if (file.get_error() != ER_SUCCESS)
    {
        cma_free(content);
        return (1);
    }
    cma_free(content);
    return (0);
}

static void ft_write_line(ft_file &file, t_json_line_writer *writer, const char *format, ...)
{
    va_list args;
    char *buffer;
    size_t buffer_size;
    FILE *stream;
    size_t length;

    (void)file;
    buffer = ft_nullptr;
    buffer_size = 0;
    stream = open_memstream(&buffer, &buffer_size);
    if (!stream)
        return ;
    va_start(args, format);
    ft_vfprintf(stream, format, args);
    va_end(args);
    fclose(stream);
    if (!buffer)
        return ;
    if (writer)
    {
        length = ft_strlen(buffer);
        while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r'))
        {
            buffer[length - 1] = '\0';
            length--;
        }
        ft_json_line_writer_append_raw(writer, buffer);
    }
    free(buffer);
    return ;
}

static void ft_npc_write_file_double_char(const char *msg, char **targets, ft_file &file,
                                            t_char *info, t_json_line_writer *writer)
{
    int index = 0;
    if (targets)
    {
        while (targets[index])
        {
            if (DEBUG == 1)
                pf_printf_fd(1, "saving array %s %s%s\n", info->name, msg, targets[index]);
            ft_write_line(file, writer, "%s%s\n", msg, targets[index]);
            index++;
        }
    }
    return ;
}

static void ft_npc_write_file_string_set(const char *msg, const ft_set<ft_string> &targets,
        ft_file &file, t_char *info, t_json_line_writer *writer)
{
    size_t              index;
    size_t              count;
    const ft_string    *names;

    count = targets.size();
    if (count == 0)
        return ;
    names = ft_set_get_raw_data(targets);
    if (!names)
        return ;
    index = 0;
    while (index < count)
    {
        if (DEBUG == 1)
            pf_printf_fd(1, "saving array %s %s%s\n", info->name, msg, names[index].c_str());
        ft_write_line(file, writer, "%s%s\n", msg, names[index].c_str());
        index++;
    }
    return ;
}

static void ft_npc_write_spell_slots(t_char * info, ft_file &file,
        t_json_line_writer *writer)
{
    ft_write_line(file, writer, "%s%i\n", LEVEL_1_AVAILABLE_KEY, info->spell_slots.level_1.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_1_TOTAL_KEY, info->spell_slots.level_1.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_1_LEVEL_KEY, info->spell_slots.level_1.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_1_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_1.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_2_AVAILABLE_KEY, info->spell_slots.level_2.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_2_TOTAL_KEY, info->spell_slots.level_2.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_2_LEVEL_KEY, info->spell_slots.level_2.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_2_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_2.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_3_AVAILABLE_KEY, info->spell_slots.level_3.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_3_TOTAL_KEY, info->spell_slots.level_3.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_3_LEVEL_KEY, info->spell_slots.level_3.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_3_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_3.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_4_AVAILABLE_KEY, info->spell_slots.level_4.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_4_TOTAL_KEY, info->spell_slots.level_4.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_4_LEVEL_KEY, info->spell_slots.level_4.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_4_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_4.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_5_AVAILABLE_KEY, info->spell_slots.level_5.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_5_TOTAL_KEY, info->spell_slots.level_5.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_5_LEVEL_KEY, info->spell_slots.level_5.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_5_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_5.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_6_AVAILABLE_KEY, info->spell_slots.level_6.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_6_TOTAL_KEY, info->spell_slots.level_6.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_6_LEVEL_KEY, info->spell_slots.level_6.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_6_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_6.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_7_AVAILABLE_KEY, info->spell_slots.level_7.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_7_TOTAL_KEY, info->spell_slots.level_7.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_7_LEVEL_KEY, info->spell_slots.level_7.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_7_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_7.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_8_AVAILABLE_KEY, info->spell_slots.level_8.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_8_TOTAL_KEY, info->spell_slots.level_8.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_8_LEVEL_KEY, info->spell_slots.level_8.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_8_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_8.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", LEVEL_9_AVAILABLE_KEY, info->spell_slots.level_9.available);
    ft_write_line(file, writer, "%s%i\n", LEVEL_9_TOTAL_KEY, info->spell_slots.level_9.total);
    ft_write_line(file, writer, "%s%i\n", LEVEL_9_LEVEL_KEY, info->spell_slots.level_9.level);
    ft_write_line(file, writer, "%s%i\n", LEVEL_9_REPLENISHING_SLOT_KEY,
            info->spell_slots.level_9.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", WARLOCK_AVAILABLE_KEY, info->spell_slots.warlock.available);
    ft_write_line(file, writer, "%s%i\n", WARLOCK_TOTAL_KEY, info->spell_slots.warlock.total);
    ft_write_line(file, writer, "%s%i\n", WARLOCK_LEVEL_KEY, info->spell_slots.warlock.level);
    ft_write_line(file, writer, "%s%i\n", WARLOCK_REPLENISHING_SLOT_KEY,
            info->spell_slots.warlock.replenishing_slot);
    ft_write_line(file, writer, "%s%i\n", BUFF_BLESS_BASE_MOD_KEY, info->bufs.bless.base_mod);
    ft_write_line(file, writer, "%s%i\n", BUFF_BLESS_DURATION_KEY, info->bufs.bless.duration);
    ft_write_line(file, writer, "%s%i\n", BUFF_BLESS_DICE_FACES_MOD_KEY, info->bufs.bless.dice_faces_mod);
    ft_write_line(file, writer, "%s%i\n", BUFF_BLESS_DICE_AMOUNT_MOD_KEY, info->bufs.bless.dice_amount_mod);
    ft_npc_write_file_string_set(BUFF_BLESS_CASTER_NAME_KEY,
            info->bufs.bless.caster_name, file, info, writer);
    ft_write_line(file, writer, "%s%i\n", BUFF_REJUVENATION_DURATION_KEY, info->bufs.rejuvenation.duration);
    ft_write_line(file, writer, "%s%i\n", BUFF_REJUVENATION_DICE_AMOUNT_KEY,
            info->bufs.rejuvenation.healing_dice_amount);
    ft_write_line(file, writer, "%s%i\n", BUFF_REJUVENATION_DICE_FACES_KEY,
            info->bufs.rejuvenation.healing_dice_faces);
    ft_write_line(file, writer, "%s%i\n",BUFF_REJUVENATION_EXTRA_KEY, info->bufs.rejuvenation.healing_extra);
    return ;
}

static void ft_npc_write_file_1(t_char * info, t_stats *stats, ft_file &file,
        t_json_line_writer *writer)
{
    ft_write_line(file, writer, "%s%i\n", HEALTH_KEY, stats->health);
    ft_write_line(file, writer, "%s%i\n", MAX_HEALTH_KEY, info->dstats.health);
    ft_write_line(file, writer, "%s%i\n", TEMP_HP_KEY, stats->temp_hp);
    ft_write_line(file, writer, "%s%i\n", STR_KEY, stats->str);
    ft_write_line(file, writer, "%s%i\n", DEX_KEY, stats->dex);
    ft_write_line(file, writer, "%s%i\n", CON_KEY, stats->con);
    ft_write_line(file, writer, "%s%i\n", INT_KEY, stats->inte);
    ft_write_line(file, writer, "%s%i\n", WIS_KEY, stats->wis);
    ft_write_line(file, writer, "%s%i\n", CHA_KEY, stats->cha);
    ft_write_line(file, writer, "%s%i\n", TURN_KEY, stats->turn);
    ft_write_line(file, writer, "%s%i\n", PHASE_KEY, stats->phase);
    ft_write_line(file, writer, "%s%i\n", INITIATIVE_KEY, info->initiative);
    ft_write_line(file, writer, "%s%i\n", POSITION_X_KEY, info->position.x);
    ft_write_line(file, writer, "%s%i\n", POSITION_Y_KEY, info->position.y);
    ft_write_line(file, writer, "%s%i\n", POSITION_Z_KEY, info->position.z);
    ft_write_line(file, writer, "%s%i\n", BLESS_DUR_KEY, info->bufs.bless.duration);
    ft_write_line(file, writer, "%s%i\n", PROTECTIVE_WINDS_DUR_KEY,
            info->bufs.protective_winds.duration);
    return ;
}

static void ft_npc_write_file_2(t_char * info, t_resistance *resistance, ft_file &file,
        t_json_line_writer *writer)
{
    ft_write_line(file, writer, "%s%i\n", ACID_RESISTANCE_KEY, resistance->acid);
    ft_write_line(file, writer, "%s%i\n", BLUDGEONING_RESISTANCE_KEY, resistance->bludgeoning);
    ft_write_line(file, writer, "%s%i\n", COLD_RESISTANCE_KEY, resistance->cold);
    ft_write_line(file, writer, "%s%i\n", FIRE_RESISTANCE_KEY, resistance->fire);
    ft_write_line(file, writer, "%s%i\n", FORCE_RESISTANCE_KEY, resistance->force);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_RESISTANCE_KEY, resistance->lightning);
    ft_write_line(file, writer, "%s%i\n", NECROTIC_RESISTANCE_KEY, resistance->necrotic);
    ft_write_line(file, writer, "%s%i\n", PIERCING_RESISTANCE_KEY, resistance->piercing);
    ft_write_line(file, writer, "%s%i\n", POISON_RESISTANCE_KEY, resistance->poison);
    ft_write_line(file, writer, "%s%i\n", PSYCHIC_RESISTANCE_KEY, resistance->psychic);
    ft_write_line(file, writer, "%s%i\n", RADIANT_RESISTANCE_KEY, resistance->radiant);
    ft_write_line(file, writer, "%s%i\n", SLASHING_RESISTANCE_KEY, resistance->slashing);
    ft_write_line(file, writer, "%s%i\n", THUNDER_RESISTANCE_KEY, resistance->thunder);
    ft_write_line(file, writer, "%s%i\n", CONCENTRATION_KEY, info->concentration.concentration);
    ft_write_line(file, writer, "%s%i\n", CONC_SPELL_ID_KEY, info->concentration.spell_id);
    ft_write_line(file, writer, "%s%i\n", CONC_DICE_AMOUNT_KEY, info->concentration.dice_amount_mod);
    ft_write_line(file, writer, "%s%i\n", CONC_DICE_FACES_KEY, info->concentration.dice_faces_mod);
    ft_write_line(file, writer, "%s%i\n", CONC_BASE_MOD_KEY, info->concentration.base_mod);
    ft_write_line(file, writer, "%s%i\n", CONC_DURATION_KEY, info->concentration.duration);
    ft_npc_write_file_double_char(CONC_TARGETS_KEY,
            info->concentration.targets, file, info, writer);
    ft_write_line(file, writer, "%s%i\n", HUNTERS_MARK_AMOUNT_KEY,
            info->debufs.hunters_mark.amount);
    ft_npc_write_file_string_set(HUNTERS_MARK_CASTER_KEY,
            info->debufs.hunters_mark.caster_name, file, info, writer);
    ft_write_line(file, writer, "%s%i\n", CHAOS_ARMOR_DURATION_KEY,
            info->bufs.chaos_armor.duration);
    ft_write_line(file, writer, "%s%i\n", PRONE_KEY,
            info->flags.prone);
    ft_write_line(file, writer, "%s%i\n", BLINDED_KEY,
            info->debufs.blinded.duration);
    ft_write_line(file, writer, "%s%i\n", FLAME_GEYSER_DURATION_KEY,
            info->bufs.flame_geyser.duration);
    ft_write_line(file, writer, "%s%i\n", FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY,
            info->bufs.flame_geyser.close_to_tower_d);
    ft_write_line(file, writer, "%s%i\n", FLAME_GEYSER_TOWER_EXPLODE_D_KEY,
            info->bufs.flame_geyser.tower_explode_d);
    ft_write_line(file, writer, "%s%i\n", FLAME_GEYSER_AMOUNT_KEY,
            info->bufs.flame_geyser.amount);
    ft_write_line(file, writer, "%s%i\n", METEOR_STRIKE_DURATION_KEY,
            info->bufs.meteor_strike.duration);
    ft_write_line(file, writer, "%s%i\n", METEOR_STRIKE_ONE_TARGET_D_KEY,
            info->bufs.meteor_strike.one_target_d);
    ft_write_line(file, writer, "%s%i\n", METEOR_STRIKE_TWO_TARGETS_D_KEY,
            info->bufs.meteor_strike.two_targets_d);
    ft_write_line(file, writer, "%s%i\n", METEOR_STRIKE_THREE_TARGETS_D_KEY,
            info->bufs.meteor_strike.three_targets_d);
    ft_write_line(file, writer, "%s%i\n", METEOR_STRIKE_FOUR_TARGETS_D_KEY,
            info->bufs.meteor_strike.four_targets_d);
    ft_write_line(file, writer, "%s%i\n", METEOR_STRIKE_FIVE_TARGETS_D_KEY,
            info->bufs.meteor_strike.five_targets_d);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKE_DURATION_KEY,
            info->bufs.lightning_strike.duration);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKE_AMOUNT_KEY,
            info->bufs.lightning_strike.amount);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKE_DISTANCE_KEY,
            info->bufs.lightning_strike.distance);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKE_DICE_AMOUNT_KEY,
            info->bufs.lightning_strike.dice_amount);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKE_DICE_FACES_KEY,
            info->bufs.lightning_strike.dice_faces);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY,
            info->bufs.lightning_strike.extra_damage);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKEV2_DURATION_KEY,
            info->bufs.lightning_strikeV2.duration);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKEV2_AMOUNT_KEY,
            info->bufs.lightning_strikeV2.amount);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKEV2_DISTANCE_KEY,
            info->bufs.lightning_strikeV2.distance);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY,
            info->bufs.lightning_strikeV2.dice_amount);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKEV2_DICE_FACES_KEY,
            info->bufs.lightning_strikeV2.dice_faces);
    ft_write_line(file, writer, "%s%i\n", LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY,
            info->bufs.lightning_strikeV2.extra_damage);
    ft_write_line(file, writer, "%s%i\n", EARTH_POUNCE_ACTIVE_KEY,
            info->bufs.earth_pounce.active);
    ft_write_line(file, writer, "%s%i\n", EARTH_POUNCE_BASE_DAMAGE_KEY,
            info->bufs.earth_pounce.base_damage);
    ft_write_line(file, writer, "%s%i\n", ARCANE_POUNCE_ACTIVE_KEY,
            info->bufs.arcane_pounce.active);
    ft_write_line(file, writer, "%s%i\n", ARCANE_POUNCE_EREA_DAMAGE_KEY,
            info->bufs.arcane_pounce.erea_damage);
    ft_write_line(file, writer, "%s%i\n", ARCANE_POUNCE_MAGIC_DAMAGE_KEY,
            info->bufs.arcane_pounce.magic_damage);
    ft_write_line(file, writer, "%s%i\n", FROST_BREATH_ACTIVE_KEY,
            info->bufs.frost_breath.active);
    ft_write_line(file, writer, "%s%i\n", FROST_BREATH_DAMAGE_KEY,
            info->bufs.frost_breath.damage);
    ft_write_line(file, writer, "%s%i\n", SHADOW_ILLUSION_ACTIVE_KEY,
            info->bufs.shadow_illusion.active);
    ft_write_line(file, writer, "%s%i\n", SHADOW_ILLUSION_DURATION_KEY,
            info->bufs.shadow_illusion.duration);
    ft_write_line(file, writer, "%s%i\n", BUFF_GROWTH_STACKS_KEY, info->bufs.growth.stacks);
    ft_write_line(file, writer, "%s%s\n", METEOR_STRIKE_TARGET_KEY,
            info->bufs.meteor_strike.target_id);
    if (info->bufs.frost_breath.target_id)
        ft_write_line(file, writer, "%s%s\n", FROST_BREATH_TARGET_ID_KEY,
                info->bufs.frost_breath.target_id);
    if (info->bufs.arcane_pounce.target_id)
        ft_write_line(file, writer, "%s%s\n", ARCANE_POUNCE_TARGET_ID_KEY,
                info->bufs.arcane_pounce.target_id);
    if (info->bufs.earth_pounce.target_id != ft_nullptr)
        ft_write_line(file, writer, "%s%s\n", EARTH_POUNCE_TARGET_ID_KEY,
                info->bufs.earth_pounce.target_id);
    ft_write_line(file, writer, "%s%i\n", REACTION_USED_KEY, info->flags.reaction_used);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_DAMAGE_FLAT_KEY, info->spells.magic_drain.damage_flat);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_DICE_AMOUNT_KEY,
            info->spells.magic_drain.damage_dice_amount);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_DICE_FACES_KEY,
            info->spells.magic_drain.damage_dice_faces);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN_KEY,
            info->spells.magic_drain.spell_slot_total_level_drain);
    if (info->spells.magic_drain.target)
        ft_write_line(file, writer, "%s%s\n", SPELL_MAGIC_DRAIN_TARGET_KEY, info->spells.magic_drain.target);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_DEX_SAVE_KEY, info->spells.magic_drain.dex_save);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_TURNS_PASSED_FROM_LAST_CAST_KEY,
            info->spells.magic_drain.turns_passed_fron_last_cast);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT_KEY,
            info->spells.magic_drain.extra_damage_flat);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_EXTRA_DICE_AMOUNT_KEY,
            info->spells.magic_drain.extra_dice_amount);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_EXTRA_DICE_FACES_KEY,
            info->spells.magic_drain.extra_dice_faces);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_COOLDOWN_KEY, info->spells.magic_drain.cooldown);

    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_DAMAGE_FLAT_KEY, info->debufs.magic_drain.damage_flat);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_DICE_AMOUNT_KEY,
            info->debufs.magic_drain.damage_dice_amount);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_DICE_FACES_KEY,
            info->debufs.magic_drain.damage_dice_faces);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN_KEY,
            info->debufs.magic_drain.spell_slot_total_level_drain);
    ft_npc_write_file_string_set(DEBUFF_MAGIC_DRAIN_CASTER_KEY,
            info->debufs.magic_drain.caster, file, info, writer);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_CON_SAVE_KEY, info->debufs.magic_drain.con_save);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT_KEY,
            info->debufs.magic_drain.extra_damage_flat);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_EXTRA_DICE_AMOUNT_KEY,
            info->debufs.magic_drain.extra_dice_amount);
    ft_write_line(file, writer, "%s%i\n", DEBUFF_MAGIC_DRAIN_EXTRA_DICE_FACES_KEY,
            info->debufs.magic_drain.extra_dice_faces);
    ft_write_line(file, writer, "%s%i\n", SPELL_MAGIC_DRAIN_LEARNED_KEY, info->spells.magic_drain.learned);
    return ;
}

void ft_npc_write_file(t_char * info, t_stats *stats, t_resistance *resistance,
        ft_file &file)
{
    t_json_line_writer    writer_instance;
    t_json_line_writer    *writer;

    if (DEBUG == 1)
        pf_printf("fd = %i\n", file.get_fd());
    if (info->flags.alreaddy_saved)
        return ;
    if (DEBUG == 1)
        pf_printf("saving %s %i\n", info->name, stats->health);
    writer = &writer_instance;
    ft_json_line_writer_init(writer);
    ft_npc_write_file_1(info, stats, file, writer);
    ft_npc_write_file_2(info, resistance, file, writer);
    ft_npc_write_spell_slots(info, file, writer);
    if (writer->error || ft_json_line_writer_flush(writer, file) != 0)
    {
        pf_printf_fd(2, "Error writing JSON save for %s\n", info->name);
        return ;
    }
    info->flags.alreaddy_saved = 1;
    return ;
}
