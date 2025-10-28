#include "dnd_tools.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/vector.hpp"

typedef struct s_buff_duration_entry
{
    const char  *name;
    int         *duration;
}   t_buff_duration_entry;

typedef struct s_buff_special_entry
{
    int         *duration;
    void        (*callback)(t_char *);
}   t_buff_special_entry;

typedef struct s_buff_flag_entry
{
    int         *flag;
    void        (*callback)(t_char *);
}   t_buff_flag_entry;

static void    ft_update_buff_duration(t_char * info, const char *buff_name, int duration)
{
    if (duration == 0)
        pf_printf("%s just lost his %s buff\n", info->name, buff_name);
    else if (duration == 1)
        pf_printf("%s has a single turn of %s left\n", info->name, buff_name);
    else
        pf_printf("%s has %d turns left on his %s buff\n", info->name, duration, buff_name);
    return ;
}

static void    ft_update_buf_duration(t_char * info, const char *buf_name, int *duration)
{
    (*duration)--;
    ft_update_buff_duration(info, buf_name, *duration);
    return ;
}

static int ft_collect_duration_entries(t_char * info,
        ft_vector<t_buff_duration_entry> &entries)
{
    t_buff_duration_entry entry;

    if (!info)
        return (1);
    entries.clear();
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.name = "bless";
    entry.duration = &info->bufs.bless.duration;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.name = "protective winds";
    entry.duration = &info->bufs.protective_winds.duration;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    return (0);
}

static void ft_tick_duration_entries(t_char * info,
        ft_vector<t_buff_duration_entry> &entries)
{
    size_t count;
    size_t index;

    if (!info)
        return ;
    count = entries.size();
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return ;
    }
    index = 0;
    while (index < count)
    {
        t_buff_duration_entry   &entry = entries[index];

        if (entries.get_error() != ER_SUCCESS)
        {
            ft_errno = entries.get_error();
            return ;
        }
        if (entry.duration && entry.name && *(entry.duration) > 0)
            ft_update_buf_duration(info, entry.name, entry.duration);
        index++;
    }
    return ;
}

static void ft_update_chaos_armor_tick(t_char * info)
{
    ft_update_buf_duration(info, "chaos armor", &info->bufs.chaos_armor.duration);
    info->concentration.duration = info->bufs.chaos_armor.duration;
    if (info->concentration.duration)
        ft_remove_concentration(info);
    return ;
}

static int ft_collect_special_entries(t_char * info,
        ft_vector<t_buff_special_entry> &entries)
{
    t_buff_special_entry entry;

    if (!info)
        return (1);
    entries.clear();
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.duration = &info->bufs.lightning_strike.duration;
    entry.callback = ft_update_lightning_strike;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.duration = &info->bufs.lightning_strikeV2.duration;
    entry.callback = ft_update_lightningV2_strike;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.duration = &info->bufs.flame_geyser.duration;
    entry.callback = ft_update_flame_geyser;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.duration = &info->bufs.meteor_strike.duration;
    entry.callback = ft_update_meteor_strike;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.duration = &info->bufs.rejuvenation.duration;
    entry.callback = ft_update_buff_rejuvenation;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.duration = &info->bufs.chaos_armor.duration;
    entry.callback = ft_update_chaos_armor_tick;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    return (0);
}

static void ft_run_special_entries(t_char * info,
        ft_vector<t_buff_special_entry> &entries)
{
    size_t count;
    size_t index;

    if (!info)
        return ;
    count = entries.size();
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return ;
    }
    index = 0;
    while (index < count)
    {
        t_buff_special_entry   &entry = entries[index];

        if (entries.get_error() != ER_SUCCESS)
        {
            ft_errno = entries.get_error();
            return ;
        }
        if (entry.duration && entry.callback && *(entry.duration) > 0)
            entry.callback(info);
        index++;
    }
    return ;
}

static int ft_collect_flag_entries(t_char * info,
        ft_vector<t_buff_flag_entry> &entries)
{
    t_buff_flag_entry entry;

    if (!info)
        return (1);
    entries.clear();
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.flag = &info->bufs.earth_pounce.active;
    entry.callback = ft_update_earth_pounce;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.flag = &info->bufs.arcane_pounce.active;
    entry.callback = ft_update_arcane_pounce;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.flag = &info->bufs.frost_breath.active;
    entry.callback = ft_update_frost_breath;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    entry.flag = &info->bufs.shadow_illusion.active;
    entry.callback = ft_update_shadow_illusion;
    entries.push_back(entry);
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return (1);
    }
    return (0);
}

static void ft_run_flag_entries(t_char * info,
        ft_vector<t_buff_flag_entry> &entries)
{
    size_t count;
    size_t index;

    if (!info)
        return ;
    count = entries.size();
    if (entries.get_error() != ER_SUCCESS)
    {
        ft_errno = entries.get_error();
        return ;
    }
    index = 0;
    while (index < count)
    {
        t_buff_flag_entry  &entry = entries[index];

        if (entries.get_error() != ER_SUCCESS)
        {
            ft_errno = entries.get_error();
            return ;
        }
        if (entry.flag && entry.callback && *(entry.flag) == 1)
            entry.callback(info);
        index++;
    }
    return ;
}

void    ft_update_buf(t_char * info)
{
    ft_vector<t_buff_duration_entry> duration_entries(2);
    ft_vector<t_buff_special_entry> special_entries(6);
    ft_vector<t_buff_flag_entry> flag_entries(4);

    if (!info)
        return ;
    if (duration_entries.get_error() != ER_SUCCESS)
    {
        ft_errno = duration_entries.get_error();
        return ;
    }
    if (ft_collect_duration_entries(info, duration_entries) == 0)
        ft_tick_duration_entries(info, duration_entries);
    if (special_entries.get_error() != ER_SUCCESS)
    {
        ft_errno = special_entries.get_error();
        return ;
    }
    if (ft_collect_special_entries(info, special_entries) == 0)
        ft_run_special_entries(info, special_entries);
    if (flag_entries.get_error() != ER_SUCCESS)
    {
        ft_errno = flag_entries.get_error();
        return ;
    }
    if (ft_collect_flag_entries(info, flag_entries) == 0)
        ft_run_flag_entries(info, flag_entries);
    return ;
}
