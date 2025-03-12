#include "character.hpp"
#include "dnd_tools.hpp"
#include "initialize.hpp"
#include "identification.hpp"

void	ft_cast_magic_drain(t_char *info)
{
	t_buff	buff_info = INITIALIZE_T_BUFF;

	buff_info.spell_name = MAGIC_DRAIN_NAME;
	buff_info.spell_id = MAGIC_DRAIN_ID;
	buff_info.extra_mod = info->spells.magic_drain.damage_flat
		+ info->spells.magic_drain.extra_damage_flat;
	buff_info.dice_amount_mod = info->spells.magic_drain.damage_dice_amount
		+ info->spells.magic_drain.extra_dice_amount;
	buff_info.dice_faces_mod = info->spells.magic_drain.damage_dice_faces
		+ info->spells.magic_drain.extra_dice_faces;
	(void)buff_info;
	(void)info;
	return ;
}
