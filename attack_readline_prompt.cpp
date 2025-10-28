#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/CPP_class/class_string_class.hpp"
#include "libft/Template/vector.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Errno/errno.hpp"

typedef struct s_attack_prompt_option
{
    const char  *keyword;
    int         outcome;
}   t_attack_prompt_option;

static int    ft_attack_prompt_add_option(ft_vector<t_attack_prompt_option> &options,
                const char *keyword, int outcome)
{
    t_attack_prompt_option option;

    option.keyword = keyword;
    option.outcome = outcome;
    options.push_back(option);
    if (options.get_error() != ER_SUCCESS)
    {
        ft_errno = options.get_error();
        return (FT_FAILURE);
    }
    return (FT_SUCCESS);
}

static int    ft_attack_prompt_populate_options(ft_vector<t_attack_prompt_option> &options)
{
    if (ft_attack_prompt_add_option(options, "hit", 0) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "y", 0) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "yes", 0) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "miss", 1) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "n", 1) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "no", 1) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "exit", 2) == FT_FAILURE)
        return (FT_FAILURE);
    if (ft_attack_prompt_add_option(options, "quit", 2) == FT_FAILURE)
        return (FT_FAILURE);
    return (FT_SUCCESS);
}

int ft_attack_prompt_parse_response(const char *input, int *prompt_result)
{
    if ((input == ft_nullptr) || (prompt_result == ft_nullptr))
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (FT_FAILURE);
    }
    int                                 result;
    int                                 final_errno;

    result = FT_FAILURE;
    final_errno = FT_ERR_INVALID_ARGUMENT;
    {
        ft_vector<t_attack_prompt_option>    options(8);
        ft_string                            normalized_input(input);
        size_t                              option_count;
        size_t                              index;
        t_attack_prompt_option              *option;

        if (normalized_input.get_error() != ER_SUCCESS)
            final_errno = normalized_input.get_error();
        else
        {
            ft_to_lower(normalized_input.data());
            if (normalized_input.get_error() != ER_SUCCESS)
                final_errno = normalized_input.get_error();
            else if (ft_attack_prompt_populate_options(options) == FT_FAILURE)
                final_errno = ft_errno;
            else
            {
                option_count = options.size();
                if (options.get_error() != ER_SUCCESS)
                    final_errno = options.get_error();
                else
                {
                    index = 0;
                    while (index < option_count && result == FT_FAILURE)
                    {
                        option = &options[index];
                        if (options.get_error() != ER_SUCCESS)
                        {
                            final_errno = options.get_error();
                            break;
                        }
                        if (ft_strcmp(normalized_input.c_str(), option->keyword) == 0)
                        {
                            *prompt_result = option->outcome;
                            final_errno = ER_SUCCESS;
                            result = FT_SUCCESS;
                        }
                        index++;
                    }
                }
            }
        }
    }
    ft_errno = final_errno;
    return (result);
}

int ft_readline_prompt_hit_or_miss(void)
{
    char *input;
    int invalid_attempts = 0;
    int prompt_result;
    int parse_status;

    while ((input = rl_readline("Does the attack [hit/miss/exit]? ")) != ft_nullptr)
    {
        parse_status = ft_attack_prompt_parse_response(input, &prompt_result);
        cma_free(input);
        if (parse_status == FT_SUCCESS)
            return (prompt_result);
        if (ft_errno != FT_ERR_INVALID_ARGUMENT)
        {
            pf_printf_fd(2, "Error: failed to parse attack prompt response: %s\n",
                ft_strerror(ft_errno));
            return (-1);
        }
        invalid_attempts++;
        if (invalid_attempts >= 5)
        {
            pf_printf("Too many invalid attempts. Exiting the prompt.\n");
            return (2);
        }
        pf_printf("Invalid input. Please type 'hit', 'miss', or 'exit' (Attempt %d/5).\n",
            invalid_attempts);
    }
    pf_printf_fd(2, "Error: read line memory allocation failed\n");
    return (-1);
}
