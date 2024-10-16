#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <time.h>

char **get_random_pc_file(void) {
    const char *directory_name = "data";
    const char *prefix = "pc--";
    size_t prefix_len = ft_strlen(prefix);
    DIR *dir;
    struct dirent *entry;
    char **file_list = NULL;
    size_t count = 0;

    dir = opendir(directory_name);
    if (dir == NULL) {
        perror("Failed to open directory");
        char **result = (char **)cma_malloc(sizeof(char *) * 2, false);
        if (result != NULL) {
            result[0] = NULL;
            result[1] = NULL;
        }
        return result;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Ensure it's a regular file
            if (strncmp(entry->d_name, prefix, prefix_len) == 0) {
                count++;
            }
        }
    }
    if (count == 0) {
        closedir(dir);
        char **result = (char **)cma_malloc(sizeof(char *) * 2, false);
        if (result != NULL) {
            result[0] = NULL;
            result[1] = NULL;
        }
        return result;
    }
    file_list = (char **)malloc(sizeof(char *) * count);
    if (file_list == NULL) {
        perror("Failed to allocate memory for file list");
        closedir(dir);
        char **result = (char **)cma_malloc(sizeof(char *) * 2, false);
        if (result != NULL) {
            result[0] = NULL;
            result[1] = NULL;
        }
        return result;
    }
    rewinddir(dir);
    size_t index = 0;
    while ((entry = readdir(dir)) != NULL && index < count) {
        if (entry->d_type == DT_REG) {
            if (strncmp(entry->d_name, prefix, prefix_len) == 0) {
                size_t name_len = strlen(entry->d_name) - prefix_len;
                char *name = (char *)cma_malloc(sizeof(char) * (name_len + 1), false);
                if (name == NULL) {
                    perror("cma_malloc failed for filename");
                    for (size_t i = 0; i < index; i++) {
                        cma_free(file_list[i]);
                    }
                    free(file_list);
                    closedir(dir);
                    char **result = (char **)cma_malloc(sizeof(char *) * 2, false);
                    if (result != NULL) {
                        result[0] = NULL;
                        result[1] = NULL;
                    }
                    return result;
                }
                strncpy(name, entry->d_name + prefix_len, name_len);
                name[name_len] = '\0';
                file_list[index++] = name;
            }
        }
    }

    closedir(dir);
    size_t random_index = rand() % count;
    char *selected_name = file_list[random_index];
    for (size_t i = 0; i < count; i++) {
        if (i != random_index) {
            cma_free(file_list[i]);
        }
    }
    free(file_list);
    char **result = (char **)cma_malloc(sizeof(char *) * 2, false);
    if (result == NULL) {
        cma_free(selected_name);
        return NULL;
    }

    result[0] = selected_name;
    result[1] = NULL;
    return result;
}
