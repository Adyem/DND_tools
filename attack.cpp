#include "dnd_tools.hpp"
#include "identification.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/Template/math.hpp"
#include "libft/Template/shared_ptr.hpp"
#include "libft/ReadLine/readline.hpp"

extern bool g_dnd_test;

typedef struct s_damage_info
{
    int mod;
    int result;
    int damage;
    int stat_mod;
    int dice_amount;
    int dice_faces;
}   t_damage_info;

static int ft_readline_prompt_hit_or_miss(void)
{
    char *input;
    int invalid_attempts = 0;

    while ((input = rl_readline("Does the attack [hit/miss/exit]? ")) != ft_nullptr)
    {
        if ((ft_strcmp_dnd(input, "y") == 0) || (ft_strcmp_dnd(input, "yes") == 0)
            || (ft_strcmp_dnd(input, "hit") == 0))
        {
            cma_free(input);
            return (0);
        }
        else if ((ft_strcmp_dnd(input, "n") == 0) || (ft_strcmp_dnd(input, "no") == 0)
                 || (ft_strcmp_dnd(input, "miss") == 0))
        {
            cma_free(input);
            return (1);
        }
        else if (ft_strcmp_dnd(input, "exit") == 0)
        {
            cma_free(input);
            return (2);
        }
        else
        {
            invalid_attempts++;
            if (invalid_attempts >= 5)
            {
                pf_printf("Too many invalid attempts. Exiting the prompt.\n");
                cma_free(input);
                return (2);
            }
            pf_printf("Invalid input. Please type 'hit', 'miss', or 'exit' (Attempt %d/5).\n",
					invalid_attempts);
        }
        cma_free(input);
    }

    pf_printf_fd(2, "Error: read line memory allocation failed\n");
    return (-1);
}


static int ft_weapon_find_stat(ft_sharedptr<t_char> &info, t_equipment_id *weapon)
{
    if (!weapon->attack.stat)
        return (0);
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_STR) == 0)
        return (ft_calculate_str(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_DEX) == 0)
        return (ft_calculate_dex(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_CON) == 0)
        return (ft_calculate_con(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_INT) == 0)
        return (ft_calculate_inte(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_WIS) == 0)
        return (ft_calculate_wis(info));
    if (ft_strcmp_dnd(weapon->attack.stat, STAT_CHA) == 0)
        return (ft_calculate_cha(info));
    if (ft_strcmp_dnd(weapon->attack.stat, FINESSE) == 0)
        return max(ft_calculate_str(info), ft_calculate_dex(info));
    return (0);
}

static void ft_check_dice_amount_and_faces(t_equipment_id *weapon, t_damage_info *d_info,
                                           int offhand, ft_sharedptr<t_char> &info)
{
    d_info->dice_amount = weapon->attack.effect_dice_amount;
    d_info->dice_faces = weapon->attack.effect_dice_faces;
    if (offhand && weapon->slot == (SLOT_WEAPON | SLOT_OFFHAND_WEAPON))
    {
        d_info->dice_amount = weapon->attack.effect_secund_dice_amount;
        d_info->dice_faces = weapon->attack.effect_secund_dice_faces;
    }
    else if (!offhand && weapon->slot == SLOT_WEAPON
             && info->equipment.offhand_weapon.equipment_id == 0)
    {
        d_info->dice_amount = weapon->attack.effect_dice_amount;
        d_info->dice_faces = weapon->attack.effect_dice_faces;
    }
    return ;
}

static void ft_calculate_damage(t_equipment_id *weapon, t_damage_info *d_info, bool is_crit)
{
    int multiplier;

    if (is_crit)
        multiplier = 2;
    else
        multiplier = 1;

    d_info->damage = ft_dice_roll(d_info->dice_amount * multiplier, d_info->dice_faces)
                     + d_info->stat_mod;
    pf_printf("deals %d %s damage\n", d_info->damage, weapon->attack.damage_type);
    return ;
}

void ft_weapon_attack(ft_sharedptr<t_char> &info, t_equipment_id *weapon, int offhand)
{
    t_damage_info d_info;
    d_info.stat_mod = (ft_weapon_find_stat(info, weapon) - 10) / 2;
    d_info.result = ft_dice_roll(1, 20);
    if (d_info.result == -1)
    {
        pf_printf_fd(2, "101-Error: dice rolling error in attack\n");
        return ;
    }
    pf_printf("%s attacks with his/her %s and rolled a %d on the die.\n",
              info->name, weapon->name, d_info.result);
    if (d_info.result <= 1 + info->crit.attack_fail)
        pf_printf("A critical fail (%d)! That can't be good...\n", d_info.result);
    bool is_hit = false;
    if (g_dnd_test == true)
    {
        int test_roll = ft_dice_roll(1, 2);
        if (test_roll == 1)
            is_hit = true;
        else
            is_hit = false;

        if (is_hit)
            pf_printf("[TEST MODE] The attack is a HIT (random)!\n");
        else
        {
            pf_printf("[TEST MODE] The attack is a MISS (random)!\n");
            return ;
        }
    }
    else
    {
        int choice = ft_readline_prompt_hit_or_miss();
        if (choice == -1)
            return ;
        else if (choice == 2)
        {
            pf_printf("Exiting attack...\n");
            return ;
        }
        else if (choice == 1)
        {
            pf_printf("%s missed the attack.\n", info->name);
            return ;
        }
        else
            is_hit = true;
    }
    bool is_crit = false;
    if (d_info.result >= 20 - info->crit.attack)
    {
        is_crit = true;
        pf_printf("A critical hit (%d)!\n", d_info.result);
    }
    ft_check_dice_amount_and_faces(weapon, &d_info, offhand, info);
    ft_calculate_damage(weapon, &d_info, is_crit);
    return ;
}
