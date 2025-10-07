#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_file.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/JSon/document.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Libft/libft.hpp"
#include "key_list.hpp"

static int ft_add_player_field(json_document &document, json_group *group,
        const char *key, const char *value)
{
    json_item *item;

    if (!group || !key || !value)
        return (1);
    item = document.create_item(key, value);
    if (!item)
        return (1);
    document.add_item(group, item);
    return (0);
}

static int ft_add_player_field_int(json_document &document, json_group *group,
        const char *key, int value)
{
    json_item *item;

    if (!group || !key)
        return (1);
    item = document.create_item(key, value);
    if (!item)
        return (1);
    document.add_item(group, item);
    return (0);
}

void    ft_save_pc(t_pc *player, ft_file &file)
{
    json_document       document;
    json_group          *player_group;
    char                *content;

    player_group = document.create_group(PLAYER_JSON_GROUP_NAME);
    if (!player_group)
    {
        pf_printf_fd(2, "Failed to create JSON player group for player save\n");
        return ;
    }
    document.append_group(player_group);
    if (ft_add_player_field(document, player_group, PLAYER_JSON_NAME_KEY, player->name)
        || ft_add_player_field_int(document, player_group, PLAYER_JSON_INITIATIVE_KEY, player->initiative)
        || ft_add_player_field_int(document, player_group, PLAYER_JSON_POSITION_X_KEY, player->position.x)
        || ft_add_player_field_int(document, player_group, PLAYER_JSON_POSITION_Y_KEY, player->position.y)
        || ft_add_player_field_int(document, player_group, PLAYER_JSON_POSITION_Z_KEY, player->position.z))
    {
        pf_printf_fd(2, "Failed to build player fields for JSON save\n");
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
