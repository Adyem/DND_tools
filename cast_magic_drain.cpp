#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"

#define MAKE_BUFF_MAGIC_DRAIN(magic_drain, target_str) \
    (t_buff){ \
        .target_amount = 1, \
        .target = cma_strdup(target_str), \
        .spell_id = MAGIC_DRAIN_ID, \
        .dice_faces_mod = (magic_drain).damage_dice_faces, \
        .dice_amount_mod = (magic_drain).damage_dice_amount, \
        .mod = (magic_drain).damage_flat, \
        .extra_dice_faces = (magic_drain).extra_dice_faces, \
        .extra_dice_amount = (magic_drain).extra_dice_amount, \
        .extra_mod = (magic_drain).extra_damage_flat, \
        .duration = 0, \
        .buff = 0, \
        .error = 0, \
        .cast_spell = ft_magic_drain_apply_debuff, \
        .spell_name = MAGIC_DRAIN_NAME \
    }

static bool generate_magic_drain_message(const t_char *info, ft_string &out_message)
{
    char *dex_save = cma_itoa(info->spells.magic_drain.dex_save);
    if (!dex_save)
    {
        pf_printf_fd(2, "151-Error: %s Magic Drain allocation failure", info->name);
        return (true);
    }
    ft_string temp = "the target needs to succeed on a DC ";
    if (temp.get_error())
    {
        pf_printf_fd(2, "152-Error: %s Magic Drain allocation failure", info->name);
        cma_free(dex_save);
        return (true);
    }
    out_message = temp + dex_save + " to avoid the spell";
    cma_free(dex_save);

    if (out_message.get_error())
    {
        pf_printf_fd(2, "153-Error: %s Magic Drain allocation failure", info->name);
        return (true);
    }
    return (false);
}

void    ft_cast_magic_drain(t_char *info, const char **input)
{
    if (info->spells.magic_drain.cooldown != 0)
    {
        pf_printf("%s Magic Drain is on cooldown", info->name);
        return ;
    }
    ft_string message;
    if (generate_magic_drain_message(info, message))
        return ;
    int confirm;

    confirm = ft_readline_confirm(message);
    if (confirm == RL_INPUT_CANCEL)
    {
        pf_printf("Magic Drain cancelled.\n");
        return ;
    }
    if (confirm != 0)
        return ;
    t_buff buff_info = MAKE_BUFF_MAGIC_DRAIN(info->spells.magic_drain, input[3]);
    int error = ft_cast_concentration(info, input, &buff_info);
    cma_free(buff_info.target);
    if (error)
        return ;
    info->spells.magic_drain.cooldown = 2;
}

int    ft_magic_drain_apply_debuff(t_char *target, const char **input, t_buff *buff)
{
    (void)buff;
    if (target)
    {
        if (ft_is_caster_name_present(&target->debufs.magic_drain.caster, input[0]))
        {
            pf_printf_fd(2, "102-Error: Caster name already present\n");
            return (1);
        }
        if (ft_update_caster_name(&target->debufs.magic_drain.caster, input[0]))
            return (2);
    }
    if (DEBUG == 1 && target)
    {
        size_t              index;
        size_t              count;
        const ft_string    *names;

        count = target->debufs.magic_drain.caster.size();
        if (count > 0)
        {
            names = target->debufs.magic_drain.caster.data();
            if (names)
            {
                index = 0;
                while (index < count)
                {
                    pf_printf("%s has cast magic drain\n", names[index].c_str());
                    index++;
                }
            }
        }
    }
    target->debufs.magic_drain.amount++;
    return (0);
}

void    ft_concentration_remove_magic_drain(t_char *character, t_target_data *targets_data)
{
    int target_index = 0;
    while (targets_data->target[target_index])
    {
        ft_string                       caster_name(character->name);
        ft_set<ft_string>               *caster_set;
        const ft_string                *existing_name;

        if (!caster_name.get_error())
        {
            caster_set = &targets_data->target[target_index]->debufs.magic_drain.caster;
            existing_name = caster_set->find(caster_name);
            if (existing_name)
            {
                caster_set->remove(caster_name);
                if (targets_data->target[target_index]->debufs.magic_drain.amount > 0)
                    targets_data->target[target_index]->debufs.magic_drain.amount--;
            }
        }
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
