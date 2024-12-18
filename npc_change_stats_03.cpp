#include "libft/Printf/printf.hpp"
#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"

static void ft_npc_update_hp(ft_sharedptr<t_char> &info, const char **input)
{
    int number;
    int temp;

    if (ft_check_value(input[2]))
    {
        pf_printf("Expecting a positive or negative integer\n");
        return ;
    }
    number = ft_atoi(input[2]);
    temp = info->stats.health;
    info->stats.health = info->stats.health + number;
    if (info->stats.health > info->dstats.health)
        info->stats.health = info->dstats.health;
    else if (info->stats.health < 0)
        info->stats.health = 0;
    ft_print_character_status(info, number, temp);
	return ;
}

void ft_npc_set_stat(ft_sharedptr<t_char> &info, const char **input)
{
    if (ft_strcmp_dnd(input[2], "flank") == 0 || ft_strcmp_dnd(input[2], "flanking") == 0)
    {
        info->flags.flanking = 1;
        if (ft_strcmp_dnd(input[1], "attack") == 0)
        {
            if (info->equipment.weapon.attack.function)
                info->equipment.weapon.attack.function(info, &info->equipment.weapon, 0);
            else
                pf_printf("%s No attack set\n", info->name);
        }
        else if (ft_strcmp_dnd(input[1], "ranged_attack") == 0)
        {
            if (info->equipment.ranged_weapon.attack.function)
                info->equipment.ranged_weapon.attack.function(info, &info->equipment.ranged_weapon, 0);
            else
                pf_printf("%s No ranged attack set\n", info->name);
        }
        else
        {
            pf_printf("6-Error: Invalid argument given\n");
        }
    }
    else if (ft_strcmp_dnd(input[1], "blinded") == 0)
        ft_set_debuf_blinded(info, input);
    else if (ft_strcmp_dnd(input[1], "hp") == 0)
        ft_npc_update_hp(info, input);
    else if (ft_strcmp_dnd(input[1], "bless") == 0)
        ft_npc_update_buff(info, input, &info->bufs.bless.duration, "bless");
    else if (ft_strcmp_dnd(input[1], "lightning_strike") == 0)
        ft_npc_update_lightning_strike(info, input);
    else if (ft_strcmp_dnd(input[1], "protective_winds") == 0)
        ft_npc_update_buff(info, input, &info->bufs.protective_winds.duration, "protective winds");
    else if (ft_strcmp_dnd(input[1], "to_hit") == 0)
        ft_npc_check_ac(info, input);
    else if (ft_strcmp_dnd(input[2], "save") == 0)
    {
        if (ft_strcmp_dnd(input[1], "str") == 0)
            ft_saving_throw(info, "strength", ft_calculate_str(info), info->save_mod.str);
        else if (ft_strcmp_dnd(input[1], "dex") == 0)
            ft_saving_throw(info, "dexterity", ft_calculate_dex(info), info->save_mod.dex);
        else if (ft_strcmp_dnd(input[1], "con") == 0)
            ft_saving_throw(info, "constitution", ft_calculate_con(info), info->save_mod.con);
        else if (ft_strcmp_dnd(input[1], "int") == 0)
            ft_saving_throw(info, "intelligence", ft_calculate_inte(info), info->save_mod.inte);
        else if (ft_strcmp_dnd(input[1], "wis") == 0)
            ft_saving_throw(info, "wisdom", ft_calculate_wis(info), info->save_mod.wis);
        else if (ft_strcmp_dnd(input[1], "cha") == 0)
            ft_saving_throw(info, "charisma", ft_calculate_cha(info), info->save_mod.cha);
        else
        {
            pf_printf("4-%s Invalid argument given\n", info->name);
            return ;
        }
    }
    else if (ft_strcmp_dnd(input[1], "cast") == 0)
    {
		if (ft_strcmp_dnd(input[2], "chaos_armor") == 0)
            ft_cast_chaos_armor(info);
		else if (ft_strcmp_dnd(input[2], "cure_wounds") == 0)
			ft_cast_cure_wounds(info);
		else
            pf_printf("7-%s invalid command\n", info->name);
    }
    else if (ft_strcmp_dnd(input[1], "initiative") == 0)
    {
        if (ft_strcmp_dnd(input[2], "roll") == 0)
            ft_roll_initiative(info);
        else
        {
            pf_printf("3-%s invalid command\n", info->name);
            return ;
        }
    }
    else
    {
        pf_printf("5-%s Invalid argument given\n", info->name);
        return ;
    }
	return ;
}
