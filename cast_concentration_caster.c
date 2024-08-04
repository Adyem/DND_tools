#include "dnd_tools.h"

int file_exists(const char *path, const char *prefix)
{
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL)
        return (0);
    while ((entry = readdir(dp)))
    {
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0)
        {
            if (strcmp(entry->d_name + strlen(prefix), input_name) == 0)
            {
                closedir(dp);
                return (1);
            }
        }
    }

    closedir(dp);
    return (0);
}

int is_duplicate(char **caster_name, const char *name)
{
    for (int i = 0; caster_name[i] != NULL; i++)
    {
        if (strcmp(caster_name[i], name) == 0)
            return (1);
    }
    return (0);
}

int ft_update_caster_name(char ***caster_name, const char *input_name, t_buff *buff)
{
    char **temp;
    char *user_input;

    if (DEBUG == 1)
        ft_printf("adding the new caster name to the target struct\n");

    if (!(*caster_name))
    {
        *caster_name = (char **)ft_calloc(2, sizeof(char *));
        if (!(*caster_name))
        {
            ft_printf_fd(2, "165-Error allocating memory for caster name\n");
            return (1);
        }
        **caster_name = ft_strdup(input_name);
        if (!(**caster_name))
        {
            ft_printf_fd(2, "162-Error allocating memory for caster name\n");
            return (1);
        }
    }
    else
    {
        temp = ft_resize_double_char(*caster_name, input_name, 1);
        if (temp)
        {
            ft_free_double_char(*caster_name);
            *caster_name = temp;
        }
        else
        {
            ft_printf_fd(2, "297-Error allocating memory for caster name\n");
            return (1);
        }
    }
    if (buff->target_amount > 1)
    {
        int count = 0;
        while (count < buff->target_amount)
        {
            user_input = readline("Enter caster name (or 'exit' to finish): ");
            if (strcmp(user_input, "exit") == 0)
            {
                free(user_input);
                break ;
            }
            if (is_duplicate(*caster_name, user_input))
            {
                ft_printf("Name '%s' is a duplicate, try another.\n", user_input);
                free(user_input);
                continue ;
            }
            if (file_exists("./data", "pc--", user_input) || file_exists("./data", "mob--", user_input))
            {
                temp = ft_resize_double_char(*caster_name, user_input, 1);
                if (temp)
                {
                    ft_free_double_char(*caster_name);
                    *caster_name = temp;
                    count++;
                }
                else
                {
                    ft_printf_fd(2, "297-Error allocating memory for caster name\n");
                    free(user_input);
                    return (1);
                }
            }
            else
            {
                ft_printf("No valid file found for '%s'.\n", user_input);
            }

            free(user_input);
        }
    }
    return (0);
}
