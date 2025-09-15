#include "dnd_tools.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Printf/printf.hpp"

void    ft_encounter(int argument_count, const char **argument_vector, t_name *name)
{
    if (argument_count >= 1 && ft_strcmp_dnd(argument_vector[0], "xavius") == 0)
    {
        if (argument_count == 1)
        {
            ft_excecute_test("shield_spell_a", "init", name);
            ft_excecute_test("demonic_portal_a", "init", name);
            ft_excecute_test("xavius", "init", name);
            ft_excecute_test("malfurion", "init", name);
        }
        else if (argument_count >= 3 && ft_strcmp_dnd(argument_vector[1], "damage") == 0)
        {
            if (ft_strcmp_dnd(argument_vector[2], "portal") == 0)
            {
                const char      *input[] = {"demonic_portal_a", ft_nullptr};
                t_char          *info = ft_demonic_portal_a(1, input, name, 1);

                if (info != ft_nullptr)
                {
                    ft_deal_damage(info, "1", "force", 0, 1);
                    ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                    if (file.get_error())
                        pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file, file.get_error_str());
                    else
                        ft_npc_write_file(info, &info->stats, &info->d_resistance, file);
                    ft_free_info(info);
                }
            }
            else if (argument_count >= 4 &&
                    ft_strcmp_dnd(argument_vector[2], "shield") == 0 &&
                    ft_strcmp_dnd(argument_vector[3], "spell") == 0)
            {
                const char      *input[] = {"shield_spell_a", ft_nullptr};
                t_char          *info = ft_shield_spell_a(1, input, name, 1);

                if (info != ft_nullptr)
                {
                    ft_deal_damage(info, "1", "force", 0, 1);
                    ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                    if (file.get_error())
                        pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file, file.get_error_str());
                    else
                        ft_npc_write_file(info, &info->stats, &info->d_resistance, file);
                    ft_free_info(info);
                }
            }
        }
    }
    return ;
}

