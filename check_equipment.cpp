#include "character.hpp"
#include "dnd_tools.hpp"
#include <iostream>
#include "identification.hpp"

static void	ft_check_mainhand(t_char *info, int *error)
{
	bool	is_two_handed_weapon;

	if (info->equipment.weapon.slot != SLOT_NONE && !(info->equipment.weapon.slot & SLOT_WEAPON))
	{
		std::cerr << "Error: Weapon is not in the correct slot.\n";
		*error += 1;
	}
	is_two_handed_weapon = !(info->equipment.weapon.slot & SLOT_OFFHAND_WEAPON);
	if (info->equipment.offhand_weapon.slot != SLOT_NONE)
	{
		if (!(info->equipment.offhand_weapon.slot & SLOT_OFFHAND_WEAPON))
		{
			std::cerr << "Error: Offhand weapon is not in the correct slot.\n";
			*error += 2;
		}
		else if (is_two_handed_weapon)
		{
			std::cerr << "Error: Cannot equip offhand weapon with a two-handed weapon in the main hand.\n";
			*error += 13;
		}
	}
}

static void	ft_check_slot(t_equipment_id equipment_slot, int slot_type, const char *error_message, int *error, int error_code)
{
	if (equipment_slot.slot != SLOT_NONE && !(equipment_slot.slot & slot_type))
	{
		std::cerr << error_message << '\n';
		*error += error_code;
	}
}

int	ft_check_equipment_slots(t_char *info)
{
	int	error = 0;

	ft_check_mainhand(info, &error);
	ft_check_slot(info->equipment.ranged_weapon, SLOT_RANGED_WEAPON, "Error: Ranged weapon is not in the correct slot.", &error, 3);
	ft_check_slot(info->equipment.armor, SLOT_ARMOR, "Error: Armor is not in the correct slot.", &error, 4);
	ft_check_slot(info->equipment.helmet, SLOT_HELMET, "Error: Helmet is not in the correct slot.", &error, 5);
	ft_check_slot(info->equipment.shield, SLOT_SHIELD, "Error: Shield is not in the correct slot.", &error, 6);
	ft_check_slot(info->equipment.boots, SLOT_BOOTS, "Error: Boots are not in the correct slot.", &error, 7);
	ft_check_slot(info->equipment.gloves, SLOT_GLOVES, "Error: Gloves are not in the correct slot.", &error, 8);
	ft_check_slot(info->equipment.amulet, SLOT_AMULET, "Error: Amulet is not in the correct slot.", &error, 9);
	ft_check_slot(info->equipment.ring_01, SLOT_RING_01, "Error: First ring is not in the correct slot.", &error, 10);
	ft_check_slot(info->equipment.ring_02, SLOT_RING_02, "Error: Second ring is not in the correct slot.", &error, 11);
	ft_check_slot(info->equipment.belt, SLOT_BELT, "Error: Belt is not in the correct slot.", &error, 12);
	return (error);
}
