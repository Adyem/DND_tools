#include "dnd_tools.hpp"
#include <iostream>

void ft_concentration_remove_hunters_mark(t_char *info, t_char *target)
{
    int i;
    int j;

    i = 0;
    while (target->debufs.hunters_mark.caster_name && target->debufs.hunters_mark.caster_name[i])
    {
        if (DEBUG == 1)
            std::cout << "r-debuff checking " << target->debufs.hunters_mark.caster_name[i] 
                      << " " << info->name << std::endl;
        if (ft_strcmp_dnd(target->debufs.hunters_mark.caster_name[i], info->name) == 0)
        {
            free(target->debufs.hunters_mark.caster_name[i]);
            j = i;
            while (target->debufs.hunters_mark.caster_name[j])
            {
                target->debufs.hunters_mark.caster_name[j] = target->debufs.hunters_mark.caster_name[j + 1];
                j++;
            }
            target->debufs.hunters_mark.amount--;
            if (j > 0)
                target->debufs.hunters_mark.caster_name[j - 1] = nullptr;

            if (DEBUG == 1)
                std::cout << "Found target with debuff and removed it: " << target->name << std::endl;
            return ;
        }
        i++;
    }
    std::cerr << "304-Error: " << target->name << " Hunters mark debuff not found" << std::endl;
    return ;
}
