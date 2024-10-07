#include "dnd_tools.hpp"
#include "character.hpp"

void	ft_excecute_test(const char *string1, t_name *name)
{
	const char *args[2];

	args[0] = string1;
	args[1] = nullptr;
	ft_test_excecute(args, 1, name);
	return ;
}

void	ft_excecute_test(const char *string1, const char *string2, t_name *name)
{
	const char *args[3];

	args[0] = string1;
	args[1] = string2;
	args[2] = nullptr;
	ft_test_excecute(args, 2, name);
	return ;
}

void	ft_excecute_test(const char *string1, const char *string2, const char *string3, t_name *name)
{
	const char *args[4];

	args[0] = string1;
	args[1] = string2;
	args[2] = string3;
	args[3] = nullptr;
	ft_test_excecute(args, 3, name);
	return ;
}

void	ft_excecute_test(const char *string1, const char *string2, const char *string3, const char *string4, t_name *name)
{
	const char *args[5];

	args[0] = string1;
	args[1] = string2;
	args[2] = string3;
	args[3] = string4;
	args[4] = nullptr;
	ft_test_excecute(args, 4, name);
	return ;
}

void	ft_excecute_test(const char *string1, const char *string2, const char *string3, const char *string4, const char *string5, t_name *name)
{
	const char *args[6];

	args[0] = string1;
	args[1] = string2;
	args[2] = string3;
	args[3] = string4;
	args[4] = string5;
	args[5] = nullptr;
	ft_test_excecute(args, 5, name);
	return ;
}
