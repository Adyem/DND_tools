#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <cstdlib>
#include <cstring>

static const	t_buff BUFF_BLESS =
{
	.target_amount = 1,
	.target = ft_nullptr,
	.spell_name = "bless",
	.spell_id = BLESS_ID,
	.dice_faces_mod = 6,
	.dice_amount_mod = 1,
	.extra_mod = 0,
	.duration = 10,
	.buff = 0,
	.error = 0,
	.cast_spell = ft_cast_bless_apply_debuf,
};

void ft_cast_bless(ft_sharedptr<t_char> &info, const char **input)
{
	if (info->spells.bless.learned != 1)
	{
		pf_printf_fd(2, "%s hasn't learned the spell bless\n", info->name);
		return ;
	}
	int cast_at_level = ft_prompt_spell_level(info, info->spells.bless.base_level);
	if (cast_at_level == -1)
		return ;
    t_buff	buff = BUFF_BLESS;
	int		error = 0;
	buff.dice_amount_mod = info->spells.bless.dice_amount;
	buff.dice_faces_mod = info->spells.bless.dice_faces;
	buff.extra_mod = info->spells.bless.extra_damage;
	int upcast_level = cast_at_level - info->spells.bless.base_level;
	if (upcast_level > 0)
	{
		buff.dice_amount_mod += info->spells.bless.upcast_extra_dice_amount * upcast_level;
		buff.dice_faces_mod += info->spells.bless.upcast_extra_dice_face * upcast_level;
		buff.extra_mod += info->spells.bless.upcast_extra_damage * upcast_level;
	}
	buff.target = cma_strdup(input[3], false);
	if (!buff.target)
	{
		pf_printf_fd(2, "121-Error allocating memory bless target");
		return ;
	}
    error = ft_cast_concentration(info, input, &buff);
	cma_free(buff.target);
	if (error)
		return ;
	pf_printf("%s cast bless on %s\n", info->name, input[3]);
	ft_remove_spell_slot(&info->spell_slots, cast_at_level);
    return ;
}

static int ft_is_caster_name_present(char **caster_name_list, const char *name)
{
    if (!caster_name_list || !name)
        return (0);
    int index = 0;
    while (caster_name_list[index])
    {
        if (ft_strcmp_dnd(caster_name_list[index], name) == 0)
            return (1);
        index++;
    }
    return (0);
}

int ft_cast_bless_apply_debuf(ft_sharedptr<t_char> &target, const char **input, t_buff *buff)
{

    (void)buff;
    if (target)
    {
        if (ft_is_caster_name_present(target->bufs.bless.caster_name, input[0]))
        {
            pf_printf_fd(2, "102-Error: Caster name already present\n");
            return (1);
        }
        if (ft_update_caster_name(&target->bufs.bless.caster_name, input[0]))
            return (2);
    }

    if (DEBUG == 1 && target)
    {
        int index = 0;
        while (target->bufs.bless.caster_name
				&& target->bufs.bless.caster_name[index])
        {
            pf_printf("%s has cast bless\n", target->bufs.bless.caster_name[index]);
            index++;
        }
    }
    target->debufs.bless.amount++;
    return (0);
}

void	ft_concentration_remove_bless(ft_sharedptr<t_char> &character,
			t_target_data *targets_data)
{
	int target_index = 0;
	int caster_index;

	while (targets_data->target[target_index])
	{
		caster_index = 0;
		while (targets_data->target[target_index]->bufs.bless.caster_name[caster_index])
		{
			if (ft_strcmp_dnd(targets_data->target[target_index]->bufs.bless.caster_name
					[caster_index],
				character->name) == 0)
			{
				cma_free(targets_data->target[target_index]->bufs.bless.caster_name
						[caster_index]);
				targets_data->target[target_index]->bufs.bless.caster_name[caster_index]
					= ft_nullptr;
				targets_data->target[target_index]->bufs.bless.amount--;
			}
			caster_index++;
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
