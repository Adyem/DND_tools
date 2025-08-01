#include "libft/Printf/printf.hpp"
#include "dnd_tools.hpp"
#include "libft/Libft/libft.hpp"
#include <unistd.h>

static void ft_remove_dead_shadow_illusion(t_char *info, int had_turn)
{
    if (ft_strncmp(info->name, "shadow_illusion_", 15) == 0)
    {
        if (info->save_file)
        {
            if (unlink(info->save_file) == 0 && DEBUG == 1)
                pf_printf("Deleted save file for %s\n", info->name);
        }
        if (had_turn)
            ft_turn_next(info->struct_name);
    }
}

void ft_print_character_status(t_char * info, int number, int temp)
{
    if (number == 0 && temp == 0)
        pf_printf("%s remains unchanged and is dead\n", info->name);
    else if (temp == info->dstats.health && info->stats.health == info->dstats.health)
        pf_printf("%s remains at their current state and is at maximum hp (%d)\n",
				info->name, info->dstats.health);
    else if (number == 0)
        pf_printf("%s remains at their current state, with health at %d\n", info->name,
				info->stats.health);
    else if (temp == 0)
    {
        if (number == info->dstats.health)
        {
            pf_printf("%s has been restored to their full health (%d)\n", info->name,
					info->stats.health);
            ft_initiative_add(info);
        }
        else if (info->stats.health == info->dstats.health)
        {
            pf_printf("%s has been fully revived from 0 to full %d health with %d " \
					"surplus recovery\n", info->name, info->stats.health, number -
					info->dstats.health);
            ft_initiative_add(info);
        }
        else if (info->stats.health > 0)
        {
            pf_printf("%s has been revived with %d health\n", info->name,
					info->stats.health);
            ft_initiative_add(info);
        }
        else
        {
            pf_printf("Efforts on %s were redundant, %d damage was unnecessary\n",
					info->name, -number);
        }
    }
    else if (temp == info->dstats.health && info->stats.health == info->dstats.health)
        pf_printf("%s is already at peak condition %d, with %d surplus recovery\n",
				info->name, info->stats.health, number);
    else if (info->stats.health + number > info->dstats.health)
        pf_printf("%s has been fully healed to peak condition %d with %d surplus " \
				"recovery\n",
				info->name, info->stats.health, temp + number - info->dstats.health);
    else
    {
        if (info->stats.health == 0)
        {
            if (-number == temp)
                pf_printf("%s encountered a precise setback\n", info->name);
            else
                pf_printf("%s encountered a setback with %d excess damage\n", info->name,
						(-number - temp));
            int had_turn = ft_initiative_remove(info);
            ft_remove_dead_shadow_illusion(info, had_turn);
        }
        else if (number < 0)
            pf_printf("%s has received %d damage and now has %d health remaining\n",
					info->name,
					-number, info->stats.health);
        else if (number > 0)
            pf_printf("%s's health was enhanced by %d, reaching %d\n", info->name, number,
					info->stats.health);
    }
}
