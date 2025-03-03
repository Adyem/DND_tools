#include "dnd_tools.hpp"

int ft_calculate_athletics(t_char * info)
{
    int athletics;

	athletics = info->skill_mod.athletics;
    athletics += info->equipment.weapon.skill_mod.athletics;
    athletics += info->equipment.offhand_weapon.skill_mod.athletics;
    athletics += info->equipment.ranged_weapon.skill_mod.athletics;
    athletics += info->equipment.armor.skill_mod.athletics;
    athletics += info->equipment.helmet.skill_mod.athletics;
    athletics += info->equipment.shield.skill_mod.athletics;
    athletics += info->equipment.boots.skill_mod.athletics;
    athletics += info->equipment.gloves.skill_mod.athletics;
    athletics += info->equipment.amulet.skill_mod.athletics;
    athletics += info->equipment.ring_01.skill_mod.athletics;
    athletics += info->equipment.ring_02.skill_mod.athletics;
    athletics += info->equipment.belt.skill_mod.athletics;
    return (athletics);
}

int ft_calculate_acrobatics(t_char * info)
{
    int acrobatics;

	acrobatics = info->skill_mod.acrobatics;
    acrobatics += info->equipment.weapon.skill_mod.acrobatics;
    acrobatics += info->equipment.offhand_weapon.skill_mod.acrobatics;
    acrobatics += info->equipment.ranged_weapon.skill_mod.acrobatics;
    acrobatics += info->equipment.armor.skill_mod.acrobatics;
    acrobatics += info->equipment.helmet.skill_mod.acrobatics;
    acrobatics += info->equipment.shield.skill_mod.acrobatics;
    acrobatics += info->equipment.boots.skill_mod.acrobatics;
    acrobatics += info->equipment.gloves.skill_mod.acrobatics;
    acrobatics += info->equipment.amulet.skill_mod.acrobatics;
    acrobatics += info->equipment.ring_01.skill_mod.acrobatics;
    acrobatics += info->equipment.ring_02.skill_mod.acrobatics;
    acrobatics += info->equipment.belt.skill_mod.acrobatics;
    return (acrobatics);
}

int ft_calculate_sleight_of_hand(t_char * info)
{
    int sleight_of_hand;

	sleight_of_hand = info->skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.weapon.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.offhand_weapon.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.ranged_weapon.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.armor.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.helmet.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.shield.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.boots.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.gloves.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.amulet.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.ring_01.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.ring_02.skill_mod.sleight_of_hand;
    sleight_of_hand += info->equipment.belt.skill_mod.sleight_of_hand;
    return (sleight_of_hand);
}

int ft_calculate_stealth(t_char * info)
{
    int stealth;

	stealth = info->skill_mod.stealth;
    stealth += info->equipment.weapon.skill_mod.stealth;
    stealth += info->equipment.offhand_weapon.skill_mod.stealth;
    stealth += info->equipment.ranged_weapon.skill_mod.stealth;
    stealth += info->equipment.armor.skill_mod.stealth;
    stealth += info->equipment.helmet.skill_mod.stealth;
    stealth += info->equipment.shield.skill_mod.stealth;
    stealth += info->equipment.boots.skill_mod.stealth;
    stealth += info->equipment.gloves.skill_mod.stealth;
    stealth += info->equipment.amulet.skill_mod.stealth;
    stealth += info->equipment.ring_01.skill_mod.stealth;
    stealth += info->equipment.ring_02.skill_mod.stealth;
    stealth += info->equipment.belt.skill_mod.stealth;
    return (stealth);
}

int ft_calculate_arcana(t_char * info)
{
    int arcana;

	arcana = info->skill_mod.arcana;
    arcana += info->equipment.weapon.skill_mod.arcana;
    arcana += info->equipment.offhand_weapon.skill_mod.arcana;
    arcana += info->equipment.ranged_weapon.skill_mod.arcana;
    arcana += info->equipment.armor.skill_mod.arcana;
    arcana += info->equipment.helmet.skill_mod.arcana;
    arcana += info->equipment.shield.skill_mod.arcana;
    arcana += info->equipment.boots.skill_mod.arcana;
    arcana += info->equipment.gloves.skill_mod.arcana;
    arcana += info->equipment.amulet.skill_mod.arcana;
    arcana += info->equipment.ring_01.skill_mod.arcana;
    arcana += info->equipment.ring_02.skill_mod.arcana;
    arcana += info->equipment.belt.skill_mod.arcana;
    return (arcana);
}

int ft_calculate_history(t_char * info)
{
    int history;

	history = info->skill_mod.history;
    history += info->equipment.weapon.skill_mod.history;
    history += info->equipment.offhand_weapon.skill_mod.history;
    history += info->equipment.ranged_weapon.skill_mod.history;
    history += info->equipment.armor.skill_mod.history;
    history += info->equipment.helmet.skill_mod.history;
    history += info->equipment.shield.skill_mod.history;
    history += info->equipment.boots.skill_mod.history;
    history += info->equipment.gloves.skill_mod.history;
    history += info->equipment.amulet.skill_mod.history;
    history += info->equipment.ring_01.skill_mod.history;
    history += info->equipment.ring_02.skill_mod.history;
    history += info->equipment.belt.skill_mod.history;
    return (history);
}

int ft_calculate_investigation(t_char * info)
{
    int investigation;

	investigation = info->skill_mod.investigation;
    investigation += info->equipment.weapon.skill_mod.investigation;
    investigation += info->equipment.offhand_weapon.skill_mod.investigation;
    investigation += info->equipment.ranged_weapon.skill_mod.investigation;
    investigation += info->equipment.armor.skill_mod.investigation;
    investigation += info->equipment.helmet.skill_mod.investigation;
    investigation += info->equipment.shield.skill_mod.investigation;
    investigation += info->equipment.boots.skill_mod.investigation;
    investigation += info->equipment.gloves.skill_mod.investigation;
    investigation += info->equipment.amulet.skill_mod.investigation;
    investigation += info->equipment.ring_01.skill_mod.investigation;
    investigation += info->equipment.ring_02.skill_mod.investigation;
    investigation += info->equipment.belt.skill_mod.investigation;
    return (investigation);
}

int ft_calculate_nature(t_char * info)
{
    int nature;

	nature = info->skill_mod.nature;
    nature += info->equipment.weapon.skill_mod.nature;
    nature += info->equipment.offhand_weapon.skill_mod.nature;
    nature += info->equipment.ranged_weapon.skill_mod.nature;
    nature += info->equipment.armor.skill_mod.nature;
    nature += info->equipment.helmet.skill_mod.nature;
    nature += info->equipment.shield.skill_mod.nature;
    nature += info->equipment.boots.skill_mod.nature;
    nature += info->equipment.gloves.skill_mod.nature;
    nature += info->equipment.amulet.skill_mod.nature;
    nature += info->equipment.ring_01.skill_mod.nature;
    nature += info->equipment.ring_02.skill_mod.nature;
    nature += info->equipment.belt.skill_mod.nature;
    return (nature);
}

int ft_calculate_religion(t_char * info)
{
    int religion;

	religion = info->skill_mod.religion;
    religion += info->equipment.weapon.skill_mod.religion;
    religion += info->equipment.offhand_weapon.skill_mod.religion;
    religion += info->equipment.ranged_weapon.skill_mod.religion;
    religion += info->equipment.armor.skill_mod.religion;
    religion += info->equipment.helmet.skill_mod.religion;
    religion += info->equipment.shield.skill_mod.religion;
    religion += info->equipment.boots.skill_mod.religion;
    religion += info->equipment.gloves.skill_mod.religion;
    religion += info->equipment.amulet.skill_mod.religion;
    religion += info->equipment.ring_01.skill_mod.religion;
    religion += info->equipment.ring_02.skill_mod.religion;
    religion += info->equipment.belt.skill_mod.religion;
    return (religion);
}

int ft_calculate_animal_handling(t_char * info)
{
    int animal_handling;

	animal_handling = info->skill_mod.animal_handling;
    animal_handling += info->equipment.weapon.skill_mod.animal_handling;
    animal_handling += info->equipment.offhand_weapon.skill_mod.animal_handling;
    animal_handling += info->equipment.ranged_weapon.skill_mod.animal_handling;
    animal_handling += info->equipment.armor.skill_mod.animal_handling;
    animal_handling += info->equipment.helmet.skill_mod.animal_handling;
    animal_handling += info->equipment.shield.skill_mod.animal_handling;
    animal_handling += info->equipment.boots.skill_mod.animal_handling;
    animal_handling += info->equipment.gloves.skill_mod.animal_handling;
    animal_handling += info->equipment.amulet.skill_mod.animal_handling;
    animal_handling += info->equipment.ring_01.skill_mod.animal_handling;
    animal_handling += info->equipment.ring_02.skill_mod.animal_handling;
    animal_handling += info->equipment.belt.skill_mod.animal_handling;
    return (animal_handling);
}

int ft_calculate_insight(t_char * info)
{
    int insight;

	insight = info->skill_mod.insight;
    insight += info->equipment.weapon.skill_mod.insight;
    insight += info->equipment.offhand_weapon.skill_mod.insight;
    insight += info->equipment.ranged_weapon.skill_mod.insight;
    insight += info->equipment.armor.skill_mod.insight;
    insight += info->equipment.helmet.skill_mod.insight;
    insight += info->equipment.shield.skill_mod.insight;
    insight += info->equipment.boots.skill_mod.insight;
    insight += info->equipment.gloves.skill_mod.insight;
    insight += info->equipment.amulet.skill_mod.insight;
    insight += info->equipment.ring_01.skill_mod.insight;
    insight += info->equipment.ring_02.skill_mod.insight;
    insight += info->equipment.belt.skill_mod.insight;
    return (insight);
}

int ft_calculate_medicine(t_char * info)
{
    int medicine;

	medicine = info->skill_mod.medicine;
    medicine += info->equipment.weapon.skill_mod.medicine;
    medicine += info->equipment.offhand_weapon.skill_mod.medicine;
    medicine += info->equipment.ranged_weapon.skill_mod.medicine;
    medicine += info->equipment.armor.skill_mod.medicine;
    medicine += info->equipment.helmet.skill_mod.medicine;
    medicine += info->equipment.shield.skill_mod.medicine;
    medicine += info->equipment.boots.skill_mod.medicine;
    medicine += info->equipment.gloves.skill_mod.medicine;
    medicine += info->equipment.amulet.skill_mod.medicine;
    medicine += info->equipment.ring_01.skill_mod.medicine;
    medicine += info->equipment.ring_02.skill_mod.medicine;
    medicine += info->equipment.belt.skill_mod.medicine;
    return (medicine);
}

int ft_calculate_perception(t_char * info)
{
    int perception;

	perception = info->skill_mod.perception;
    perception += info->equipment.weapon.skill_mod.perception;
    perception += info->equipment.offhand_weapon.skill_mod.perception;
    perception += info->equipment.ranged_weapon.skill_mod.perception;
    perception += info->equipment.armor.skill_mod.perception;
    perception += info->equipment.helmet.skill_mod.perception;
    perception += info->equipment.shield.skill_mod.perception;
    perception += info->equipment.boots.skill_mod.perception;
    perception += info->equipment.gloves.skill_mod.perception;
    perception += info->equipment.amulet.skill_mod.perception;
    perception += info->equipment.ring_01.skill_mod.perception;
    perception += info->equipment.ring_02.skill_mod.perception;
    perception += info->equipment.belt.skill_mod.perception;
    return (perception);
}

int ft_calculate_survival(t_char * info)
{
    int survival;

	survival = info->skill_mod.survival;
    survival += info->equipment.weapon.skill_mod.survival;
    survival += info->equipment.offhand_weapon.skill_mod.survival;
    survival += info->equipment.ranged_weapon.skill_mod.survival;
    survival += info->equipment.armor.skill_mod.survival;
    survival += info->equipment.helmet.skill_mod.survival;
    survival += info->equipment.shield.skill_mod.survival;
    survival += info->equipment.boots.skill_mod.survival;
    survival += info->equipment.gloves.skill_mod.survival;
    survival += info->equipment.amulet.skill_mod.survival;
    survival += info->equipment.ring_01.skill_mod.survival;
    survival += info->equipment.ring_02.skill_mod.survival;
    survival += info->equipment.belt.skill_mod.survival;
    return (survival);
}

int ft_calculate_deception(t_char * info)
{
    int deception;

	deception = info->skill_mod.deception;
    deception += info->equipment.weapon.skill_mod.deception;
    deception += info->equipment.offhand_weapon.skill_mod.deception;
    deception += info->equipment.ranged_weapon.skill_mod.deception;
    deception += info->equipment.armor.skill_mod.deception;
    deception += info->equipment.helmet.skill_mod.deception;
    deception += info->equipment.shield.skill_mod.deception;
    deception += info->equipment.boots.skill_mod.deception;
    deception += info->equipment.gloves.skill_mod.deception;
    deception += info->equipment.amulet.skill_mod.deception;
    deception += info->equipment.ring_01.skill_mod.deception;
    deception += info->equipment.ring_02.skill_mod.deception;
    deception += info->equipment.belt.skill_mod.deception;
    return (deception);
}

int ft_calculate_intimidation(t_char * info)
{
    int intimidation;

	intimidation = info->skill_mod.intimidation;
    intimidation += info->equipment.weapon.skill_mod.intimidation;
    intimidation += info->equipment.offhand_weapon.skill_mod.intimidation;
    intimidation += info->equipment.ranged_weapon.skill_mod.intimidation;
    intimidation += info->equipment.armor.skill_mod.intimidation;
    intimidation += info->equipment.helmet.skill_mod.intimidation;
    intimidation += info->equipment.shield.skill_mod.intimidation;
    intimidation += info->equipment.boots.skill_mod.intimidation;
    intimidation += info->equipment.gloves.skill_mod.intimidation;
    intimidation += info->equipment.amulet.skill_mod.intimidation;
    intimidation += info->equipment.ring_01.skill_mod.intimidation;
    intimidation += info->equipment.ring_02.skill_mod.intimidation;
    intimidation += info->equipment.belt.skill_mod.intimidation;
    return (intimidation);
}

int ft_calculate_performance(t_char * info)
{
    int performance;

	performance = info->skill_mod.performance;
    performance += info->equipment.weapon.skill_mod.performance;
    performance += info->equipment.offhand_weapon.skill_mod.performance;
    performance += info->equipment.ranged_weapon.skill_mod.performance;
    performance += info->equipment.armor.skill_mod.performance;
    performance += info->equipment.helmet.skill_mod.performance;
    performance += info->equipment.shield.skill_mod.performance;
    performance += info->equipment.boots.skill_mod.performance;
    performance += info->equipment.gloves.skill_mod.performance;
    performance += info->equipment.amulet.skill_mod.performance;
    performance += info->equipment.ring_01.skill_mod.performance;
    performance += info->equipment.ring_02.skill_mod.performance;
    performance += info->equipment.belt.skill_mod.performance;
    return (performance);
}

int ft_calculate_persuasion(t_char * info)
{
    int persuasion;

	persuasion = info->skill_mod.persuasion;
    persuasion += info->equipment.weapon.skill_mod.persuasion;
    persuasion += info->equipment.offhand_weapon.skill_mod.persuasion;
    persuasion += info->equipment.ranged_weapon.skill_mod.persuasion;
    persuasion += info->equipment.armor.skill_mod.persuasion;
    persuasion += info->equipment.helmet.skill_mod.persuasion;
    persuasion += info->equipment.shield.skill_mod.persuasion;
    persuasion += info->equipment.boots.skill_mod.persuasion;
    persuasion += info->equipment.gloves.skill_mod.persuasion;
    persuasion += info->equipment.amulet.skill_mod.persuasion;
    persuasion += info->equipment.ring_01.skill_mod.persuasion;
    persuasion += info->equipment.ring_02.skill_mod.persuasion;
    persuasion += info->equipment.belt.skill_mod.persuasion;
    return (persuasion);
}
