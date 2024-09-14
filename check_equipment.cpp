#include <iostream>
#include "character.hpp"
#include "identification.hpp"
#include "dnd_tools.hpp"

int	ft_check_equipment_slots(t_char *info)
{
	int error = 0;

	if (info->equipment.weapon.slot != SLOT_NONE && !(info->equipment.weapon.slot & SLOT_WEAPON))
	{
		std::cerr << "Error: Weapon is not in the correct slot.\n";
		error += 1;
	}
	if (info->equipment.offhand_weapon.slot != SLOT_NONE && !(info->equipment.offhand_weapon.slot & SLOT_OFFHAND_WEAPON))
	{
		std::cerr << "Error: Offhand weapon is not in the correct slot.\n";
		error += 2;
	}
	if (info->equipment.ranged_weapon.slot != SLOT_NONE && !(info->equipment.ranged_weapon.slot & SLOT_RANGED_WEAPON))
	{
		std::cerr << "Error: Ranged weapon is not in the correct slot.\n";
		error += 3;
	}
	if (info->equipment.armor.slot != SLOT_NONE && !(info->equipment.armor.slot & SLOT_ARMOR))
	{
		std::cerr << "Error: Armor is not in the correct slot.\n";
		error += 4;
	}
	if (info->equipment.helmet.slot != SLOT_NONE && !(info->equipment.helmet.slot & SLOT_HELMET))
	{
		std::cerr << "Error: Helmet is not in the correct slot.\n";
		error += 5;
	}
	if (info->equipment.shield.slot != SLOT_NONE && !(info->equipment.shield.slot & SLOT_SHIELD))
	{
		std::cerr << "Error: Shield is not in the correct slot.\n";
		error += 6;
	}
	if (info->equipment.boots.slot != SLOT_NONE && !(info->equipment.boots.slot & SLOT_BOOTS))
	{
		std::cerr << "Error: Boots are not in the correct slot.\n";
		error += 7;
	}
	if (info->equipment.gloves.slot != SLOT_NONE && !(info->equipment.gloves.slot & SLOT_GLOVES))
	{
		std::cerr << "Error: Gloves are not in the correct slot.\n";
		error += 8;
	}
	if (info->equipment.amulet.slot != SLOT_NONE && !(info->equipment.amulet.slot & SLOT_AMULET))
	{
		std::cerr << "Error: Amulet is not in the correct slot.\n";
		error += 9;
	}
	if (info->equipment.ring_01.slot != SLOT_NONE && !(info->equipment.ring_01.slot & SLOT_RING_01))
	{
		std::cerr << "Error: First ring is not in the correct slot.\n";
		error += 10;
	}
	if (info->equipment.ring_02.slot != SLOT_NONE && !(info->equipment.ring_02.slot & SLOT_RING_02))
	{
		std::cerr << "Error: Second ring is not in the correct slot.\n";
		error += 11;
	}
	if (info->equipment.belt.slot != SLOT_NONE && !(info->equipment.belt.slot & SLOT_BELT))
	{
		std::cerr << "Error: Belt is not in the correct slot.\n";
		error += 12;
	}
	return (error);
}
