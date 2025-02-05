#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include <climits>


static int check_spell_slot(ft_sharedptr<t_char> &info, const char *slot_name, t_spell_slot *slot)
{
    int error = 0;

    if (ft_strcmp_dnd(slot_name, "warlock") == 0)
    {
        if (slot->level == 0 && (slot->total != 0 || slot->available != 0))
        {
            error++;
            pf_printf("%s: Warlock slot level is 0, but total (%d) or available " \
					"(%d) slots are not 0\n", info->name, slot->total, slot->available);
        }
    }
    else
    {
        if (slot->level != 0)
        {
            error++;
            pf_printf("%s: Spell slot %s should have level 0, but found %d\n", 
					info->name, slot_name, slot->level);
        }
    }
    if (slot->available < 0 || slot->available > slot->total)
    {
        error++;
        pf_printf("%s: Available slots (%d) for %s are out of range (0 to %d)\n",
				info->name, slot->available, slot_name, slot->total);
    }
    return (error);
}

static int check_spell_slots(ft_sharedptr<t_char> &info)
{
    int error = 0;
    error += check_spell_slot(info, "level_1", &info->spell_slots.level_1);
    error += check_spell_slot(info, "level_2", &info->spell_slots.level_2);
    error += check_spell_slot(info, "level_3", &info->spell_slots.level_3);
    error += check_spell_slot(info, "level_4", &info->spell_slots.level_4);
    error += check_spell_slot(info, "level_5", &info->spell_slots.level_5);
    error += check_spell_slot(info, "level_6", &info->spell_slots.level_6);
    error += check_spell_slot(info, "level_7", &info->spell_slots.level_7);
    error += check_spell_slot(info, "level_8", &info->spell_slots.level_8);
    error += check_spell_slot(info, "level_9", &info->spell_slots.level_9);
    error += check_spell_slot(info, "warlock", &info->spell_slots.warlock);
    return (error);
}

int ft_npc_check_info(ft_sharedptr<t_char> &info)
{
    int error = 0;
    error += check_spell_slots(info);
    error += ft_check_equipment_slots(info);
    if (error)
        pf_printf("%s: Error with the save file, please reinitialize it with the " \
				"correct values\n", info->name);
    return (error);
}
