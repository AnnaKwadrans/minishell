#include "parser.h"
/*
char	**rm_quotes(char **args)
{
	char	**res;
	int	i;

	res = (char **)malloc(sizeof(char *) * (array_size(args) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (args[i])
	{
		res[i] = rm_quotes_arg(args[i]);
		i++;
	}
	res[i] = NULL;
	free_array(args);
	return(res);
}
*//*
char	*rm_quotes_arg(char *arg)
{
	char	*res;
	int	i;
	int	j;
	bool	q_simple;
	bool	q_double;

	res = (char *)malloc(sizeof(char) * (count_no_quotes(arg) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	q_simple = 0;
	q_double = 0;
	while (arg[i])
	{
		if (cpy_char(arg[i], &q_simple, &q_double))
		{
			res[j] = arg[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
*/
bool	cpy_char(char arg, bool *q_simple, bool *q_double)
{
	if (arg == '\'' && *q_simple == 0 && *q_double == 0)
	{
		*q_simple = 1;
		return (0);
	}
	else if (arg == '\'' && *q_simple == 1)
	{
		*q_simple = 0;
		return (0);
	}
	else if (arg == '\"' && *q_double == 0 && *q_simple == 0)
	{
		*q_double = 1;
		return (0);
	}
	else if (arg == '\"' && *q_double == 1)
	{
		*q_double = 0;
		return (0);
	}
	else
		return (1);
}

int	count_no_quotes(char *arg)
{
	int	i;
	int	count;
	bool	q_simple;
	bool	q_double;

	i = 0;
	count = 0;
	q_simple = 0;
	q_double = 0;
	while (arg[i])
	{
		if (cpy_char(arg[i], &q_simple, &q_double))
			count++;
		i++;
		/*
		if (arg[i] == '\'' && q_simple == 0 && q_double == 0)
		{
			q_simple = 1;
			i++;
		}
		else if (arg[i] == '\'' && q_simple == 1)
		{
			q_simple = 0;
			i++;
		}
		else if (arg[i] == '\"' && q_double == 0 && q_simple == 0)
		{
			q_double = 1;
			i++;
		}
		else if (arg[i] == '\"' && q_double == 1)
		{
			q_double = 0;
			i++;
		}
		*/
		//else
		//{
		//	i++;
		//	count++;
		//}
	}
	return (count);
}
