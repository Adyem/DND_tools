#include "dnd_tools.hpp"

int	ft_calculate_acid_resistance(SharedPtr<t_char> info)
{
	int acid;

	acid = info->c_resistance.acid;
	acid += info->equipment.weapon.resistance.acid;
	acid += info->equipment.offhand_weapon.resistance.acid;
	acid += info->equipment.ranged_weapon.resistance.acid;
	acid += info->equipment.armor.resistance.acid;
	acid += info->equipment.helmet.resistance.acid;
	acid += info->equipment.shield.resistance.acid;
	acid += info->equipment.boots.resistance.acid;
	acid += info->equipment.gloves.resistance.acid;
	acid += info->equipment.amulet.resistance.acid;
	acid += info->equipment.ring_01.resistance.acid;
	acid += info->equipment.ring_02.resistance.acid;
	acid += info->equipment.belt.resistance.acid;
	return (acid);
}

int	ft_calculate_bludgeoning_resistance(SharedPtr<t_char> info)
{
	int bludgeoning;

	bludgeoning = info->c_resistance.bludgeoning;
	bludgeoning += info->equipment.weapon.resistance.bludgeoning;
	bludgeoning += info->equipment.offhand_weapon.resistance.bludgeoning;
	bludgeoning += info->equipment.ranged_weapon.resistance.bludgeoning;
	bludgeoning += info->equipment.armor.resistance.bludgeoning;
	bludgeoning += info->equipment.helmet.resistance.bludgeoning;
	bludgeoning += info->equipment.shield.resistance.bludgeoning;
	bludgeoning += info->equipment.boots.resistance.bludgeoning;
	bludgeoning += info->equipment.gloves.resistance.bludgeoning;
	bludgeoning += info->equipment.amulet.resistance.bludgeoning;
	bludgeoning += info->equipment.ring_01.resistance.bludgeoning;
	bludgeoning += info->equipment.ring_02.resistance.bludgeoning;
	bludgeoning += info->equipment.belt.resistance.bludgeoning;
	return (bludgeoning);
}

int	ft_calculate_cold_resistance(SharedPtr<t_char> info)
{
	int cold;

	cold = info->c_resistance.cold;
	cold += info->equipment.weapon.resistance.cold;
	cold += info->equipment.offhand_weapon.resistance.cold;
	cold += info->equipment.ranged_weapon.resistance.cold;
	cold += info->equipment.armor.resistance.cold;
	cold += info->equipment.helmet.resistance.cold;
	cold += info->equipment.shield.resistance.cold;
	cold += info->equipment.boots.resistance.cold;
	cold += info->equipment.gloves.resistance.cold;
	cold += info->equipment.amulet.resistance.cold;
	cold += info->equipment.ring_01.resistance.cold;
	cold += info->equipment.ring_02.resistance.cold;
	cold += info->equipment.belt.resistance.cold;
	return (cold);
}

int	ft_calculate_fire_resistance(SharedPtr<t_char> info)
{
	int fire;

	fire = info->c_resistance.fire;
	fire += info->equipment.weapon.resistance.fire;
	fire += info->equipment.offhand_weapon.resistance.fire;
	fire += info->equipment.ranged_weapon.resistance.fire;
	fire += info->equipment.armor.resistance.fire;
	fire += info->equipment.helmet.resistance.fire;
	fire += info->equipment.shield.resistance.fire;
	fire += info->equipment.boots.resistance.fire;
	fire += info->equipment.gloves.resistance.fire;
	fire += info->equipment.amulet.resistance.fire;
	fire += info->equipment.ring_01.resistance.fire;
	fire += info->equipment.ring_02.resistance.fire;
	fire += info->equipment.belt.resistance.fire;
	return (fire);
}

int	ft_calculate_force_resistance(SharedPtr<t_char> info)
{
	int force;

	force = info->c_resistance.force;
	force += info->equipment.weapon.resistance.force;
	force += info->equipment.offhand_weapon.resistance.force;
	force += info->equipment.ranged_weapon.resistance.force;
	force += info->equipment.armor.resistance.force;
	force += info->equipment.helmet.resistance.force;
	force += info->equipment.shield.resistance.force;
	force += info->equipment.boots.resistance.force;
	force += info->equipment.gloves.resistance.force;
	force += info->equipment.amulet.resistance.force;
	force += info->equipment.ring_01.resistance.force;
	force += info->equipment.ring_02.resistance.force;
	force += info->equipment.belt.resistance.force;
	return (force);
}

int	ft_calculate_lightning_resistance(SharedPtr<t_char> info)
{
	int lightning;

	lightning = info->c_resistance.lightning;
	lightning += info->equipment.weapon.resistance.lightning;
	lightning += info->equipment.offhand_weapon.resistance.lightning;
	lightning += info->equipment.ranged_weapon.resistance.lightning;
	lightning += info->equipment.armor.resistance.lightning;
	lightning += info->equipment.helmet.resistance.lightning;
	lightning += info->equipment.shield.resistance.lightning;
	lightning += info->equipment.boots.resistance.lightning;
	lightning += info->equipment.gloves.resistance.lightning;
	lightning += info->equipment.amulet.resistance.lightning;
	lightning += info->equipment.ring_01.resistance.lightning;
	lightning += info->equipment.ring_02.resistance.lightning;
	lightning += info->equipment.belt.resistance.lightning;
	return (lightning);
}

int	ft_calculate_necrotic_resistance(SharedPtr<t_char> info)
{
	int necrotic;

	necrotic = info->c_resistance.necrotic;
	necrotic += info->equipment.weapon.resistance.necrotic;
	necrotic += info->equipment.offhand_weapon.resistance.necrotic;
	necrotic += info->equipment.ranged_weapon.resistance.necrotic;
	necrotic += info->equipment.armor.resistance.necrotic;
	necrotic += info->equipment.helmet.resistance.necrotic;
	necrotic += info->equipment.shield.resistance.necrotic;
	necrotic += info->equipment.boots.resistance.necrotic;
	necrotic += info->equipment.gloves.resistance.necrotic;
	necrotic += info->equipment.amulet.resistance.necrotic;
	necrotic += info->equipment.ring_01.resistance.necrotic;
	necrotic += info->equipment.ring_02.resistance.necrotic;
	necrotic += info->equipment.belt.resistance.necrotic;
	return (necrotic);
}

int	ft_calculate_piercing_resistance(SharedPtr<t_char> info)
{
	int piercing;

	piercing = info->c_resistance.piercing;
	piercing += info->equipment.weapon.resistance.piercing;
	piercing += info->equipment.offhand_weapon.resistance.piercing;
	piercing += info->equipment.ranged_weapon.resistance.piercing;
	piercing += info->equipment.armor.resistance.piercing;
	piercing += info->equipment.helmet.resistance.piercing;
	piercing += info->equipment.shield.resistance.piercing;
	piercing += info->equipment.boots.resistance.piercing;
	piercing += info->equipment.gloves.resistance.piercing;
	piercing += info->equipment.amulet.resistance.piercing;
	piercing += info->equipment.ring_01.resistance.piercing;
	piercing += info->equipment.ring_02.resistance.piercing;
	piercing += info->equipment.belt.resistance.piercing;
	return (piercing);
}

int	ft_calculate_poison_resistance(SharedPtr<t_char> info)
{
	int poison;

	poison = info->c_resistance.poison;
	poison += info->equipment.weapon.resistance.poison;
	poison += info->equipment.offhand_weapon.resistance.poison;
	poison += info->equipment.ranged_weapon.resistance.poison;
	poison += info->equipment.armor.resistance.poison;
	poison += info->equipment.helmet.resistance.poison;
	poison += info->equipment.shield.resistance.poison;
	poison += info->equipment.boots.resistance.poison;
	poison += info->equipment.gloves.resistance.poison;
	poison += info->equipment.amulet.resistance.poison;
	poison += info->equipment.ring_01.resistance.poison;
	poison += info->equipment.ring_02.resistance.poison;
	poison += info->equipment.belt.resistance.poison;
	return (poison);
}

int	ft_calculate_psychic_resistance(SharedPtr<t_char> info)
{
	int psychic;

	psychic = info->c_resistance.psychic;
	psychic += info->equipment.weapon.resistance.psychic;
	psychic += info->equipment.offhand_weapon.resistance.psychic;
	psychic += info->equipment.ranged_weapon.resistance.psychic;
	psychic += info->equipment.armor.resistance.psychic;
	psychic += info->equipment.helmet.resistance.psychic;
	psychic += info->equipment.shield.resistance.psychic;
	psychic += info->equipment.boots.resistance.psychic;
	psychic += info->equipment.gloves.resistance.psychic;
	psychic += info->equipment.amulet.resistance.psychic;
	psychic += info->equipment.ring_01.resistance.psychic;
	psychic += info->equipment.ring_02.resistance.psychic;
	psychic += info->equipment.belt.resistance.psychic;
	return (psychic);
}

int	ft_calculate_radiant_resistance(SharedPtr<t_char> info)
{
	int radiant;

	radiant = info->c_resistance.radiant;
	radiant += info->equipment.weapon.resistance.radiant;
	radiant += info->equipment.offhand_weapon.resistance.radiant;
	radiant += info->equipment.ranged_weapon.resistance.radiant;
	radiant += info->equipment.armor.resistance.radiant;
	radiant += info->equipment.helmet.resistance.radiant;
	radiant += info->equipment.shield.resistance.radiant;
	radiant += info->equipment.boots.resistance.radiant;
	radiant += info->equipment.gloves.resistance.radiant;
	radiant += info->equipment.amulet.resistance.radiant;
	radiant += info->equipment.ring_01.resistance.radiant;
	radiant += info->equipment.ring_02.resistance.radiant;
	radiant += info->equipment.belt.resistance.radiant;
	return (radiant);
}

int	ft_calculate_slashing_resistance(SharedPtr<t_char> info)
{
	int slashing;

	slashing = info->c_resistance.slashing;
	slashing += info->equipment.weapon.resistance.slashing;
	slashing += info->equipment.offhand_weapon.resistance.slashing;
	slashing += info->equipment.ranged_weapon.resistance.slashing;
	slashing += info->equipment.armor.resistance.slashing;
	slashing += info->equipment.helmet.resistance.slashing;
	slashing += info->equipment.shield.resistance.slashing;
	slashing += info->equipment.boots.resistance.slashing;
	slashing += info->equipment.gloves.resistance.slashing;
	slashing += info->equipment.amulet.resistance.slashing;
	slashing += info->equipment.ring_01.resistance.slashing;
	slashing += info->equipment.ring_02.resistance.slashing;
	slashing += info->equipment.belt.resistance.slashing;
	return (slashing);
}

int	ft_calculate_thunder_resistance(SharedPtr<t_char> info)
{
	int thunder;

	thunder = info->c_resistance.thunder;
	thunder += info->equipment.weapon.resistance.thunder;
	thunder += info->equipment.offhand_weapon.resistance.thunder;
	thunder += info->equipment.ranged_weapon.resistance.thunder;
	thunder += info->equipment.armor.resistance.thunder;
	thunder += info->equipment.helmet.resistance.thunder;
	thunder += info->equipment.shield.resistance.thunder;
	thunder += info->equipment.boots.resistance.thunder;
	thunder += info->equipment.gloves.resistance.thunder;
	thunder += info->equipment.amulet.resistance.thunder;
	thunder += info->equipment.ring_01.resistance.thunder;
	thunder += info->equipment.ring_02.resistance.thunder;
	thunder += info->equipment.belt.resistance.thunder;
	return (thunder);
}
