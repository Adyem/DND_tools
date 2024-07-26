#include "dnd_tools.h"

int	ft_calculate_acid_dr(t_char *info)
{
	int acid_dr;

	acid_dr = info->equipment.weapon.flat_dr.acid;
	acid_dr += info->equipment.offhand_weapon.flat_dr.acid;
	acid_dr += info->equipment.ranged_weapon.flat_dr.acid;
	acid_dr += info->equipment.armor.flat_dr.acid;
	acid_dr += info->equipment.helmet.flat_dr.acid;
	acid_dr += info->equipment.shield.flat_dr.acid;
	acid_dr += info->equipment.boots.flat_dr.acid;
	acid_dr += info->equipment.gloves.flat_dr.acid;
	acid_dr += info->equipment.amulet.flat_dr.acid;
	acid_dr += info->equipment.ring_01.flat_dr.acid;
	acid_dr += info->equipment.ring_02.flat_dr.acid;
	acid_dr += info->equipment.belt.flat_dr.acid;
	return (acid_dr);
}

int	ft_calculate_bludgeoning_dr(t_char *info)
{
	int bludgeoning_dr;

	bludgeoning_dr = info->equipment.weapon.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.offhand_weapon.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.ranged_weapon.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.armor.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.helmet.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.shield.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.boots.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.gloves.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.amulet.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.ring_01.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.ring_02.flat_dr.bludgeoning;
	bludgeoning_dr += info->equipment.belt.flat_dr.bludgeoning;
	return (bludgeoning_dr);
}

int	ft_calculate_cold_dr(t_char *info)
{
	int cold_dr;

	cold_dr = info->equipment.weapon.flat_dr.cold;
	cold_dr += info->equipment.offhand_weapon.flat_dr.cold;
	cold_dr += info->equipment.ranged_weapon.flat_dr.cold;
	cold_dr += info->equipment.armor.flat_dr.cold;
	cold_dr += info->equipment.helmet.flat_dr.cold;
	cold_dr += info->equipment.shield.flat_dr.cold;
	cold_dr += info->equipment.boots.flat_dr.cold;
	cold_dr += info->equipment.gloves.flat_dr.cold;
	cold_dr += info->equipment.amulet.flat_dr.cold;
	cold_dr += info->equipment.ring_01.flat_dr.cold;
	cold_dr += info->equipment.ring_02.flat_dr.cold;
	cold_dr += info->equipment.belt.flat_dr.cold;
	return (cold_dr);
}

int	ft_calculate_fire_dr(t_char *info)
{
	int fire_dr;

	fire_dr = info->equipment.weapon.flat_dr.fire;
	fire_dr += info->equipment.offhand_weapon.flat_dr.fire;
	fire_dr += info->equipment.ranged_weapon.flat_dr.fire;
	fire_dr += info->equipment.armor.flat_dr.fire;
	fire_dr += info->equipment.helmet.flat_dr.fire;
	fire_dr += info->equipment.shield.flat_dr.fire;
	fire_dr += info->equipment.boots.flat_dr.fire;
	fire_dr += info->equipment.gloves.flat_dr.fire;
	fire_dr += info->equipment.amulet.flat_dr.fire;
	fire_dr += info->equipment.ring_01.flat_dr.fire;
	fire_dr += info->equipment.ring_02.flat_dr.fire;
	fire_dr += info->equipment.belt.flat_dr.fire;
	return (fire_dr);
}

int	ft_calculate_force_dr(t_char *info)
{
	int force_dr;

	force_dr = info->equipment.weapon.flat_dr.force;
	force_dr += info->equipment.offhand_weapon.flat_dr.force;
	force_dr += info->equipment.ranged_weapon.flat_dr.force;
	force_dr += info->equipment.armor.flat_dr.force;
	force_dr += info->equipment.helmet.flat_dr.force;
	force_dr += info->equipment.shield.flat_dr.force;
	force_dr += info->equipment.boots.flat_dr.force;
	force_dr += info->equipment.gloves.flat_dr.force;
	force_dr += info->equipment.amulet.flat_dr.force;
	force_dr += info->equipment.ring_01.flat_dr.force;
	force_dr += info->equipment.ring_02.flat_dr.force;
	force_dr += info->equipment.belt.flat_dr.force;
	return (force_dr);
}

int	ft_calculate_lightning_dr(t_char *info)
{
	int lightning_dr;

	lightning_dr = info->equipment.weapon.flat_dr.lightning;
	lightning_dr += info->equipment.offhand_weapon.flat_dr.lightning;
	lightning_dr += info->equipment.ranged_weapon.flat_dr.lightning;
	lightning_dr += info->equipment.armor.flat_dr.lightning;
	lightning_dr += info->equipment.helmet.flat_dr.lightning;
	lightning_dr += info->equipment.shield.flat_dr.lightning;
	lightning_dr += info->equipment.boots.flat_dr.lightning;
	lightning_dr += info->equipment.gloves.flat_dr.lightning;
	lightning_dr += info->equipment.amulet.flat_dr.lightning;
	lightning_dr += info->equipment.ring_01.flat_dr.lightning;
	lightning_dr += info->equipment.ring_02.flat_dr.lightning;
	lightning_dr += info->equipment.belt.flat_dr.lightning;
	return (lightning_dr);
}

int	ft_calculate_necrotic_dr(t_char *info)
{
	int necrotic_dr;

	necrotic_dr = info->equipment.weapon.flat_dr.necrotic;
	necrotic_dr += info->equipment.offhand_weapon.flat_dr.necrotic;
	necrotic_dr += info->equipment.ranged_weapon.flat_dr.necrotic;
	necrotic_dr += info->equipment.armor.flat_dr.necrotic;
	necrotic_dr += info->equipment.helmet.flat_dr.necrotic;
	necrotic_dr += info->equipment.shield.flat_dr.necrotic;
	necrotic_dr += info->equipment.boots.flat_dr.necrotic;
	necrotic_dr += info->equipment.gloves.flat_dr.necrotic;
	necrotic_dr += info->equipment.amulet.flat_dr.necrotic;
	necrotic_dr += info->equipment.ring_01.flat_dr.necrotic;
	necrotic_dr += info->equipment.ring_02.flat_dr.necrotic;
	necrotic_dr += info->equipment.belt.flat_dr.necrotic;
	return (necrotic_dr);
}

int	ft_calculate_piercing_dr(t_char *info)
{
	int piercing_dr;

	piercing_dr = info->equipment.weapon.flat_dr.piercing;
	piercing_dr += info->equipment.offhand_weapon.flat_dr.piercing;
	piercing_dr += info->equipment.ranged_weapon.flat_dr.piercing;
	piercing_dr += info->equipment.armor.flat_dr.piercing;
	piercing_dr += info->equipment.helmet.flat_dr.piercing;
	piercing_dr += info->equipment.shield.flat_dr.piercing;
	piercing_dr += info->equipment.boots.flat_dr.piercing;
	piercing_dr += info->equipment.gloves.flat_dr.piercing;
	piercing_dr += info->equipment.amulet.flat_dr.piercing;
	piercing_dr += info->equipment.ring_01.flat_dr.piercing;
	piercing_dr += info->equipment.ring_02.flat_dr.piercing;
	piercing_dr += info->equipment.belt.flat_dr.piercing;
	return (piercing_dr);
}

int	ft_calculate_poison_dr(t_char *info)
{
	int poison_dr;

	poison_dr = info->equipment.weapon.flat_dr.poison;
	poison_dr += info->equipment.offhand_weapon.flat_dr.poison;
	poison_dr += info->equipment.ranged_weapon.flat_dr.poison;
	poison_dr += info->equipment.armor.flat_dr.poison;
	poison_dr += info->equipment.helmet.flat_dr.poison;
	poison_dr += info->equipment.shield.flat_dr.poison;
	poison_dr += info->equipment.boots.flat_dr.poison;
	poison_dr += info->equipment.gloves.flat_dr.poison;
	poison_dr += info->equipment.amulet.flat_dr.poison;
	poison_dr += info->equipment.ring_01.flat_dr.poison;
	poison_dr += info->equipment.ring_02.flat_dr.poison;
	poison_dr += info->equipment.belt.flat_dr.poison;
	return (poison_dr);
}

int	ft_calculate_psychic_dr(t_char *info)
{
	int psychic_dr;

	psychic_dr = info->equipment.weapon.flat_dr.psychic;
	psychic_dr += info->equipment.offhand_weapon.flat_dr.psychic;
	psychic_dr += info->equipment.ranged_weapon.flat_dr.psychic;
	psychic_dr += info->equipment.armor.flat_dr.psychic;
	psychic_dr += info->equipment.helmet.flat_dr.psychic;
	psychic_dr += info->equipment.shield.flat_dr.psychic;
	psychic_dr += info->equipment.boots.flat_dr.psychic;
	psychic_dr += info->equipment.gloves.flat_dr.psychic;
	psychic_dr += info->equipment.amulet.flat_dr.psychic;
	psychic_dr += info->equipment.ring_01.flat_dr.psychic;
	psychic_dr += info->equipment.ring_02.flat_dr.psychic;
	psychic_dr += info->equipment.belt.flat_dr.psychic;
	return (psychic_dr);
}

int	ft_calculate_radiant_dr(t_char *info)
{
	int radiant_dr;

	radiant_dr = info->equipment.weapon.flat_dr.radiant;
	radiant_dr += info->equipment.offhand_weapon.flat_dr.radiant;
	radiant_dr += info->equipment.ranged_weapon.flat_dr.radiant;
	radiant_dr += info->equipment.armor.flat_dr.radiant;
	radiant_dr += info->equipment.helmet.flat_dr.radiant;
	radiant_dr += info->equipment.shield.flat_dr.radiant;
	radiant_dr += info->equipment.boots.flat_dr.radiant;
	radiant_dr += info->equipment.gloves.flat_dr.radiant;
	radiant_dr += info->equipment.amulet.flat_dr.radiant;
	radiant_dr += info->equipment.ring_01.flat_dr.radiant;
	radiant_dr += info->equipment.ring_02.flat_dr.radiant;
	radiant_dr += info->equipment.belt.flat_dr.radiant;
	return (radiant_dr);
}

int	ft_calculate_slashing_dr(t_char *info)
{
	int slashing_dr;

	slashing_dr = info->equipment.weapon.flat_dr.slashing;
	slashing_dr += info->equipment.offhand_weapon.flat_dr.slashing;
	slashing_dr += info->equipment.ranged_weapon.flat_dr.slashing;
	slashing_dr += info->equipment.armor.flat_dr.slashing;
	slashing_dr += info->equipment.helmet.flat_dr.slashing;
	slashing_dr += info->equipment.shield.flat_dr.slashing;
	slashing_dr += info->equipment.boots.flat_dr.slashing;
	slashing_dr += info->equipment.gloves.flat_dr.slashing;
	slashing_dr += info->equipment.amulet.flat_dr.slashing;
	slashing_dr += info->equipment.ring_01.flat_dr.slashing;
	slashing_dr += info->equipment.ring_02.flat_dr.slashing;
	slashing_dr += info->equipment.belt.flat_dr.slashing;
	return (slashing_dr);
}

int	ft_calculate_thunder_dr(t_char *info)
{
	int thunder_dr;

	thunder_dr = info->equipment.weapon.flat_dr.thunder;
	thunder_dr += info->equipment.offhand_weapon.flat_dr.thunder;
	thunder_dr += info->equipment.ranged_weapon.flat_dr.thunder;
	thunder_dr += info->equipment.armor.flat_dr.thunder;
	thunder_dr += info->equipment.helmet.flat_dr.thunder;
	thunder_dr += info->equipment.shield.flat_dr.thunder;
	thunder_dr += info->equipment.boots.flat_dr.thunder;
	thunder_dr += info->equipment.gloves.flat_dr.thunder;
	thunder_dr += info->equipment.amulet.flat_dr.thunder;
	thunder_dr += info->equipment.ring_01.flat_dr.thunder;
	thunder_dr += info->equipment.ring_02.flat_dr.thunder;
	thunder_dr += info->equipment.belt.flat_dr.thunder;
	return (thunder_dr);
}

