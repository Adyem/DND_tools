#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"

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
		.duration = 10, \
		.buff = 0, \
		.error = 0, \
		.cast_spell = ft_magic_drain_apply_debuff, \
		.spell_name = MAGIC_DRAIN_NAME \
	}

void	ft_cast_magic_drain(t_char *info, const char **input)
{
	if (info->spells.magic_drain.cooldown != 0)
	{
		pf_printf_fd(2, "%s Magic Drain is on cooldown", info->name);
		return ;
	}
	t_buff buff_info = MAKE_BUFF_MAGIC_DRAIN(info->spells.magic_drain, input[3]);
	int error = ft_cast_concentration(info, input, &buff_info);
	cma_free(buff_info.target);
	if (error)
		return ;
	info->spells.magic_drain.cooldown = 2;
	return ;
}

int	ft_magic_drain_apply_debuff(t_char *target, const char **input, t_buff *buff)
{
	t_debuff_magic_drain *debuff_magic_drain = &target->debufs.magic_drain;

	(void)target;
	(void)input;
	(void)buff;
	(void)debuff_magic_drain;
	return (0);
}

void	ft_concentration_remove_magic_drain(t_char *character, t_target_data *targets_data)
{
	(void)character;
	(void)targets_data;
	return ;
}
