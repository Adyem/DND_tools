#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <cstdlib>
#include <cstring>

#define MAKE_BUFF_HUNTERS_MARK(hunters_mark, level, target_str) \
	(t_buff){ \
		.target_amount = 1, \
		.target = cma_strdup(target_str), \
		.spell_id = HUNTERS_MARK_ID, \
		.dice_faces_mod = (hunters_mark).dice_faces + ((hunters_mark).upcast_extra_dice_face \
				* ((((level) - (hunters_mark).base_level) + abs((level) \
				- (hunters_mark).base_level)) / 2)), \
		.dice_amount_mod = (hunters_mark).dice_amount + ((hunters_mark).upcast_extra_dice_amount \
				* ((((level) - (hunters_mark).base_level) + abs((level) \
				- (hunters_mark).base_level)) / 2)), \
		.mod = (hunters_mark).extra_damage + ((hunters_mark).upcast_extra_damage * ((((level) \
				- (hunters_mark).base_level) + abs((level) \
				- (hunters_mark).base_level)) / 2)), \
		.extra_dice_faces = 0, \
		.extra_dice_amount = 0, \
		.extra_mod = 0, \
		.duration = 10, \
		.buff = 0, \
		.error = 0, \
		.cast_spell = ft_cast_hunters_mark_apply_debuf, \
		.spell_name = HUNTERS_MARK_NAME \
	}

void ft_cast_hunters_mark(t_char * info, const char **input)
{
	if (info->spells.hunters_mark.learned == 1)
	{
		pf_printf_fd(2, "%s hasn't learned the spell hunters mark\n", info->name);
		return ;
	}
	int cast_at_level = ft_prompt_spell_level(info, info->spells.hunters_mark.base_level);
	if (cast_at_level == -1)
		return ;
	t_buff buff = MAKE_BUFF_HUNTERS_MARK(info->spells.hunters_mark, cast_at_level, input[3]);
	if (!buff.target)
	{
		pf_printf_fd(2, "121-Error allocating memory hunters mark target");
		return ;
	}
	int error = ft_cast_concentration(info, input, &buff);
	cma_free(buff.target);
	if (error)
		return ;
	pf_printf("%s cast hunters mark on %s\n", info->name, input[3]);
	ft_remove_spell_slot(&info->spell_slots, cast_at_level);
	return ;
}

int ft_cast_hunters_mark_apply_debuf(t_char *target, const char **input, t_buff *buff)
{

    (void)buff;
    if (target)
    {
        if (ft_is_caster_name_present(target->debufs.hunters_mark.caster_name, input[0]))
        {
            pf_printf_fd(2, "102-Error: Caster name already present\n");
            return (1);
        }
        if (ft_update_caster_name(&target->debufs.hunters_mark.caster_name, input[0]))
            return (2);
    }
    if (DEBUG == 1 && target)
    {
        int index = 0;
        while (target->debufs.hunters_mark.caster_name
				&& target->debufs.hunters_mark.caster_name[index])
        {
            pf_printf("%s has cast hunter's mark\n", target->debufs.hunters_mark.caster_name[index]);
            index++;
        }
    }
    target->debufs.hunters_mark.amount++;
    return (0);
}

void	ft_concentration_remove_hunters_mark(t_char *character, t_target_data *targets_data)
{
	int target_index = 0;
	int caster_index;

	while (targets_data->target[target_index])
	{
		caster_index = 0;
		while (targets_data->target[target_index]->debufs.hunters_mark.caster_name[caster_index])
		{
			if (ft_strcmp_dnd(targets_data->target[target_index]->debufs.hunters_mark.caster_name
						[caster_index],
					character->name) == 0)
			{
				cma_free(targets_data->target[target_index]->debufs.hunters_mark.caster_name
						[caster_index]);
				targets_data->target[target_index]->debufs.hunters_mark.caster_name[caster_index]
					= ft_nullptr;
				targets_data->target[target_index]->debufs.hunters_mark.amount--;
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
