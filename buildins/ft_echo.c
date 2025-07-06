#include "builtins.h"

static int	is_correct_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo (t_data *data, char **args)
{
	int	i;
	int	size;
	int	is_n_flag;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	size = array_size(args) - 1;
	if (args[1])
		is_n_flag = is_correct_flag(args[1]);
	i = 1;
	if (is_n_flag)
		i = 2;
	while (i < size)
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("%s", args[i]);
	if (!is_n_flag)
		printf("\n");
	return (0);
}
