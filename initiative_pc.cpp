#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/JSon/document.hpp"
#include "dnd_tools.hpp"
#include "key_list.hpp"

static void ft_reset_player_defaults(t_pc *player)
{
    if (!player)
        return ;
    if (player->name)
    {
        cma_free(player->name);
        player->name = ft_nullptr;
    }
    player->initiative = -1;
    player->position.x = -1;
    player->position.y = -1;
    player->position.z = -1;
    player->next = ft_nullptr;
    return ;
}

static int ft_player_json_report_missing(const char *field, char *filename)
{
    const char *file_label;

    file_label = filename;
    if (!file_label)
        file_label = "player save";
    pf_printf_fd(2, "JSON player save missing key %s in %s\n", field, file_label);
    return (1);
}

static int ft_player_json_report_invalid(const char *field, const char *value, char *filename)
{
    const char *file_label;
    const char *value_label;

    file_label = filename;
    if (!file_label)
        file_label = "player save";
    value_label = value;
    if (!value_label)
        value_label = "";
    pf_printf_fd(2, "JSON player save invalid value %s for key %s in %s\n", value_label, field, file_label);
    return (1);
}

static int ft_player_json_assign_int(int *target, const char *value, const char *field, char *filename)
{
    if (!target)
        return (1);
    if (!value)
        return (ft_player_json_report_missing(field, filename));
    if (ft_check_value(value))
        return (ft_player_json_report_invalid(field, value, filename));
    *target = ft_atoi(value);
    return (0);
}

static int ft_validate_player_fields(t_pc *player)
{
    if (!(player->initiative >= 0 && player->initiative <= 50))
    {
        pf_printf_fd(2, "Initiative value not found: %d\n", player->initiative);
        return (1);
    }
    if (!(player->position.x >= 0 && player->position.x <= MAX_COORDINATE))
    {
        pf_printf_fd(2, "Position X value not found: %d\n", player->position.x);
        return (1);
    }
    if (!(player->position.y >= 0 && player->position.y <= MAX_COORDINATE))
    {
        pf_printf_fd(2, "Position Y value not found: %d\n", player->position.y);
        return (1);
    }
    if (!(player->position.z >= 0 && player->position.z <= MAX_COORDINATE))
    {
        pf_printf_fd(2, "Position Z value not found: %d\n", player->position.z);
        return (1);
    }
    if (!player->name)
    {
        pf_printf_fd(2, "Player name not found\n");
        return (1);
    }
    return (0);
}

int ft_check_stat_pc_json_object(t_pc *player, json_document *document, json_group *player_group, char *filename)
{
    json_item   *item;
    int         error;

    if (!player || !document || !player_group)
        return (1);
    ft_reset_player_defaults(player);
    item = document->find_item(player_group, PLAYER_JSON_NAME_KEY);
    if (!item || !item->value)
        return (ft_player_json_report_missing(PLAYER_JSON_NAME_KEY, filename));
    player->name = cma_strdup(item->value);
    if (!player->name)
        return (1);
    item = document->find_item(player_group, PLAYER_JSON_INITIATIVE_KEY);
    if (!item || !item->value)
    {
        ft_reset_player_defaults(player);
        return (ft_player_json_report_missing(PLAYER_JSON_INITIATIVE_KEY, filename));
    }
    error = ft_player_json_assign_int(&player->initiative, item->value,
            PLAYER_JSON_INITIATIVE_KEY, filename);
    if (error)
    {
        ft_reset_player_defaults(player);
        return (1);
    }
    item = document->find_item(player_group, PLAYER_JSON_POSITION_X_KEY);
    if (!item || !item->value)
    {
        ft_reset_player_defaults(player);
        return (ft_player_json_report_missing(PLAYER_JSON_POSITION_X_KEY, filename));
    }
    error = ft_player_json_assign_int(&player->position.x, item->value,
            PLAYER_JSON_POSITION_X_KEY, filename);
    if (error)
    {
        ft_reset_player_defaults(player);
        return (1);
    }
    item = document->find_item(player_group, PLAYER_JSON_POSITION_Y_KEY);
    if (!item || !item->value)
    {
        ft_reset_player_defaults(player);
        return (ft_player_json_report_missing(PLAYER_JSON_POSITION_Y_KEY, filename));
    }
    error = ft_player_json_assign_int(&player->position.y, item->value,
            PLAYER_JSON_POSITION_Y_KEY, filename);
    if (error)
    {
        ft_reset_player_defaults(player);
        return (1);
    }
    item = document->find_item(player_group, PLAYER_JSON_POSITION_Z_KEY);
    if (!item || !item->value)
    {
        ft_reset_player_defaults(player);
        return (ft_player_json_report_missing(PLAYER_JSON_POSITION_Z_KEY, filename));
    }
    error = ft_player_json_assign_int(&player->position.z, item->value,
            PLAYER_JSON_POSITION_Z_KEY, filename);
    if (error)
    {
        ft_reset_player_defaults(player);
        return (1);
    }
    error = ft_validate_player_fields(player);
    if (error)
    {
        ft_reset_player_defaults(player);
        return (1);
    }
    return (0);
}
