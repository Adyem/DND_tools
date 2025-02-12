#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"

static int	ft_check_mainhand(t_char * info)
{
	if (info->equipment.offhand_weapon.slot == SLOT_TWO_HANDED_WEAPON)
	{
		pf_printf_fd(2, "135-Error: Two-handed weapon in offhand slot\n");
		return (1);
	}
	if (info->equipment.weapon.slot == SLOT_TWO_HANDED_WEAPON)
		return (0);
	if (info->equipment.weapon.slot != SLOT_NONE && 
	    !(info->equipment.weapon.slot & SLOT_WEAPON))
	{
		pf_printf_fd(2, "136-Error: Weapon is not in the correct slot\n");
		return (1);
	}
	if (info->equipment.offhand_weapon.slot != SLOT_NONE)
	{
		if (!(info->equipment.offhand_weapon.slot & SLOT_OFFHAND_WEAPON))
		{
			pf_printf_fd(2, "137-Error: Offhand weapon is not in the correct slot\n");
			return (2);
		}
	}
	return (0);
}

static int	ft_check_slot(t_equipment_id equipment_slot, int slot_type,
				const char *error_message, int error_code)
{
	if (equipment_slot.slot != SLOT_NONE && !(equipment_slot.slot & slot_type))
	{
		pf_printf_fd(2, "%s\n", error_message);
		return error_code;
	}
	return (0);
}

int	ft_check_equipment_slots(t_char * info)
{
	int	error;

	error = 0;
	error += ft_check_mainhand(info);
	error += ft_check_slot(info->equipment.ranged_weapon, SLOT_RANGED_WEAPON,
			"125-Error: Ranged weapon is not in the correct slot.", 3);
	error += ft_check_slot(info->equipment.armor, SLOT_ARMOR,
			"126-Error: Armor is not in the correct slot.", 4);
	error += ft_check_slot(info->equipment.helmet, SLOT_HELMET,
			"127-Error: Helmet is not in the correct slot.", 5);
	error += ft_check_slot(info->equipment.shield, SLOT_SHIELD,
			"128-Error: Shield is not in the correct slot.", 6);
	error += ft_check_slot(info->equipment.boots, SLOT_BOOTS,
			"129-Error: Boots are not in the correct slot.", 7);
	error += ft_check_slot(info->equipment.gloves, SLOT_GLOVES,
			"130-Error: Gloves are not in the correct slot.", 8);
	error += ft_check_slot(info->equipment.amulet, SLOT_AMULET,
			"131-Error: Amulet is not in the correct slot.", 9);
	error += ft_check_slot(info->equipment.ring_01, SLOT_RING_01,
			"132-Error: First ring is not in the correct slot.", 10);
	error += ft_check_slot(info->equipment.ring_02, SLOT_RING_02,
			"133-Error: Second ring is not in the correct slot.", 11);
	error += ft_check_slot(info->equipment.belt, SLOT_BELT,
			"134-Error: Belt is not in the correct slot.", 12);
	return (error);
}
