#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <cstdlib>
#include <cstring>

static const	t_buff BUFF_HUNTERS_MARK =
{
	.target_amount = 1,
	.target = ft_nullptr,
	.spell_name = "hunters mark",
	.spell_id = HUNTERS_MARK_ID,
	.dice_faces_mod = 6,
	.dice_amount_mod = 1,
	.duration = 10,
	.buff = 0,
	.error = 0,
	.cast_spell = ft_cast_hunters_mark_apply_debuf,
};

void ft_cast_hunters_mark(t_char *info, const char **input)
{
	if (info->spells.hunters_mark.learned != 1)
		pf_printf_fd(2, "%s hasn't learned the spell", info->name);
    t_buff	buff = BUFF_HUNTERS_MARK;
	int		error = 0;
	buff.target = cma_strdup(input[3], false);
	if (!buff.target)
	{
		pf_printf_fd(2, "121-Error allocating memory hunters mark target");
		return ;
	}
    error = ft_cast_concentration(info, input, &buff);
	cma_free(buff.target);
	if (error)
		return ;
	pf_printf("%s cast hunters mark on %s\n", info->name, input[3]);
    return ;
}

static int ft_is_caster_name_present(char **caster_name_list, const char *name)
{
    int i;

    if (!caster_name_list || !name)
        return (0);
    i = 0;
    while (caster_name_list[i])
    {
        if (ft_strcmp_dnd(caster_name_list[i], name) == 0)
            return (1);
        i++;
    }
    return (0);
}

int ft_cast_hunters_mark_apply_debuf(t_char *target, const char **input, t_buff *buff)
{
    int i;

    (void)buff;
    if (DEBUG == 1)
        pf_printf("setting the caster name in the target %s %p\n", input[0], (void *)target);
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
        i = 0;
        while (target->debufs.hunters_mark.caster_name && target->debufs.hunters_mark.caster_name[i])
        {
            pf_printf("%s has cast hunter's mark\n", target->debufs.hunters_mark.caster_name[i]);
            i++;
        }
    }
    target->debufs.hunters_mark.amount++;
    return (0);
}

void	ft_concentration_remove_hunters_mark(t_char *info, t_target_data *targets)
{
	int i = 0;
	int	j;

	while (targets->target[i])
	{
		j = 0;
		while (targets->target[i]->debufs.hunters_mark.caster_name[j])
		{
			if (ft_strcmp_dnd(targets->target[i]->debufs.hunters_mark.caster_name[j],
						info->name) == 0)
			{
				cma_free(targets->target[i]->debufs.hunters_mark.caster_name[j]);
				targets->target[i]->debufs.hunters_mark.caster_name[j] = ft_nullptr;
				targets->target[i]->debufs.hunters_mark.amount--;
			}
			j++;
		}
		i++;
	}
    info->concentration.concentration = 0;
    info->concentration.spell_id = 0;
    info->concentration.dice_amount_mod = 0;
    info->concentration.dice_faces_mod = 0;
    info->concentration.base_mod = 0;
	cma_free_double(info->concentration.targets);
    info->concentration.targets = ft_nullptr;
    info->bufs.chaos_armor.duration = 0;
	return ;
}
