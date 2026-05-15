#include "character.hpp"
#include "libft/Modules/CMA/CMA.hpp"
#include "libft/Modules/Basic/basic.hpp"
#include "libft/Modules/Printf/printf.hpp"
#include "libft/Modules/ReadLine/readline.hpp"
#include "libft/Modules/CPP_class/class_nullptr.hpp"
#include "dnd_tools.hpp"

static int ft_check_target_amount(int target_amount)
{
    if (target_amount > 20)
    {
        pf_printf("110-Error: too many targets\n");
        return (0);
    }
    return (1);
}

static char *ft_read_target_name(int index)
{
    char    message[55];
    char    *target_name;

    if (pf_snprintf(message, sizeof(message), "Requesting the name of the %s target",
            ft_ordinal_suffix(index + 1)) < 0)
        return (ft_nullptr);
    target_name = rl_readline(message);
    if (!target_name)
    {
        pf_printf("108-Error: Failed to allocate memory for readline target\n");
        return (ft_nullptr);
    }
    return (target_name);
}

int    ft_cast_concentration_multi_target_01(t_char * info, t_buff *buff,
                                            const char **input)
{
    t_target_data    target_data;
    int                error = 0;
    int                targets_collected = 0;
    int                error_code;

    if (ft_remove_concentration(info))
        return (1);
    ft_initialize_variables(&target_data);
    if (!ft_check_target_amount(buff->target_amount))
        return (1);
    while (targets_collected < buff->target_amount)
    {
        target_data.Pchar_name[targets_collected] = ft_read_target_name(targets_collected);
        if (!target_data.Pchar_name[targets_collected])
        {
            ft_free_memory_cmt(&target_data, targets_collected);
            return (1);
        }
        target_data.target[targets_collected] = ft_validate_and_fetch_target
            (target_data.Pchar_name[targets_collected], info, &error_code);
        target_data.target_copy[targets_collected] = ft_validate_and_fetch_target
            (target_data.Pchar_name[targets_collected], info, &error_code);
        if (!target_data.target[targets_collected])
        {
            if (error_code == 0)
            {
                cma_free(target_data.Pchar_name[targets_collected]);
                target_data.Pchar_name[targets_collected] = ft_nullptr;
            }
            else
            {
                cma_free(target_data.Pchar_name[targets_collected]);
                target_data.Pchar_name[targets_collected] = ft_nullptr;
                error++;
                if (error >= MAX_ERROR_COUNT)
                {
                    ft_free_memory_cmt(&target_data, targets_collected);
                    return (1);
                }
                continue ;
            }
        }
        targets_collected++;
    }
    buff->target_amount = targets_collected;
    target_data.buff_info = buff;
    ft_cast_concentration_multi_target_02(info, &target_data, input);
    ft_free_memory_cmt(&target_data, buff->target_amount);
    return (0);
}
