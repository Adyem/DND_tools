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

int ft_set_stats_check_name(char *name)
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
        if (ft_strncmp(entry->d_name, PREFIX_TO_SKIP, strlen(PREFIX_TO_SKIP)) == 0)
            continue;
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        remove_exclude_prefix(filename);
        if (ft_strcmp_dnd(filename, name) == 0)
		{
            closedir(dir);
            return 0;
		}
    }
    closedir(dir);
    return 1;
}
