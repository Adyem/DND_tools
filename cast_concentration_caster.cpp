#include "dnd_tools.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Printf/printf.hpp"

int ft_update_caster_name(ft_set<ft_string> *caster_name, const char *input_name)
{
    int error_code;

    if (!caster_name || !input_name)
        return (1);
    if (DEBUG == 1)
        pf_printf("adding the new caster name to the target struct %s\n", input_name);
    caster_name->insert(ft_string(input_name));
    error_code = caster_name->get_error();
    if (error_code != ER_SUCCESS && error_code != FT_ERR_NOT_FOUND)
    {
        pf_printf_fd(2, "165-Error updating caster name: %s\n",
            caster_name->get_error_str());
        return (1);
    }
    return (0);
}
