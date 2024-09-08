#include "dnd_tools.hpp"
#include <iostream>

void ft_print_character_status(t_char *info, int number, int temp)
{
    if (number == 0 && temp == 0)
        std::cout << info->name << " remains unchanged and is dead" << std::endl;
    else if (temp == info->dstats.health && info->stats.health == info->dstats.health)
        std::cout << info->name << " remains at their current state and is at maximum hp ("
                  << info->dstats.health << ")" << std::endl;
    else if (number == 0)
        std::cout << info->name << " remains at their current state, with health at "
                  << info->stats.health << std::endl;
    else if (temp == 0)
    {
        if (number == info->dstats.health)
        {
            std::cout << info->name << " has been restored to their full health ("
                      << info->stats.health << ")" << std::endl;
            ft_initiative_add(info);
        }
        else if (info->stats.health == info->dstats.health)
        {
            std::cout << info->name << " has been fully revived from 0 to full "
                      << info->stats.health << " health with " << number - info->dstats.health
                      << " surplus recovery" << std::endl;
            ft_initiative_add(info);
        }
        else if (info->stats.health > 0)
        {
            std::cout << info->name << " has been revived with " << info->stats.health
                      << " health" << std::endl;
            ft_initiative_add(info);
        }
        else
        {
            std::cout << "Efforts on " << info->name << " were redundant, "
                      << -number << " damage was unnecessary" << std::endl;
        }
    }
    else if (temp == info->dstats.health && info->stats.health == info->dstats.health)
        std::cout << info->name << " is already at peak condition " << info->stats.health
                  << ", with " << number << " surplus recovery" << std::endl;
    else if (info->stats.health + number > info->dstats.health)
        std::cout << info->name << " has been fully healed to peak condition "
                  << info->stats.health << " with " << temp + number - info->dstats.health
                  << " surplus recovery" << std::endl;
    else
    {
        if (info->stats.health == 0)
        {
            if (-number == temp)
                std::cout << info->name << " encountered a precise setback" << std::endl;
            else
                std::cout << info->name << " encountered a setback with "
                          << (-number - temp) << " excess damage" << std::endl;
            ft_initiative_remove(info);
        }
        else if (number < 0)
            std::cout << info->name << " has received " << -number << " damage and now has "
                      << info->stats.health << " health remaining" << std::endl;
        else if (number > 0)
            std::cout << info->name << "'s health was enhanced by " << number
                      << ", reaching " << info->stats.health << std::endl;
    }
}
