#include "dnd_tools.h"

int file_exists(const char *filename)
{
    return (access(filename, F_OK) != -1);
}

char *build_file_path(const char *folder, const char *prefix, const char *name)
{
    size_t len = strlen(folder) + strlen(prefix) + strlen(name) + 2;
    char *filepath = (char *)malloc(len);
    if (!filepath) return NULL;
    snprintf(filepath, len, "%s/%s%s", folder, prefix, name);
    return filepath;
}

int add_name_if_unique(char ***caster_name, const char *name, int *count)
{
    for (int i = 0; i < *count; i++)
        if (strcmp((*caster_name)[i], name) == 0)
            return (0);
    char **temp = ft_resize_double_char(*caster_name, name, 1);
    if (!temp)
	{
        ft_printf_fd(2, "Error allocating memory for caster name\n");
        return (1);
    }
    *caster_name = temp;
    (*count)++;
    return (0);
}

int ft_update_caster_name(char ***caster_name, const char *input_name, t_buff *buff)
{
    char *name_input;
    int count = 0;
    
    if (DEBUG == 1)
        ft_printf("Adding the new caster name to the target struct\n");
    if (!(*caster_name))
	{
        *caster_name = (char **)ft_calloc(2, sizeof(char *));
        if (!(*caster_name))
		{
            ft_printf_fd(2, "Error allocating memory for caster name\n");
            return 1;
        }
        **caster_name = ft_strdup(input_name);
        if (!(**caster_name))
		{
            ft_printf_fd(2, "Error allocating memory for caster name\n");
            return 1;
        }
        count = 1;
    }
    while (count < buff->target_amount)
	{
        name_input = readline("Enter caster name (or type 'exit' to quit): ");
        if (!name_input || strcmp(name_input, "exit") == 0)
		{
            free(name_input);
            break;
        }
        char *pc_filepath = build_file_path("data", "pc--", name_input);
        char *mob_filepath = build_file_path("data", "", name_input);
		if ((pc_filepath && file_exists(pc_filepath)) || 
			(mob_filepath && file_exists(mob_filepath) && !strstr(mob_filepath, "data--")))
		{
			if (add_name_if_unique(caster_name, name_input, &count) != 0)
			{
				free(name_input);
				free(pc_filepath);
				free(mob_filepath);
				return (1);
			}
		}
		else
			printf("No valid file found for '%s'\n", name_input);
		free(name_input);
		free(pc_filepath);
		free(mob_filepath);
	}
	return (0);
}
