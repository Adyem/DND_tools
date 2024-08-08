#include "dnd_tools.h"

static int	ft_check_open_braces(char *string, int i, int *open_braces)
{
	if (i > 0)
		if (ft_roll_check_character(string[i - 1]))
			return (1);
	if (ft_roll_check_number_next(string, i))
		return (1);
	(*open_braces)++;
	return (0);
}

static int	ft_check_close_braces(char *string, int i,
				int open_braces, int *close_braces)
{
	(*close_braces)++;
	if (i == 0 || open_braces < *close_braces)
		return (1);
	if (ft_roll_check_character(string[i + 1]))
		return (1);
	if (ft_roll_check_number_previous(string, i))
		return (1);
	return (0);
}

static int	ft_roll_check_arg(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '+' || string[i] == '-')
			i++;
		else if (string[i] == '/' || string[i] == '*')
			i++;
		else if (string[i] >= '0' || string[i] <= '9')
			i++;
		else if (string[i] == '(' || string[i] ==  ')')
			i++;
		else if (string[i] == 'd')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_check_plus_minus(char *string, int i)
{
	int sign_seen;

	sign_seen = 0;
	if (i > 0)
	{
		if (string[i - 1] == '+' || string[i - 1] == '-')
			sign_seen++;
		else if (ft_roll_check_number_previous(string, i) &&
				(ft_roll_check_character(string[i - 1])))
			return (1);
	}
	else if (ft_roll_check_number_previous(string, i))
		return (1);
	if (!((string[i + 1] == '+' && !sign_seen) ||
			(string[i + 1] == '-' && !sign_seen) ||
			(string[i + 1] >= '0' && string[i + 1] <= '9')))
		return (1);
	return (0);
}

static int	ft_check_divide_multiply(char *string, int i)
{
	if (i == 0)
		return (1);
	if (ft_roll_check_number_next(string, i))
		return (1);
	if (ft_roll_check_number_previous(string, i))
		return (1);
	return (0);
}

static int	ft_check_dice(char *string, int i)
{
	if (i == 0)
		return (0);
	if (ft_roll_check_number_previous(string, i))
		return (1);
	if (string[i - 1] == '/' || string[i - 1] == '*')
		return (0);
	else if (i > 1)
	{
		if (string[i - 1] == '-' && (ft_roll_check_character(string[i - 2])))
			return (1);
		else if (string[i + 1] == '-' || !string[i + 1])
			return (1);
	}
	return (0);
}

void debug_print_error(const char *error_message, int index)
{
    if (DEBUG)
        printf("Error: %s at index %d\n", error_message, index);
}

int ft_command_roll_validate(char *string) {
    int open_braces;
    int close_braces;
    int i;

    i = 0;
    open_braces = 0;
    close_braces = 0;
    
    if (ft_roll_check_arg(string))
	{
        debug_print_error("Invalid argument", i);
        return (1);
    }
    while (string[i])
	{
        while (string[i] >= '0' && string[i] <= '9')
            i++;
		if (string[i] == '(')
		{
			if (ft_check_open_braces(string, i, &open_braces))
			{
				debug_print_error("Invalid open brace", i);
				return(1);
			}
		}
		else if (string[i] == ')')
		{
			if (ft_check_close_braces(string, i, open_braces, &close_braces))
			{
				debug_print_error("Invalid close brace", i);
				return (1);
			}
		}
		else if (string[i] == '-' || string[i] == '+')
		{
			if (ft_check_plus_minus(string, i))
			{
				debug_print_error("Invalid plus/minus operator", i);
				return (1);
			}
		} 
		else if (string[i] == '/' || string[i] == '*')
		{
			if (ft_check_divide_multiply(string, i))
			{
				debug_print_error("Invalid divide/multiply operator", i);
				return (1);
			}
		}
		else if (string[i] == 'd')
		{
			if (ft_check_dice(string, i))
			{
				debug_print_error("Invalid dice notation", i);
				return(1);
			}
		}
		if (string[i])
			i++;
	} 
	return (0);
}
