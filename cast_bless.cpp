#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <cstdlib>
#include <cstring>

#define MAKE_BUFF_BLESS(bless, level, target_str) \
	(t_buff){ \
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
	int cast_at_level = ft_prompt_spell_level(info, info->spells.bless.base_level);
	if (cast_at_level == -1)
		return ;
	t_buff buff = MAKE_BUFF_BLESS(info->spells.bless, cast_at_level, input[3]);
	if (!buff.target)
	{
		pf_printf_fd(2, "121-Error allocating memory bless target");
		return ;
	}
	int error = ft_cast_concentration_multi_target_01(info, &buff, input);
	cma_free(buff.target);
	if (error)
		return ;
	pf_printf("%s cast bless on %s\n", info->name, input[3]);
	ft_remove_spell_slot(&info->spell_slots, cast_at_level);
	return ;
}

int ft_cast_bless_apply_debuf(t_char * target, const char **input, t_buff *buff)
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
    return (0);
}

void	ft_concentration_remove_bless(t_char * character,
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
