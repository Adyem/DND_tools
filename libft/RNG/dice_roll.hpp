#ifndef DICE_ROLL_HPP
# define DICE_ROLL_HPP

#ifndef DEBUG
# define DEBUG 0
#endif

#include "../CPP_class/nullptr.hpp"
#include <ctime>
#include <cstdlib>

extern bool g_srand_init;

inline __attribute__((always_inline)) void ft_init_srand(void)
{
    if (g_srand_init == false)
    {
        srand((unsigned)time(ft_nullptr));
        g_srand_init = true;
    }
	return ;
}

int ft_dice_roll(int number, int faces);

#endif
