#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include <cstdlib>

static char **ft_handle_memory_error(t_char * info, char **data, int error_code)
{
    info->flags.error = 1;
    cma_free_double(data);
    pf_printf_fd(2, "%d-Error: Allocating memory\n", error_code);
    return (ft_nullptr);
}

static int ft_check_target_exists(char *target)
{
    if (ft_set_stats_check_name(target))
    {
        pf_printf_fd(2, "292-Error: Target does not exist\n");
        return (1);
    }
    return (0);
}

static char **ft_allocate_initial_data(char *content, size_t ofset, t_char * info)
{
    char **data;

    data = static_cast<char **>(cma_malloc(sizeof(char *) * 2));
    if (!data)
        return (ft_handle_memory_error(info, ft_nullptr, 293));
    data[0] = cma_strdup(&content[ofset]);
    if (!data[0])
        return (ft_handle_memory_error(info, data, 294));
    data[1] = ft_nullptr;
    return (data);
}

static char **ft_reallocate_data_array(char **data, size_t new_size, t_char *info)
{
    char **temp;

    temp = static_cast<char **>(cma_malloc(new_size * sizeof(char *)));
    if (!temp)
        return (ft_handle_memory_error(info, data, 295));
    int index = 0;
    while (data[index])
    {
        temp[index] = data[index];
        index++;
    }
    cma_free(data);
    return (temp);
}

static char **ft_append_target_to_data(char **data, char *content, size_t ofset,
        t_char * info)
{
    size_t index = 0;

    while (data[index])
        index++;
    data = ft_reallocate_data_array(data, index + 2, info);
    if (!data)
        return (ft_nullptr);
    data[index] = cma_strdup(&content[ofset]);
    if (!data[index])
        return ft_handle_memory_error(info, data, 296);
    data[index + 1] = ft_nullptr;
    return (data);
}

char **ft_set_stats_con_targets(char *content, size_t ofset, char **data, t_char *info)
{
    if (ft_check_target_exists(&content[ofset]))
        return (ft_nullptr);
    if (!data)
        return (ft_allocate_initial_data(content, ofset, info));
    else
        return (ft_append_target_to_data(data, content, ofset, info));
}
