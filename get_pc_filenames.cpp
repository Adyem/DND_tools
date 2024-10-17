#include <dirent.h>
#include <string.h>
#include "libft/CMA/CMA.hpp"

// Function to get all filenames starting with 'pc--' minus the prefix
char **get_pc_files() {
    DIR *dir;
    struct dirent *entry;
    char **file_list;
    size_t capacity = 10;
    size_t count = 0;

    // Open the 'data' directory
    dir = opendir("data");
    if (!dir)
        return NULL;

    // Allocate initial memory for the file list
    file_list = (char **)cma_malloc(sizeof(char *) * capacity, false);
    if (!file_list) {
        closedir(dir);
        return NULL;
    }

    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Check if the filename starts with 'pc--'
        if (strncmp(entry->d_name, "pc--", 4) == 0) {
            // Get the substring after 'pc--'
            char *filename = entry->d_name + 4;

            // Duplicate the filename using cma_strdup
            char *filename_copy = cma_strdup(filename, false);
            if (!filename_copy) {
                // Handle memory allocation failure
                for (size_t i = 0; i < count; i++) {
                    cma_free(file_list[i]);
                }
                cma_free(file_list);
                closedir(dir);
                return NULL;
            }

            // Resize the array if necessary
            if (count >= capacity) {
                capacity *= 2;
                char **new_list = (char **)cma_realloc(file_list, sizeof(char *) * capacity, false);
                if (!new_list) {
                    // Handle memory allocation failure
                    for (size_t i = 0; i < count; i++) {
                        cma_free(file_list[i]);
                    }
                    cma_free(file_list);
                    cma_free(filename_copy);
                    closedir(dir);
                    return NULL;
                }
                file_list = new_list;
            }

            // Add the filename to the list
            file_list[count++] = filename_copy;
        }
    }
    closedir(dir);

    // Null-terminate the array
    if (count >= capacity) {
        char **new_list = (char **)cma_realloc(file_list, sizeof(char *) * (capacity + 1), false);
        if (!new_list) {
            for (size_t i = 0; i < count; i++) {
                cma_free(file_list[i]);
            }
            cma_free(file_list);
            return NULL;
        }
        file_list = new_list;
    }
    file_list[count] = NULL;

    return file_list;
}

