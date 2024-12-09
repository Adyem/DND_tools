#include "dnd_tools.hpp"
#include "libft/CPP_class/string.hpp"

int	ft_check_value(const char *input)
{
	long	check;
	int		i;
	int		sign;

	check = 0;
	i = 0;
	sign = 1;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (!input[i])
		return (1);
	if (input[0] == '-')
		sign = -1;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			check = (check * 10) + input[i] - '0';
			if (sign * check < -2147483648 || sign * check > 2147483647)
				return (2);
			i++;
		}
		else
			return (3);
	}
	return (0);
}

int	ft_strcmp_dnd(const char *string1, const char *string2)
{
	if (!string1 || !string2)
		return (-1);
	while (*string1 && (*string1) == (*string2))
	{
		string1++;
		string2++;
	}
	return ((int)(*string1) - (int)(*string2));
}

ft_string ft_check_availeble_spell_slots(t_char *character)
{
	ft_string available_levels;

	if (character->spell_slots.level_1.available > 0)
		available_levels.append(" 1,");
	if (character->spell_slots.level_2.available > 0)
		available_levels.append(" 2,");
	if (character->spell_slots.level_3.available > 0)
		available_levels.append(" 3,");
	if (character->spell_slots.level_4.available > 0)
		available_levels.append(" 4,");
	if (character->spell_slots.level_5.available > 0)
		available_levels.append(" 5,");
	if (character->spell_slots.level_6.available > 0)
		available_levels.append(" 6,");
	if (character->spell_slots.level_7.available > 0)
		available_levels.append(" 7,");
	if (character->spell_slots.level_8.available > 0)
		available_levels.append(" 8,");
	if (character->spell_slots.level_9.available > 0)
		available_levels.append(" 9,");
	if (!available_levels.empty())
		available_levels.erase(available_levels.size() - 1, 1);
	return (available_levels);
}
