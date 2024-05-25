#include "dnd_tools.h"

#define DATA_FOLDER "data"
#define PREFIX_TO_SKIP "data--"
#define EXCLUDE_PREFIX "pc--"

static void remove_exclude_prefix(char* filename)
{
    if (strncmp(filename, EXCLUDE_PREFIX, strlen(EXCLUDE_PREFIX)) == 0)
        memmove(filename, filename + strlen(EXCLUDE_PREFIX), strlen(filename)
				- strlen(EXCLUDE_PREFIX) + 1);
}

static int ft_set_stats_check_name(char *content)
{
    DIR* dir;
    struct dirent* entry;
	char filename[256];

    if ((dir = opendir(DATA_FOLDER)) == NULL)
	{
        perror("opendir");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL)
	{
        if (strncmp(entry->d_name, PREFIX_TO_SKIP, strlen(PREFIX_TO_SKIP)) == 0)
            continue;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        remove_exclude_prefix(filename);
        if (strcmp(filename, content) == 0)
		{
            closedir(dir);
            return 0;
		}
    }
    closedir(dir);
    return 1;
}

char **ft_set_stats_con_targets(char *content, int ofset, char **data)
{
	char	**temp;
	int		i;

	if (ft_set_stats_check_name(content))
			return (NULL);
	if (!data)
	{
		data = (char **)malloc(sizeof(char *) * 2);
		if (!data)
			return (NULL);
		data[0] = (char *)malloc((ft_strlen(content) + 1) * sizeof(char));
		if (!data[0])
		{
			ft_free_content(data);
			return (NULL);
		}
		data[0] = ft_strdup(&content[ofset]);
		data[1] = NULL;
	}
	else if (data)
	{
		i = 0;
		while (data[i])
			i++;
		temp = (char **)malloc((i + 2) * sizeof(char *));
		if (!temp)
		{
			ft_free_content(data);
			return (NULL);
		}
		i = 0;
		while (data[i])
		{
			temp[i] = data[i];
			i++;
		}
		free(data);
		data = temp;
		data[i] = ft_strdup(&content[ofset]);
		if (!data[i])
		{
			ft_free_content(data);
			return (NULL);
		}
		data[i + 1] = NULL;
	}
	return (data);
}
