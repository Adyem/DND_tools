#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "set_utils.hpp"

#define MAKE_BUFF_BLESS(bless, level, target_str) \
    (t_buff) { \
        .target_amount = (bless).target_amount + (bless).upcast_extra_targets, \
        .target = cma_strdup(target_str), \
        .spell_id = BLESS_ID, \
        .dice_faces_mod = (bless).dice_faces + ((bless).upcast_extra_dice_faces \
                * ((level) - (bless).base_level)), \
        .dice_amount_mod = (bless).dice_amount, \
        .mod = (bless).dice_amount + ((bless).upcast_extra_dice_amount * ((level) \
                    - (bless).base_level)), \
        .extra_dice_faces = 0, \
        .extra_dice_amount = 0, \
        .extra_mod = 0, \
        .duration = 10, \
        .buff = 0, \
        .error = 0, \
        .cast_spell = ft_cast_bless_apply_debuf, \
        .spell_name = BLESS_NAME \
    }

void ft_cast_bless(t_char *info, const char **input)
{
    if (info->spells.bless.learned != 1)
    {
        pf_printf_fd(2, "%s hasn't learned the spell bless\n", info->name);
        return ;
    }
        int cast_at_level = ft_prompt_spell_level(info, info->spells.bless.base_level,
                                BLESS_NAME);
    if (cast_at_level == -1)
        return ;
    t_buff buff = MAKE_BUFF_BLESS(info->spells.bless, cast_at_level, input[3]);
    if (!buff.target)
    {
        pf_printf_fd(2, "121-Error: %s allocating memory bless target\n", info->name);
        return ;
    }
    int error = ft_cast_concentration_multi_target_01(info, &buff, input);
    cma_free(buff.target);
    if (error)
    {
        pf_printf_fd(2, "154-Error: %s allocating memory bless target\n", info->name);
        return ;
    }
    pf_printf("%s cast bless on %s\n", info->name, input[3]);
    ft_remove_spell_slot(&info->spell_slots, cast_at_level);
    return ;
}

int ft_cast_bless_apply_debuf(t_char * target, const char **input, t_buff *buff)
{

    (void)buff;
    if (target)
    {
        if (ft_is_caster_name_present(&target->bufs.bless.caster_name, input[0]))
        {
            pf_printf_fd(2, "102-Error: Caster name already present\n");
            return (1);
        }
        if (ft_update_caster_name(&target->bufs.bless.caster_name, input[0]))
            return (2);
    }

    if (DEBUG == 1 && target)
    {
        size_t              index;
        size_t              count;
        const ft_string    *names;

        count = target->bufs.bless.caster_name.size();
        if (count > 0)
        {
            names = ft_set_get_raw_data(target->bufs.bless.caster_name);
            if (names)
            {
                index = 0;
                while (index < count)
                {
                    pf_printf("%s has cast bless\n", names[index].c_str());
                    index++;
                }
            }
        }
    }
    if (target)
    {
        target->bufs.bless.duration = buff->duration;
        target->bufs.bless.dice_amount_mod = buff->dice_amount_mod;
        target->bufs.bless.dice_faces_mod = buff->dice_faces_mod;
        target->bufs.bless.base_mod = buff->mod;
        print_bless(target);
    }
    return (0);
}

void    ft_concentration_remove_bless(t_char * character,
            t_target_data *targets_data)
{
    int target_index = 0;
    while (targets_data->target[target_index])
    {
        targets_data->target[target_index]->bufs.bless.caster_name.remove(
            ft_string(character->name));
        target_index++;
    }
    character->concentration.concentration = 0;
    character->concentration.spell_id = 0;
    character->concentration.dice_amount_mod = 0;
    character->concentration.dice_faces_mod = 0;
    character->concentration.base_mod = 0;
    character->concentration.targets = ft_nullptr;
    cma_free_double(character->concentration.targets);
    return ;
}
