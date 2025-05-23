#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/dice_roll.hpp"
#include <cstdlib>
#include <cstring>
#include <cerrno>

int ft_request_initiative(t_pc *player)
{
    char *temp;
    char *message;
    char *input;
    int initiative;

	if (g_dnd_test == true)
		return (player->initiative = ft_dice_roll(1, 20));
	message = NULL;
    temp = cma_strjoin("Requesting initiative for ", player->name);
    if (!temp)
    {
        pf_printf_fd(2, "250 Error allocating memory: %s\n", strerror(errno));
        return (1);
    }
    message = cma_strjoin(temp, ": ");
    cma_free(temp);
    if (!message)
    {
        pf_printf_fd(2, "251 Error allocating memory: %s\n", strerror(errno));
        return (1);
    }
    while ((input = rl_readline(message)))
    {
        if (ft_check_value(input))
        {
            cma_free(input);
            pf_printf("Requesting a number between 1 and 50\n");
            continue ;
        }
        initiative = ft_atoi(input);
        cma_free(input);
        if (!(initiative >= 1 && initiative <= 50))
        {
            pf_printf("Requesting a number between 1 and 50\n");
            continue ;
        }
        player->initiative = initiative;
        break ;
    }
    cma_free(message);
    return (0);
}
