#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_file.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/JSon/document.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Libft/libft.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include "key_list.hpp"

static int ft_add_player_line(json_document &document, json_group *group, int index,
        const char *format, ...)
{
    va_list args;
    char *buffer;
    size_t buffer_size;
    FILE *stream;
    char *index_string;
    json_item *item;

    buffer = ft_nullptr;
    buffer_size = 0;
    stream = open_memstream(&buffer, &buffer_size);
    if (!stream)
        return (1);
    va_start(args, format);
    ft_vfprintf(stream, format, args);
    va_end(args);
    fclose(stream);
    if (!buffer)
        return (1);
    index_string = cma_itoa(index);
    if (!index_string)
    {
        free(buffer);
        return (1);
    }
    item = document.create_item(index_string, buffer);
    cma_free(index_string);
    free(buffer);
    if (!item)
        return (1);
    document.add_item(group, item);
    return (0);
}

void    ft_save_pc(t_pc *player, ft_file &file)
{
    json_document       document;
    json_group          *group;
    char                *content;

    group = document.create_group("lines");
    if (!group)
    {
        pf_printf_fd(2, "Failed to create JSON group for player save\n");
        return ;
    }
    document.append_group(group);
    if (ft_add_player_line(document, group, 0, "NAME=%s", player->name)
        || ft_add_player_line(document, group, 1, "INITIATIVE=%d", player->initiative)
        || ft_add_player_line(document, group, 2, "%s%d", POSITION_X_KEY, player->position.x)
        || ft_add_player_line(document, group, 3, "%s%d", POSITION_Y_KEY, player->position.y)
        || ft_add_player_line(document, group, 4, "%s%d", POSITION_Z_KEY, player->position.z))
    {
        pf_printf_fd(2, "Failed to build JSON player save\n");
        return ;
    }
    content = document.write_to_string();
    if (!content)
    {
        pf_printf_fd(2, "Failed to serialize player save\n");
        return ;
    }
    file.write(content);
    if (file.get_error() != ER_SUCCESS)
        pf_printf_fd(2, "Failed to write player save: %s\n", file.get_error_str());
    cma_free(content);
    return ;
}
