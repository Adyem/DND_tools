#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

int ft_readline_prompt_hit_or_miss(void)
{
    char *input;
    int invalid_attempts = 0;

    while ((input = rl_readline("Does the attack [hit/miss/exit]? ")) != ft_nullptr)
    {
        if ((ft_strcmp(input, "y") == 0) || (ft_strcmp(input, "yes") == 0)
            || (ft_strcmp(input, "hit") == 0))
        {
            cma_free(input);
            return (0);
        }
        else if ((ft_strcmp(input, "n") == 0) || (ft_strcmp(input, "no") == 0)
                 || (ft_strcmp(input, "miss") == 0))
        {
            cma_free(input);
            return (1);
        }
        else if (ft_strcmp(input, "exit") == 0)
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
