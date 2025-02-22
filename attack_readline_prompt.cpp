#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/nullptr.hpp"

int ft_readline_prompt_hit_or_miss(void)
{
    char *input;
    int invalid_attempts = 0;

    while ((input = rl_readline("Does the attack [hit/miss/exit]? ")) != ft_nullptr)
    {
        if ((ft_strcmp_dnd(input, "y") == 0) || (ft_strcmp_dnd(input, "yes") == 0)
            || (ft_strcmp_dnd(input, "hit") == 0))
        {
            cma_free(input);
            return (0);
        }
        else if ((ft_strcmp_dnd(input, "n") == 0) || (ft_strcmp_dnd(input, "no") == 0)
                 || (ft_strcmp_dnd(input, "miss") == 0))
        {
            cma_free(input);
            return (1);
        }
        else if (ft_strcmp_dnd(input, "exit") == 0)
        {
            cma_free(input);
            return (2);
        }
        else
        {
            invalid_attempts++;
            if (invalid_attempts >= 5)
            {
                pf_printf("Too many invalid attempts. Exiting the prompt.\n");
                cma_free(input);
                return (2);
            }
            pf_printf("Invalid input. Please type 'hit', 'miss', or 'exit' (Attempt %d/5).\n",
    				invalid_attempts);
        }
        cma_free(input);
    }
    pf_printf_fd(2, "Error: read line memory allocation failed\n");
    return (-1);
}
