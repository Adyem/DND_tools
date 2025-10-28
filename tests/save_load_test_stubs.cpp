#include "../dnd_tools.hpp"
#include "../identification.hpp"
#include "../libft/Errno/errno.hpp"

void ft_kill(t_char * info)
{
    (void)info;
    return ;
}

int ft_request_damage(t_char * info)
{
    (void)info;
    return (0);
}

void ft_check_initiative(t_char * info)
{
    (void)info;
    return ;
}

void ft_print_character_status(t_char * info, int number, int temp)
{
    (void)info;
    (void)number;
    (void)temp;
    return ;
}

void ft_npc_update_lightning_strike(t_char * info, const char **input)
{
    (void)info;
    (void)input;
    return ;
}

void ft_npc_update_buff(t_char * info, const char **input, int *buff, const char *name)
{
    (void)info;
    (void)input;
    (void)buff;
    (void)name;
    return ;
}

void ft_npc_check_ac(t_char * info, const char **input)
{
    (void)info;
    (void)input;
    return ;
}

int ft_saving_throw(t_char * info, const char *ability_score, int ability_mod, int save_mod)
{
    (void)info;
    (void)ability_score;
    (void)ability_mod;
    (void)save_mod;
    return (0);
}

void ft_cast_chaos_armor(t_char *info)
{
    (void)info;
    return ;
}

void ft_cast_cure_wounds(t_char * character)
{
    (void)character;
    return ;
}

void ft_cast_lightning_bolt(t_char * character)
{
    (void)character;
    return ;
}

void ft_cast_bless(t_char *info, const char **input)
{
    (void)info;
    (void)input;
    return ;
}

void ft_roll_initiative(t_char * info)
{
    (void)info;
    return ;
}

void ft_cast_hunters_mark(t_char *info, const char **input)
{
    (void)info;
    (void)input;
    return ;
}

void ft_check_concentration(t_char * info, int damage)
{
    (void)info;
    (void)damage;
    return ;
}

int ft_get_resistance(t_char * info, const char *type)
{
    if (type == ft_nullptr)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (-9999);
    }
    if (ft_strcmp(type, DAMAGE_TYPE_ACID) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_acid_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_BLUDGEONING) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_bludgeoning_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_COLD) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_cold_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_FIRE) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_fire_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_FORCE) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_force_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_LIGHTNING) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_lightning_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_NECROTIC) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_necrotic_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_PIERCING) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_piercing_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_POISON) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_poison_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_PSYCHIC) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_psychic_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_RADIANT) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_radiant_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_SLASHING) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_slashing_resistance(info));
    }
    if (ft_strcmp(type, DAMAGE_TYPE_THUNDER) == 0)
    {
        ft_errno = ER_SUCCESS;
        return (ft_calculate_thunder_resistance(info));
    }
    ft_errno = FT_ERR_INVALID_ARGUMENT;
    return (-9999);
}

void ft_npc_set_stat(t_char * info, const char **input)
{
    (void)info;
    (void)input;
    return ;
}

void ft_growth_stack(t_char * info, const char **input, int argc)
{
    (void)info;
    (void)input;
    (void)argc;
    return ;
}

void ft_change_stats_04(t_char * info, const char **input)
{
    (void)info;
    (void)input;
    return ;
}
