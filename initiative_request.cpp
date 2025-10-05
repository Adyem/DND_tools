#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/RNG/rng.hpp"
#include "libft/Errno/errno.hpp"

int ft_request_initiative(t_pc *player)
{
    char *message;
    char *input;
    int initiative;
    int has_initiative;

    if (g_dnd_test == true)
    {
        player->initiative = ft_dice_roll(1, 20);
        return (0);
    }
    message = cma_strjoin_multiple(3, "Requesting initiative for ",
        player->name, ": ");
    if (message == ft_nullptr)
    {
        pf_printf_fd(2, "250 Error allocating memory: %s\n",
            ft_strerror(ft_errno));
        return (1);
    }
    has_initiative = 0;
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
        has_initiative = 1;
        break ;
    }
    cma_free(message);
    if (has_initiative == 0)
        return (2);
    return (0);
}
