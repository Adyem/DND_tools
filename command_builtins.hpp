#ifndef COMMAND_BUILTINS_HPP
# define COMMAND_BUILTINS_HPP

# include "dnd_tools.hpp"

# define FT_BUILTIN_NOT_FOUND 0
# define FT_BUILTIN_HANDLED 1
# define FT_BUILTIN_EXIT -1
# define FT_BUILTIN_ERROR -2

int ft_dispatch_builtin_command(char **input, int argc, t_name *name);

#endif
