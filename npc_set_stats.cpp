#include "libft/Libft/libft.hpp"
#include "key_list.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"

static int ft_set_stat_int_internal(char *content, const char *key, int *field, int unset_value,
		ft_sharedptr<t_char> &info)
{
    int index = ft_strlen(key);
    if (ft_strncmp(content, key, index) == 0 && (unset_value == -1 || *field == unset_value))
    {
        *field = ft_check_stat(info, content, index);
        return (1);
    }
    return (0);
}

static int ft_handle_int_mapping(char *line, const t_key_value_triplet *stat_key_value_pairs,
		ft_sharedptr<t_char> &info)
{
    int index = 0;
    while (stat_key_value_pairs[index].key)
    {
        if (ft_set_stat_int_internal(line, stat_key_value_pairs[index].key,
				stat_key_value_pairs[index].value, stat_key_value_pairs[index].unset_value,
				info) == 1)
            return (0);
        index++;
    }
    return (1);
}

static int ft_handle_set_stat_char_pointer(char *content_i, size_t key_len, char **target_field)
{
    if (ft_set_stat_player(key_len, const_cast<const char **>(target_field), content_i))
        return (-1);
    return (0);
}

static int ft_handle_set_stat_double_char(char *content_i, size_t key_len, char ***target_field,
		ft_sharedptr<t_char> &info)
{
    *target_field = ft_set_stats_con_targets(content_i, key_len, *target_field, info);
    if (*target_field == ft_nullptr)
        return (-1);
    return (0);
}

static int ft_handle_string_fields(char *line, ft_sharedptr<t_char> &info)
{
	if (ft_strncmp(line, CONC_TARGETS_KEY, ft_strlen(CONC_TARGETS_KEY)) == 0)
        return (ft_handle_set_stat_double_char(line, ft_strlen(CONC_TARGETS_KEY),
				&info->concentration.targets, info));
	if (ft_strncmp(line, HUNTERS_MARK_CASTER_KEY, ft_strlen(HUNTERS_MARK_CASTER_KEY)) == 0)
        return (ft_handle_set_stat_double_char(line, ft_strlen(HUNTERS_MARK_CASTER_KEY),
				&info->debufs.hunters_mark.caster_name, info));
	if (ft_strncmp(line, METEOR_STRIKE_TARGET_KEY, ft_strlen(METEOR_STRIKE_TARGET_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(METEOR_STRIKE_TARGET_KEY),
				&info->bufs.meteor_strike.target_id));
	if (ft_strncmp(line, FROST_BREATH_TARGET_ID_KEY, ft_strlen(FROST_BREATH_TARGET_ID_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(FROST_BREATH_TARGET_ID_KEY),
				&info->bufs.frost_breath.target_id));
	if (ft_strncmp(line, ARCANE_POUNCE_TARGET_ID_KEY, ft_strlen(ARCANE_POUNCE_TARGET_ID_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(ARCANE_POUNCE_TARGET_ID_KEY),
				&info->bufs.arcane_pounce.target_id));
	if (ft_strncmp(line, EARTH_POUNCE_TARGET_ID_KEY, ft_strlen(EARTH_POUNCE_TARGET_ID_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(EARTH_POUNCE_TARGET_ID_KEY),
				&info->bufs.earth_pounce.target_id));
	if (ft_strncmp(line, BUFF_BLESS_CASTER_NAME_KEY, ft_strlen(BUFF_BLESS_CASTER_NAME_KEY)) == 0)
        return (ft_handle_set_stat_char_pointer(line, ft_strlen(BUFF_BLESS_CASTER_NAME_KEY),
				&info->bufs.earth_pounce.target_id));
    return (1);
}

int ft_set_stats(ft_sharedptr<t_char> &info, char **content)
{
    t_key_value_triplet *stat_key_value_pairs = initialize_stat_key_value_pairs(info);

    int index = 0;
    while (content[index])
	{
        if (ft_handle_int_mapping(content[index], stat_key_value_pairs, info) == 0)
		{
            index++;
            continue ;
        }
        int error_value = ft_handle_string_fields(content[index], info);
        if (error_value == 0)
		{
            index++;
            continue ;
        }
        pf_printf_fd(2, "1-Something is wrong with the save file for %s at the line: %s"
                         ", please reinitialize the save\n", info->name, content[index]);
        info->flags.error = 1;
        return (1);
    }
    return (0);
}

