#include "libft/Printf/ft_printf.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <cstdlib>

void ft_cast_hunters_mark(t_char *info, const char **input)
{
    t_buff buff;

    buff.target_amount = 1;
    buff.error = 1;
    buff.duration = 50;
    buff.dice_faces_mod = 6;
    buff.dice_amount_mod = 1;
    buff.target_amount = 1;
    buff.spell_id = HUNTERS_MARK_ID;
    buff.buff = 0;
    buff.cast_spell = ft_cast_hunters_mark_second_appli;
	buff.cleanup_f = ft_cleanup_hunters_mark;
    ft_cast_concentration(info, input, &buff);
    return ;
}

static int ft_is_caster_name_present(char **caster_name_list, const char *name)
{
    int i;

    if (!caster_name_list || !name)
        return (0);
    i = 0;
    while (caster_name_list[i])
    {
        if (ft_strcmp_dnd(caster_name_list[i], name) == 0)
            return (1);
        i++;
    }
    return (0);
}

int ft_cast_hunters_mark_second_appli(t_char *target, const char **input, t_buff *buff)
{
    int i;

    (void)buff;
    if (DEBUG == 1)
        ft_printf("setting the caster name in the target %s %p\n", input[0], (void *)target);
    if (target)
    {
        if (ft_is_caster_name_present(target->debufs.hunters_mark.caster_name, input[0]))
        {
            ft_printf_fd(2, "102-Error: Caster name already present\n");
            return (1);
        }
        if (ft_update_caster_name(&target->debufs.hunters_mark.caster_name, input[0]))
            return (2);
    }
    if (DEBUG == 1 && target)
    {
        i = 0;
        while (target->debufs.hunters_mark.caster_name && target->debufs.hunters_mark.caster_name[i])
        {
            ft_printf("%s has cast hunter's mark\n", target->debufs.hunters_mark.caster_name[i]);
            i++;
        }
    }
    target->debufs.hunters_mark.amount++;
    return (0);
}

void ft_cleanup_hunters_mark(t_char *info, t_char *target, t_buff *buff)
{
	int len;

	(void)info;
	(void)buff;
    if (target)
    {
        target->debufs.hunters_mark.amount--;
		len = ft_double_char_length(target->debufs.hunters_mark.caster_name);
        if (len > 0)
        {
            free(target->debufs.hunters_mark.caster_name[len - 1]);
            target->debufs.hunters_mark.caster_name[len - 1] = nullptr;
        }
    }
}
